/*******************************************************************************************************
*  Copyright 2017 Alliance for Sustainable Energy, LLC
*
*  NOTICE: This software was developed at least in part by Alliance for Sustainable Energy, LLC
*  (�Alliance�) under Contract No. DE-AC36-08GO28308 with the U.S. Department of Energy and the U.S.
*  The Government retains for itself and others acting on its behalf a nonexclusive, paid-up,
*  irrevocable worldwide license in the software to reproduce, prepare derivative works, distribute
*  copies to the public, perform publicly and display publicly, and to permit others to do so.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted
*  provided that the following conditions are met:
*
*  1. Redistributions of source code must retain the above copyright notice, the above government
*  rights notice, this list of conditions and the following disclaimer.
*
*  2. Redistributions in binary form must reproduce the above copyright notice, the above government
*  rights notice, this list of conditions and the following disclaimer in the documentation and/or
*  other materials provided with the distribution.
*
*  3. The entire corresponding source code of any redistribution, with or without modification, by a
*  research entity, including but not limited to any contracting manager/operator of a United States
*  National Laboratory, any institution of higher learning, and any non-profit organization, must be
*  made publicly available under this license for as long as the redistribution is made available by
*  the research entity.
*
*  4. Redistribution of this software, without modification, must refer to the software by the same
*  designation. Redistribution of a modified version of this software (i) may not refer to the modified
*  version by the same designation, or by any confusingly similar designation, and (ii) must refer to
*  the underlying software originally provided by Alliance as �System Advisor Model� or �SAM�. Except
*  to comply with the foregoing, the terms �System Advisor Model�, �SAM�, or any confusingly similar
*  designation may not be used to refer to any modified version of this software or any modified
*  version of the underlying software originally provided by Alliance without the prior written consent
*  of Alliance.
*
*  5. The name of the copyright holder, contributors, the United States Government, the United States
*  Department of Energy, or any of their employees may not be used to endorse or promote products
*  derived from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
*  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
*  FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER,
*  CONTRIBUTORS, UNITED STATES GOVERNMENT OR UNITED STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR
*  EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
*  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
*  IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
*  THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************************************/

#include <cmath>
#include <numeric>

#include <wx/wx.h>
#include <wx/gbsizer.h>
#include <wx/srchctrl.h>

#include <wex/plot/plaxis.h>
#include <wex/plot/plbarplot.h>
#include <wex/plot/pllineplot.h>
#include <wex/plot/plscatterplot.h>
#include <wex/plot/plcontourplot.h>
#include <wex/plot/plcolourmap.h>

#include <wex/dview/dvselectionlist.h>

#include <wex/radiochoice.h>
#include <wex/utils.h>
#include <wex/exttext.h>
#include <wex/metro.h>
#include <wex/snaplay.h>
#include <wex/matrix.h>

#include "case.h"
#include "uncertainties.h"
#include "variables.h"
#include "simulation.h"
#include "results.h"

Uncertainties::Uncertainties()
{
	Type = BAR;
	ShowXValues = ShowYValues = ShowLegend = true;
	LegendPos = wxPLPlotCtrl::RIGHT;
	Size=0;
	CoarseGrid = FineGrid = true;	
	YMin=YMax= std::numeric_limits<double>::quiet_NaN();
	FontScale = 1;
	FontFace = 1;  // default to 'modern'
}

void Uncertainties::Copy(Uncertainties *gr)
{
	Type = gr->Type;
	Y = gr->Y;
	
	XLabel = gr->XLabel;
	YLabel = gr->YLabel;
	Title = gr->Title;
	ShowXValues = gr->ShowXValues;
	ShowYValues = gr->ShowYValues;
	ShowLegend = gr->ShowLegend;
	LegendPos = gr->LegendPos;
	Size = gr->Size;
	CoarseGrid = gr->CoarseGrid;
	FineGrid = gr->FineGrid;
	YMin = gr->YMin;
	YMax = gr->YMax;
	Notes = gr->Notes;
	FontScale = gr->FontScale;
	FontFace = gr->FontFace;
}


bool Uncertainties::SameAs(Uncertainties *gr)
{
	return ( this->Title == gr->Title && this->Y == gr->Y );
}

bool Uncertainties::Write( wxOutputStream &os )
{
	wxDataOutputStream ds(os);
	ds.Write16( 0xfd ); // identifier
	ds.Write8( 1 ); // version

	ds.Write32( Type );
	ds.WriteString( Title );
	ds.Write32( Y.Count() );
	for (int i=0;i<(int)Y.Count();i++)
		ds.WriteString( Y[i] );

	ds.WriteString( XLabel );
	ds.WriteString( YLabel );
	ds.Write8( ShowXValues ? 1 : 0 );
	ds.Write8( ShowYValues ? 1 : 0  );
	ds.Write8( ShowLegend ? 1 : 0  );
	ds.Write8((wxUint8)LegendPos );
	ds.Write8((wxUint8)Size );
	ds.Write8( CoarseGrid ? 1 : 0  );
	ds.Write8( FineGrid ? 1 : 0  );
	ds.WriteDouble( YMin );
	ds.WriteDouble( YMax );
	ds.WriteString( Notes );
	ds.WriteDouble( FontScale );
	ds.Write8((wxUint8)FontFace );

	ds.Write16( 0xfd ); // identifier
	return true;
}


bool Uncertainties::Read( wxInputStream &is )
{
	size_t i, count;
	wxDataInputStream ds(is);

	unsigned short identifier = ds.Read16();
	/*unsigned char ver = */ ds.Read8(); // read the version number, not currently used...

	Type = ds.Read32();
	Title = ds.ReadString();

	Y.Clear();
	count = ds.Read32();
	for (i=0;i<count;i++)
		Y.Add( ds.ReadString() );

	XLabel = ds.ReadString();
	YLabel = ds.ReadString();
	
	ShowXValues = ds.Read8() ? true : false;
	ShowYValues = ds.Read8() ? true : false;
	ShowLegend = ds.Read8() ? true : false;
	LegendPos = ds.Read8();

	Size = ds.Read8();
	CoarseGrid = ds.Read8() ? true : false;
	FineGrid = ds.Read8() ? true : false;
	
	YMin = ds.ReadDouble();
	YMax = ds.ReadDouble();
	
	Notes = ds.ReadString();
	FontScale = ds.ReadDouble();
	FontFace = ds.Read8();

	return identifier == ds.Read16();
}


DEFINE_EVENT_TYPE( wxEVT_Uncertainties_SELECT )

BEGIN_EVENT_TABLE( UncertaintiesCtrl, wxPLPlotCtrl )
	EVT_LEFT_DOWN( UncertaintiesCtrl::OnLeftDown )
END_EVENT_TABLE()


UncertaintiesCtrl::UncertaintiesCtrl( wxWindow *parent, int id )
	: wxPLPlotCtrl( parent, id, wxDefaultPosition, wxScaleSize(500,400) )
{
	SetBackgroundColour( *wxWHITE );
}


std::vector<wxColour> &Uncertainties::Colours()
{
	
static std::vector<wxColour> s_colours;
	if ( s_colours.size() == 0 )
	{
		s_colours.push_back( wxColour(111,164,196) );
		s_colours.push_back( wxColour("GREY") );
		s_colours.push_back( wxColour(181,211,227) );
		s_colours.push_back( *wxLIGHT_GREY );
		s_colours.push_back( wxColour("PALE GREEN") );
		s_colours.push_back( wxColour("GOLDENROD") );
		s_colours.push_back( wxColour("MEDIUM VIOLET RED") );
		s_colours.push_back( wxColour("MEDIUM SEA GREEN") );
		s_colours.push_back( wxColour("DARK SLATE GREY") );
		s_colours.push_back( wxColour("WHEAT") );
		s_colours.push_back( wxColour("FIREBRICK") );
		s_colours.push_back( wxColour("dark orchid") );
		s_colours.push_back( wxColour("dim grey") );
		s_colours.push_back( wxColour("brown") );
	}

	return s_colours;
}

int UncertaintiesCtrl::Figure2(Simulation *sim)
{
	m_s = sim;
	// Figure 2 testing
	ShowGrid(false, false);
	std::vector<wxRealPoint> data1, data2;


	double mu1 = 5000; // kWh mean gross annual energy output
	double sigma1 = mu1 / 50; // standard deviation
	double losses = 0.1*mu1;
	double mu2 = mu1 - losses; // kWh net annual energy
	double sigma2 = mu2 / 40;

	// values depend on technology - testing for wind or can standardize outputs
	// Read in in Uncertainties.lk (like autographs)
	if (VarValue *vv = m_s->GetValue("annual_gross_energy"))
	{
		mu1 = vv->Value();
	}
	// sigma from Darice 
	if (VarValue *vv = m_s->GetValue("wspd_uncert"))
	{
		sigma1 = vv->Value() / 100.0;
		sigma1 *= mu1;
	}

	if (VarValue *vv = m_s->GetValue("annual_energy"))
	{
		mu2 = vv->Value();
	}
	if (VarValue *vv = m_s->GetValue("total_uncert"))
	{
		sigma2 = vv->Value() / 100.0;
		sigma2 *= mu2;
	}

	int interval = 1000;
	double area1 = 0, area2 = 0, ymax = 0;
	for (int i = 0; i < interval; i++)
	{
		double x1 = mu1 - 3 * sigma1 + i * 6 * sigma1 / interval;
		double y1 = exp(0.0 - ((x1 - mu1)*(x1 - mu1) / (2 * sigma1*sigma1))) / sqrt(2 * M_PI *sigma1*sigma1);
		data1.push_back(wxRealPoint(x1, y1));
		if (i > 0)
			area1 += y1 * (x1 - data1[i - 1].x);
		double x2 = mu2 - 3 * sigma2 + i * 6 * sigma2 / interval;
		double y2 = exp(0.0 - ((x2 - mu2)*(x2 - mu2) / (2 * sigma2*sigma2))) / sqrt(2 * M_PI *sigma2*sigma2);
		data2.push_back(wxRealPoint(x2, y2));
		if (i > 0)
			area2 += y2 * (x2 - data2[i - 1].x);
		if (y1 > ymax) ymax = y1;
		if (y2 > ymax) ymax = y2;
	}



	AddPlot(new wxPLLinePlot(data1, "Gross energy", wxColour("Black")));
	AddPlot(new wxPLLinePlot(data2, "Net energy", wxColour("Blue")));

	std::vector<wxRealPoint> p50LineGross;
	p50LineGross.push_back(wxRealPoint(mu1, 1.1*ymax));
	p50LineGross.push_back(wxRealPoint(mu1, 0));
	AddAnnotation(new wxPLLineAnnotation(p50LineGross, 2, *wxBLACK, wxPLOutputDevice::DASH), wxPLAnnotation::AXIS);

	std::vector<wxRealPoint> p50LineNet;
	p50LineNet.push_back(wxRealPoint(mu2, 1.1*ymax));
	p50LineNet.push_back(wxRealPoint(mu2, 0));
	AddAnnotation(new wxPLLineAnnotation(p50LineNet, 2, *wxBLUE, wxPLOutputDevice::DASH), wxPLAnnotation::AXIS);

	double p90 = 0.94* mu2;
	std::vector<wxRealPoint> p90LineNet;
	p90LineNet.push_back(wxRealPoint(p90, 0.1*ymax));
	p90LineNet.push_back(wxRealPoint(p90, 0));
	AddAnnotation(new wxPLLineAnnotation(p90LineNet, 2, *wxBLUE, wxPLOutputDevice::DASH), wxPLAnnotation::AXIS);


	std::vector<wxRealPoint> LossArrow;
	LossArrow.push_back(wxRealPoint(mu1, ymax));
	LossArrow.push_back(wxRealPoint(mu2, ymax));
	AddAnnotation(new wxPLLineAnnotation(LossArrow, 2, *wxBLUE, wxPLOutputDevice::DASH, wxPLLineAnnotation::FILLED_ARROW), wxPLAnnotation::AXIS);


	AddAnnotation(new wxPLTextAnnotation("Predicted Losses", wxRealPoint(mu2 + 0.4*(mu1 - mu2), 0.95*ymax), 2.0, 0, *wxBLACK), wxPLAnnotation::AXIS);
	AddAnnotation(new wxPLTextAnnotation("Gross Energy P50", wxRealPoint(mu1, 0.5*ymax), 2.0, 90, *wxBLACK), wxPLAnnotation::AXIS);
	AddAnnotation(new wxPLTextAnnotation("Net Energy P50", wxRealPoint(mu2, 0.5*ymax), 2.0, 90, *wxBLUE), wxPLAnnotation::AXIS);
	AddAnnotation(new wxPLTextAnnotation("P90", wxRealPoint(p90, 0.1*ymax), 2.0, 0, *wxBLUE), wxPLAnnotation::AXIS);
	GetYAxis1()->Show(false);
	GetXAxis1()->SetLabel("Annual Energy Delivered (kWh)");
	ShowLegend(false);
	SetBorderWidth(0);
//	Invalidate();
//	Refresh();
	return 0;
}

int UncertaintiesCtrl::Figure5(Simulation *sim)
{
	m_s = sim;

	ShowGrid(false, false);
	std::vector<wxRealPoint> data1, data2;

	// wind speed bins - need to make in cmod_windpower - missing now - only "wind_speed" timeseries array for all weather file inputs
	// turbine curve

	size_t ws_count;
	double *ws;
	size_t tp_count;
	double *tp;
	if (VarValue *vv = m_s->GetValue("wind_turbine_powercurve_windspeeds"))
	{
		ws = vv->Array(&ws_count);
	}
	if (VarValue *vv = m_s->GetValue("wind_turbine_powercurve_powerout"))
	{
		tp = vv->Array(&tp_count);
	}

	size_t wsb_count;
	double *wsb;
	if (VarValue *vv = m_s->GetValue("wind_speed"))
	{
		wsb = vv->Array(&wsb_count);
	}
	double max_wsb = 0;
	for (size_t i = 0; i < wsb_count; i++)
	{
		if (wsb[i] > max_wsb) max_wsb = wsb[i];
	}
	size_t num_bins = 20;
	std::vector<int> freq(num_bins);
	for (size_t j = 0; j < num_bins; j++)
		freq[j] = 0;
	double bin_width = max_wsb / num_bins;
	for (size_t i = 0; i < wsb_count; i++)
	{
		for (size_t j = 0; j< num_bins; j++)
			if ((wsb[i] > j*bin_width) && (wsb[i] < (j+1)*bin_width)) freq[j]++;
	}

	double max_speed = max_wsb;

	if (tp_count == 0 || ws_count == 0 || tp_count != ws_count)
		return 1;
	double max_power = 0;
	for (size_t i = 0; i < ws_count; i++)
	{
		double speed = ws[i];
		double power = tp[i];
		if (power > max_power) max_power = power;
		if (speed > max_speed) max_speed = speed;
		data2.push_back(wxRealPoint(speed, power));
	}

	double freq_max = 0;
	for (size_t i = 0; i < num_bins; i++)
	{
		double speed = (i+0.5)*bin_width;
		if (speed > max_speed) max_speed = speed;
		double freq_bin = (double)freq[i]/(double)wsb_count;
		if (freq_bin > freq_max) freq_max = freq_bin;
		data1.push_back(wxRealPoint(speed, freq_bin));
	}

	AddPlot(new wxPLBarPlot(data1, 0.0, "Wind speed frequency", wxColour("Blue")));
	SetYAxis1(new wxPLLinearAxis(0, freq_max, "Wind speed frequecy"));

	AddPlot(new wxPLLinePlot(data2, "Turbine power (kW)", wxColour("Gray")), wxPLPlot::X_BOTTOM, wxPLPlot::Y_RIGHT);
	SetYAxis2(new wxPLLinearAxis(0, 1.05*max_power, "Turbine power"));

	GetXAxis1()->SetLabel("Wind speed (m/s)");
// crashing
/*	SetXAxis1(new wxPLLinearAxis(0, 1.05 * max_speed, "Wind speed (m/s)"));

	std::vector<wxRealPoint> LineRatedPower;
	LineRatedPower.push_back(wxRealPoint(20, 0.1));
	LineRatedPower.push_back(wxRealPoint(40, 0.1));
	AddAnnotation(new wxPLLineAnnotation(LineRatedPower, 2, wxColour("Gray"), wxPLOutputDevice::DASH), wxPLAnnotation::AXIS);// , wxPLPlot::X_BOTTOM, wxPLPlot::Y_RIGHT);
/*
 //Horizontal annotations crashing...
	std::vector<wxRealPoint> LineRatedPower;
	LineRatedPower.push_back(wxRealPoint(20, max_power));
	LineRatedPower.push_back(wxRealPoint(40, max_power));
	AddAnnotation(new wxPLLineAnnotation(LineRatedPower, 2, wxColour("Gray"), wxPLOutputDevice::DASH), wxPLAnnotation::AXIS , wxPLPlot::X_BOTTOM, wxPLPlot::Y_RIGHT);

	AddAnnotation(new wxPLTextAnnotation("Rated power", wxRealPoint(0.75* max_speed, max_power), 2.0, 0, *wxBLACK), wxPLAnnotation::AXIS, wxPLPlot::X_BOTTOM, wxPLPlot::Y_RIGHT);
*/

	ShowLegend(false);
//	SetBorderWidth(0);

	return 0;

}

int UncertaintiesCtrl::Figure10(Simulation *sim)
{
	return 0;
}

int UncertaintiesCtrl::Display( Simulation *sim, Uncertainties &gi )
{
static const char *s_monthNames[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", 
										"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

//	std::vector<wxColour> &s_colours = Uncertainties::Colours();

	m_s = sim;
	m_g.Copy( &gi );

	DeleteAllPlots();
	DeleteAllAnnotations();
	
	if ( !m_s )
	{
		Refresh();
		return 1;
	}

	if (m_g.Title.Lower() == "figure2")
		Figure2(sim);
	else if (m_g.Title.Lower() == "figure5")
			Figure5(m_s);
	/*
	// setup visual properties of Uncertainties
	wxFont font( *wxNORMAL_FONT );
	switch( m_g.FontFace )
	{
	case 1: font = wxMetroTheme::Font( wxMT_LIGHT ); break;
	case 2: font = *wxSWISS_FONT; break;
	case 3: font = wxFont( 12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL ); break;
	case 4: font = wxFont( 12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL ); break;
	}
	
	if ( m_g.FontScale != 0.0 )
	{
		int points = (int)(((double)font.GetPointSize())*m_g.FontScale);
		if ( points < 4 ) points = 4;
		if ( points > 32 ) points = 32;
		font.SetPointSize( points );		
	}
	
	SetFont( font );

	ShowGrid( m_g.CoarseGrid, m_g.FineGrid );
	SetTitle( m_g.Title );
	ShowLegend( m_g.ShowLegend );	
	SetLegendLocation( (wxPLPlotCtrl::LegendPos)m_g.LegendPos );
	
	// setup data
	std::vector<VarValue*> yvars;
	wxArrayString ynames;
	int ndata = -1;

	if (m_g.Type == Uncertainties::CONTOUR)
	{
		if (m_g.Y.size()== 1)
			ndata = 0;
	}
	else
	{
		for (size_t i = 0; i < m_g.Y.size(); i++)
		{
			if (VarValue *vv = m_s->GetValue(m_g.Y[i]))
			{
				int count = 0;
				if (vv->Type() == VV_NUMBER)
					count = 1;
				else if (vv->Type() == VV_ARRAY)
					count = vv->Length();

				if (i == 0) ndata = count;
				else if (ndata != count) ndata = -1;

				if (count > 0)
				{
					yvars.push_back(vv);
					ynames.push_back(m_g.Y[i]);
				}
			}
		}
	}
	if ( ndata < 0 )
	{
		SetTitle( "All variables must have the same number of data values." );
		Refresh();
		return -1;
	}

	std::vector< std::vector<wxRealPoint> > plotdata( yvars.size() );

	int cidx = 0; // colour index
	wxPLBarPlot *last_bar = 0;
	std::vector<wxPLBarPlot*> bar_group;

	for (size_t i = 0; i < yvars.size(); i++)
	{
		if (yvars[i]->Type() == VV_ARRAY)
		{
			size_t n = 0;
			double *p = yvars[i]->Array(&n);

			plotdata[i].reserve(ndata);
			for (size_t k = 0; k < n; k++)
			{
				if (std::isnan(p[k]))
					plotdata[i].push_back(wxRealPoint(k, 0));
				else
					plotdata[i].push_back(wxRealPoint(k, p[k]));
			}
		}
		else
		{
			if (std::isnan(yvars[i]->Value()))
				plotdata[i].push_back(wxRealPoint(i, 0));
			else
				plotdata[i].push_back(wxRealPoint(i, yvars[i]->Value()));
		}

		wxPLPlottable *plot = 0;
		if (m_g.Type == Uncertainties::LINE)
			plot = new wxPLLinePlot(plotdata[i], m_s->GetLabel(ynames[i]), s_colours[cidx],
				wxPLLinePlot::SOLID, m_g.Size + 2);
		else if (m_g.Type == Uncertainties::BAR || m_g.Type == Uncertainties::STACKED)
		{
			wxPLBarPlot *bar = new wxPLBarPlot(plotdata[i], 0.0, m_s->GetLabel(ynames[i]), s_colours[cidx]);
			if (m_g.Size != 0)
				bar->SetThickness(m_g.Size);

			if (m_g.Type == Uncertainties::STACKED)
				bar->SetStackedOn(last_bar);
			else
				bar_group.push_back(bar);

			last_bar = bar;
			plot = bar;
		}
		else if (m_g.Type == Uncertainties::SCATTER)
		{
			plot = new wxPLScatterPlot(plotdata[i], m_s->GetLabel(ynames[i]), s_colours[cidx], m_g.Size + 2);
			if (plotdata[i].size() < 100)
				plot->SetAntiAliasing(true);
		}


		if ( ++cidx >= (int)s_colours.size() ) cidx = 0; // incr and wrap around colour index
		
		if ( plot != 0 )
			AddPlot( plot, wxPLPlotCtrl::X_BOTTOM, wxPLPlotCtrl::Y_LEFT, wxPLPlotCtrl::PLOT_TOP, false );
	}

	
	// group the bars together if they're not stacked and not single values
	if ( ndata > 1 && m_g.Type == Uncertainties::BAR )
		for( size_t i=0;i<bar_group.size();i++ )
			bar_group[i]->SetGroup( bar_group );

	// create the axes
	if (ndata == 0) // contour
	{
		if (m_g.Type == Uncertainties::CONTOUR)
		{
			// y size checked for 1 above
			double zmin = 1e99, zmax = -1e99;
			wxMatrix<double> XX, YY, ZZ;
			if (VarValue *vv = m_s->GetValue(m_g.Y[0]))
			{
				if (vv->Type() == VV_MATRIX)
				{
					// Assume col[0] contains x values in order
					// assume row[0] contains y values in order
					size_t nx, ny;
					double *data = vv->Matrix(&nx, &ny);
					XX.Resize(nx - 1, ny - 1);
					YY.Resize(nx - 1, ny - 1);
					ZZ.Resize(nx - 1, ny - 1);
					for (size_t i = 1; i < nx; i++)
					{
						for (size_t j = 1; j < ny; j++)
						{
							XX.At(i-1, j-1) = data[j];
							YY.At(i-1, j -1) = data[i*ny];
							ZZ.At(i-1, j-1) = data[i*ny + j];
							if (ZZ.At(i-1, j - 1) < zmin) zmin = ZZ.At(i-1, j - 1);
							if (ZZ.At(i-1, j - 1) > zmax) zmax = ZZ.At(i-1, j - 1);
						}
					}
					wxPLContourPlot *plot = 0;
					wxPLColourMap *jet = new wxPLJetColourMap(zmin, zmax);
					plot = new wxPLContourPlot(XX, YY, ZZ, true, wxEmptyString, 24, jet);
					if (plot != 0)
					{
						AddPlot(plot, wxPLPlotCtrl::X_TOP, wxPLPlotCtrl::Y_LEFT, wxPLPlotCtrl::PLOT_TOP, false);
						SetSideWidget(jet);
					}
				}
			}
		}
	}
	else
	{
		// x-axis
		if (ndata == 1)
		{
			// single value axis
			wxPLLabelAxis *x1 = new wxPLLabelAxis(-1, yvars.size(), m_g.XLabel);
			if (m_g.ShowXValues)
			{
				for (size_t i = 0; i < ynames.size(); i++)
					x1->Add(i, m_s->GetLabel(ynames[i]));
			}
			SetXAxis1(x1);
		}
		else if (ndata == 12)
		{
			// month axis
			wxPLLabelAxis *x1 = new wxPLLabelAxis(-1, 12, m_g.XLabel);
			for (size_t i = 0; i < 12; i++)
				x1->Add(i, s_monthNames[i]);
			SetXAxis1(x1);
		}
		else
		{
			// linear axis
			SetXAxis1(new wxPLLinearAxis(-1, ndata + 1, m_g.XLabel));
		}
		// setup y axis

		if (GetPlotCount() > 0)
		{
			double ymin, ymax;
			GetPlot(0)->GetMinMax(0, 0, &ymin, &ymax);
			for (size_t i = 1; i < GetPlotCount(); i++)
				GetPlot(i)->ExtendMinMax(0, 0, &ymin, &ymax);

			if (m_g.Type == Uncertainties::STACKED || m_g.Type == Uncertainties::BAR)
			{ // forcibly include the zero line for bar plots
				if (ymin > 0) ymin = 0;
				if (ymax < 0) ymax = 0;
			}

			double yadj = (ymax - ymin)*0.05;

			if (ymin != 0) ymin -= yadj;
			if (ymax != 0) ymax += yadj;

			if (ymin == ymax) {
				// no variation in y values, so pick some reasonable Uncertainties bounds
				if (ymax == 0)
					ymax = 1;
				else
					ymax += (ymax * 0.05);
				if (ymin == 0)
					ymin = -1;
				else
					ymin -= (ymin * 0.05);
			}

			SetYAxis1(new wxPLLinearAxis(ymin, ymax, m_g.YLabel));
		}
	}
	*/

	Invalidate();
	Refresh();
	return 0;
}

int UncertaintiesCtrl::Display(std::vector<Simulation *>sims, Uncertainties &gi)
{
	static const char *s_monthNames[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

	static std::vector<wxColour> s_colours;
	if (s_colours.size() == 0)
	{
		s_colours.push_back(wxColour(111, 164, 196));
		s_colours.push_back(wxColour("GREY"));
		s_colours.push_back(wxColour(181, 211, 227));
		s_colours.push_back(*wxLIGHT_GREY);
		s_colours.push_back(wxColour("PALE GREEN"));
		s_colours.push_back(wxColour("GOLDENROD"));
		s_colours.push_back(wxColour("MEDIUM VIOLET RED"));
		s_colours.push_back(wxColour("MEDIUM SEA GREEN"));
		s_colours.push_back(wxColour("DARK SLATE GREY"));
		s_colours.push_back(wxColour("WHEAT"));
		s_colours.push_back(wxColour("FIREBRICK"));
		s_colours.push_back(wxColour("dark orchid"));
		s_colours.push_back(wxColour("dim grey"));
		s_colours.push_back(wxColour("brown"));
	}

	m_g.Copy(&gi);

	DeleteAllPlots();

	if ((sims.size() <= 0) || (m_g.Y.Count() > 1))
	{
		Refresh();
		return 1;
	}
	m_s = sims[0];

	// setup visual properties of Uncertainties
	wxFont font(*wxNORMAL_FONT);
	switch (m_g.FontFace)
	{
	case 1: font = wxMetroTheme::Font(wxMT_LIGHT); break;
	case 2: font = *wxSWISS_FONT; break;
	case 3: font = wxFont(12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL); break;
	case 4: font = wxFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL); break;
	}

	if (m_g.FontScale != 0.0)
	{
		int points = (int)(((double)font.GetPointSize())*m_g.FontScale);
		if (points < 4) points = 4;
		if (points > 32) points = 32;
		font.SetPointSize(points);
	}

	SetFont(font);

	ShowGrid(m_g.CoarseGrid, m_g.FineGrid);
	SetTitle(m_g.Title);
	ShowLegend(m_g.ShowLegend);
	SetLegendLocation((wxPLPlotCtrl::LegendPos)m_g.LegendPos);

	// setup data
	std::vector<VarValue*> yvars;
	wxArrayString ynames;
	int ndata = -1;

	for (size_t i = 0; i<sims.size(); i++)
	{
		if (VarValue *vv = sims[i]->GetValue(m_g.Y[0]))
		{
			int count = 0;
			if (vv->Type() == VV_NUMBER)
				count = 1;
			else if (vv->Type() == VV_ARRAY)
				count = vv->Length();

			if (i == 0) ndata = count;
			else if (ndata != count) ndata = -1;

			if (count > 0)
			{
				yvars.push_back(vv);
				ynames.push_back(sims[i]->GetLabel(m_g.Y[0]) + wxString::Format(" : run %d", (int)(i+1)));
			}
		}
	}

	if (ndata < 0)
	{
		SetTitle("All variables must have the same number of data values.");
		Refresh();
		return -1;
	}

	std::vector< std::vector<wxRealPoint> > plotdata(yvars.size());

	int cidx = 0; // colour index
	wxPLBarPlot *last_bar = 0;
	std::vector<wxPLBarPlot*> bar_group;

	for (size_t i = 0; i<yvars.size(); i++)
	{
		if (yvars[i]->Type() == VV_ARRAY)
		{
			size_t n = 0;
			double *p = yvars[i]->Array(&n);

			plotdata[i].reserve(ndata);
			for (size_t k = 0; k < n; k++)
			{
				if (std::isnan(p[k]))
					plotdata[i].push_back(wxRealPoint(k, 0));
				else
					plotdata[i].push_back(wxRealPoint(k, p[k]));
			}
		}
		else
		{
			if (std::isnan(yvars[i]->Value()))
				plotdata[i].push_back(wxRealPoint(i, 0));
			else
				plotdata[i].push_back(wxRealPoint(i, yvars[i]->Value()));
		}

		wxPLPlottable *plot = 0;
		if (m_g.Type == Uncertainties::LINE)
			plot = new wxPLLinePlot(plotdata[i], ynames[i], s_colours[cidx],
			wxPLLinePlot::SOLID, m_g.Size + 2);
		else if (m_g.Type == Uncertainties::BAR || m_g.Type == Uncertainties::STACKED)
		{
			wxPLBarPlot *bar = new wxPLBarPlot(plotdata[i], 0.0, ynames[i], s_colours[cidx]);
			if (m_g.Size != 0)
				bar->SetThickness(m_g.Size);

			if (m_g.Type == Uncertainties::STACKED)
				bar->SetStackedOn(last_bar);
			else
				bar_group.push_back(bar);

			last_bar = bar;
			plot = bar;
		}
		else if (m_g.Type == Uncertainties::SCATTER)
		{
			plot = new wxPLScatterPlot(plotdata[i], ynames[i], s_colours[cidx], m_g.Size + 2);
			if (plotdata[i].size() < 100)
				plot->SetAntiAliasing(true);
		}


		if (++cidx >= (int)s_colours.size()) cidx = 0; // incr and wrap around colour index

		if (plot != 0)
			AddPlot(plot, wxPLPlotCtrl::X_BOTTOM, wxPLPlotCtrl::Y_LEFT, wxPLPlotCtrl::PLOT_TOP, false);
	}


	// group the bars together if they're not stacked and not single values
	if (ndata > 1 && m_g.Type == Uncertainties::BAR)
		for (size_t i = 0; i<bar_group.size(); i++)
			bar_group[i]->SetGroup(bar_group);

	// create the axes
	if (ndata == 1)
	{
		// single value axis
		wxPLLabelAxis *x1 = new wxPLLabelAxis(-1, yvars.size(), m_g.XLabel);
		for (size_t i = 0; i<ynames.size(); i++)
			x1->Add(i, wxString::Format("%d", (int)( i+1)));
//			x1->Add(i, ynames[i]);
		SetXAxis1(x1);
	}
	else if (ndata == 12)
	{
		// month axis
		wxPLLabelAxis *x1 = new wxPLLabelAxis(-1, 12, m_g.XLabel);
		for (size_t i = 0; i<12; i++)
			x1->Add(i, s_monthNames[i]);
		SetXAxis1(x1);
	}
	else
	{
		// linear axis
		SetXAxis1(new wxPLLinearAxis(-1, ndata + 1, m_g.XLabel));
	}


	// setup y axis

	if (GetPlotCount() > 0)
	{
		double ymin, ymax;
		GetPlot(0)->GetMinMax(0, 0, &ymin, &ymax);
		for (size_t i = 1; i<GetPlotCount(); i++)
			GetPlot(i)->ExtendMinMax(0, 0, &ymin, &ymax);

		if (m_g.Type == Uncertainties::STACKED || m_g.Type == Uncertainties::BAR)
		{ // forcibly include the zero line for bar plots
			if (ymin > 0) ymin = 0;
			if (ymax < 0) ymax = 0;
		}

		double yadj = (ymax - ymin)*0.05;

		if (ymin != 0) ymin -= yadj;
		if (ymax != 0) ymax += yadj;

		if (ymin == ymax) {
			// no variation in y values, so pick some reasonable Uncertainties bounds
		  if (ymax == 0)
		    ymax = 1;
		  else
		    ymax = (ymax * 0.05);
		  if (ymin == 0)
		    ymin = -1;
		  else
		    ymin -= (ymin * 0.05);
		}

		SetYAxis1(new wxPLLinearAxis(ymin, ymax, m_g.YLabel));
	}


	Invalidate();
	Refresh();
	return 0;
}



void UncertaintiesCtrl::OnLeftDown( wxMouseEvent &evt )
{
	wxCommandEvent e( wxEVT_Uncertainties_SELECT, GetId() );
	e.SetEventObject( this );
	GetEventHandler()->ProcessEvent( e );
	
	evt.Skip();
}



DEFINE_EVENT_TYPE( wxEVT_Uncertainties_PROPERTY_CHANGE )

enum { ID_Y = wxID_HIGHEST+495, ID_TYPE, ID_TITLE, ID_XLABEL, ID_YLABEL, ID_SHOW_LEGEND, ID_LEGENDPOS, 
	ID_SCALE, ID_SIZE, ID_COARSE, ID_FINE, ID_FONT_FACE, ID_SRCH };

BEGIN_EVENT_TABLE( UncertaintiesProperties, wxPanel )
	EVT_DVSELECTIONLIST( ID_Y, UncertaintiesProperties::OnEdit )
	EVT_TEXT( ID_TITLE, UncertaintiesProperties::OnEdit )
	EVT_TEXT( ID_XLABEL, UncertaintiesProperties::OnEdit )
	EVT_TEXT(ID_YLABEL, UncertaintiesProperties::OnEdit)
	EVT_TEXT(ID_SRCH, UncertaintiesProperties::OnSearch)
	EVT_RADIOBUTTON(ID_TYPE, UncertaintiesProperties::OnEdit)
	EVT_COMMAND_SCROLL( ID_SCALE, UncertaintiesProperties::OnSlider )
	EVT_COMMAND_SCROLL( ID_SIZE, UncertaintiesProperties::OnSlider )
	EVT_CHECKBOX( ID_COARSE, UncertaintiesProperties::OnEdit )
	EVT_CHECKBOX( ID_FINE, UncertaintiesProperties::OnEdit )
	EVT_CHECKBOX( ID_SHOW_LEGEND, UncertaintiesProperties::OnEdit )
	EVT_CHOICE( ID_LEGENDPOS, UncertaintiesProperties::OnEdit )
	EVT_CHOICE( ID_FONT_FACE, UncertaintiesProperties::OnEdit )
END_EVENT_TABLE()


UncertaintiesProperties::UncertaintiesProperties( wxWindow *parent, int id )
	: wxPanel( parent, id )
{
	m_srch = new wxSearchCtrl(this, ID_SRCH);

	m_Y = new wxDVSelectionListCtrl( this, ID_Y, 1, wxDefaultPosition, wxDefaultSize, wxDVSEL_NO_COLOURS );
	m_Y->SetBackgroundColour( *wxWHITE );

	m_type = new wxRadioChoice( this, ID_TYPE );
	m_type->SetHorizontal( true );
	m_type->Add( "Bar" );
	m_type->Add( "Stack" );
	m_type->Add( "Line" );
	m_type->Add( "Scatter" );
	m_type->SetSelection( 0 );

	m_title = new wxExtTextCtrl( this, ID_TITLE );
	m_xlabel = new wxExtTextCtrl( this, ID_XLABEL );
	m_ylabel = new wxExtTextCtrl( this, ID_YLABEL );
	
	m_size = new wxSlider( this, ID_SIZE, 0, 0, 35);
	m_scale = new wxSlider( this, ID_SCALE, 10, 5, 15 );

	m_coarse = new wxCheckBox( this, ID_COARSE, "Coarse grid" );
	m_coarse->SetValue( true );
	m_fine = new wxCheckBox( this, ID_FINE, "Fine grid" );
	m_fine->SetValue( true );


	m_showLegend = new wxCheckBox( this, ID_SHOW_LEGEND, "Legend" );

	wxString lpos[] = { "Manual", 
		"Northwest", "Southwest", "Northeast", "Southeast", 
		"North", "South", "East", "West", 
		"Bottom", "Right" };
	m_legendPos = new wxChoice( this, ID_LEGENDPOS, wxDefaultPosition, wxDefaultSize, 11, lpos );

	wxString faces[] = { "Default", "Modern", "Sanserif", "Serif", "Fixed" };
	m_font = new wxChoice( this, ID_FONT_FACE, wxDefaultPosition, wxDefaultSize, 5, faces );
	
	wxFlexGridSizer *prop_sizer = new wxFlexGridSizer( 2 );
	prop_sizer->AddGrowableCol( 1 );

	prop_sizer->Add( new wxStaticText( this, wxID_ANY, "Title:" ), 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	prop_sizer->Add( m_title, 0, wxALL|wxEXPAND, 1 );
	
	prop_sizer->Add( new wxStaticText( this, wxID_ANY, "X label:" ), 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	prop_sizer->Add( m_xlabel, 0, wxALL|wxEXPAND, 1 );
	
	prop_sizer->Add( new wxStaticText( this, wxID_ANY, "Y label:" ), 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	prop_sizer->Add( m_ylabel, 0,  wxALL|wxEXPAND, 1 );
	
	prop_sizer->Add( new wxStaticText( this, wxID_ANY, "Size:" ),0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	prop_sizer->Add( m_size, 0, wxALL|wxEXPAND, 1 );

	prop_sizer->Add( new wxStaticText( this, wxID_ANY, "Text:" ), 0, wxALL|wxALIGN_CENTER_VERTICAL, 2 );
	
	wxBoxSizer *text_sizer = new wxBoxSizer( wxHORIZONTAL );
	text_sizer->Add( m_scale, 1, wxALL|wxEXPAND, 1 );
	text_sizer->Add( m_font, 0, wxALL, 1 );
	prop_sizer->Add( text_sizer, 0, wxALL|wxEXPAND, 1 );

	prop_sizer->Add( m_showLegend, 0, wxALL|wxALIGN_CENTER_VERTICAL, 4 );
	prop_sizer->Add( m_legendPos, 0, wxALL, 1 );


	wxBoxSizer *chk_sizer = new wxBoxSizer( wxHORIZONTAL );
	chk_sizer->Add( m_coarse, 1, wxALL|wxEXPAND, 4 );
	chk_sizer->Add( m_fine, 1, wxALL|wxEXPAND, 4 );
		

	wxBoxSizer *sizer = new wxBoxSizer( wxVERTICAL );
	sizer->Add( m_type, 0, wxALL|wxEXPAND, 4 );
	sizer->Add( prop_sizer, 0, wxALL|wxEXPAND, 4 );
	sizer->Add( chk_sizer, 0, wxALL|wxEXPAND, 4 );
	sizer->Add(m_srch, 0,  wxEXPAND|wxALL, 1);
	sizer->Add(m_Y, 1, wxALL | wxEXPAND, 0);
	SetSizer(sizer);
	
	Enable( false );
}


void UncertaintiesProperties::SetupVariables( Simulation *sim )
{

	Clear();

	if ( !sim ) return;
	m_sim = sim;
	m_names.Clear();
	m_selected.Clear();
	m_srch->Clear();

	int vsx, vsy;
	m_Y->GetViewStart( &vsx, &vsy );	
	m_Y->Freeze();
	m_Y->RemoveAll();

	PopulateSelectionList( m_Y, &m_names, sim );

	m_Y->ExpandSelections();
	m_Y->Scroll( vsx, vsy );
	m_Y->Thaw();


	Enable( true );
}

void UncertaintiesProperties::Clear()
{
	m_xlabel->Clear();
	m_ylabel->Clear();
	m_title->Clear();

	Enable( false );
}


void UncertaintiesProperties::Set( const Uncertainties &g )
{

	m_names.Clear();
	m_selected.Clear();
	m_srch->Clear();

	int vsx, vsy;
	m_Y->GetViewStart(&vsx, &vsy);
	m_Y->Freeze();
	m_Y->RemoveAll();

	PopulateSelectionList(m_Y, &m_names, m_sim);

	m_Y->ExpandSelections();
	m_Y->Scroll(vsx, vsy);
	m_Y->Thaw();


	for( size_t i=0;i<m_names.size();i++ )
		m_Y->SelectRowInCol( i, 0, g.Y.Index( m_names[i] ) != wxNOT_FOUND );

	m_type->SetSelection( g.Type );
	m_title->ChangeValue( g.Title );
	m_xlabel->ChangeValue( g.XLabel );
	m_ylabel->ChangeValue( g.YLabel );
	m_scale->SetValue( (int)(g.FontScale*10) );
	m_font->SetSelection( g.FontFace );
	m_size->SetValue( g.Size );
	m_coarse->SetValue( g.CoarseGrid );
	m_fine->SetValue( g.FineGrid );
	m_showLegend->SetValue( g.ShowLegend );
	m_legendPos->SetSelection( g.LegendPos );

	Enable( true );
	m_legendPos->Enable( m_showLegend->GetValue() );
	m_Y->ExpandSelections();
}

void UncertaintiesProperties::Get( Uncertainties &g )
{
	for( size_t i=0;i<m_names.size();i++)
	{
		if ( g.Y.Index( m_names[i] ) != wxNOT_FOUND && !m_Y->IsRowSelected( i, 0 ) )
			g.Y.Remove( m_names[i] );

		if ( m_Y->IsRowSelected( i, 0 ) && g.Y.Index( m_names[i] ) == wxNOT_FOUND )
			g.Y.Add( m_names[i] );
	}

	g.Type = m_type->GetSelection();
	g.Title = m_title->GetValue();
	g.XLabel = m_xlabel->GetValue();
	g.YLabel = m_ylabel->GetValue();
	g.FontScale = ((double)m_scale->GetValue())/10.0;
	g.FontFace = m_font->GetSelection();
	g.Size = m_size->GetValue();
	g.CoarseGrid = m_coarse->GetValue();
	g.FineGrid = m_fine->GetValue();
	g.ShowLegend = m_showLegend->GetValue();
	g.LegendPos = m_legendPos->GetSelection();
}

void UncertaintiesProperties::SendChangeEvent()
{
	wxCommandEvent e( wxEVT_Uncertainties_PROPERTY_CHANGE, GetId() );
	e.SetEventObject( this );
	GetEventHandler()->ProcessEvent( e );
}

void UncertaintiesProperties::OnEdit(wxCommandEvent &)
{
	SendChangeEvent();
	m_legendPos->Enable(m_showLegend->GetValue());
}

void UncertaintiesProperties::OnSearch(wxCommandEvent &)
{
	m_Y->Filter( m_srch->GetValue() );
	m_Y->ExpandAll();
}

void UncertaintiesProperties::OnSlider( wxScrollEvent & )
{
	SendChangeEvent();
}


enum { ID_CREATE_Uncertainties = wxID_HIGHEST+466, ID_DELETE_Uncertainties,
	ID_Uncertainties_PROPS };

BEGIN_EVENT_TABLE(UncertaintiesViewer, wxPanel)
	EVT_BUTTON( ID_CREATE_Uncertainties, UncertaintiesViewer::OnCommand )
	EVT_BUTTON( ID_DELETE_Uncertainties, UncertaintiesViewer::OnCommand )
	EVT_Uncertainties_PROPERTY_CHANGE( ID_Uncertainties_PROPS, UncertaintiesViewer::OnCommand )
	EVT_Uncertainties_SELECT( wxID_ANY, UncertaintiesViewer::OnUncertaintiesSelect )
END_EVENT_TABLE()


UncertaintiesViewer::UncertaintiesViewer(wxWindow *parent) : wxPanel(parent, wxID_ANY)
//	: wxSplitterWindow( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE|wxSP_NOBORDER )
{
	m_sim = 0;
	m_current = 0;

	wxBoxSizer *main_sizer = new wxBoxSizer(wxHORIZONTAL);
/*	wxSplitterWindow *splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE | wxSP_NOBORDER | wxSP_3DSASH );
	main_sizer->Add(splitter, 1, wxBOTTOM | wxLEFT | wxEXPAND, 0);

	m_lpanel = new wxPanel(splitter);
	wxBoxSizer *sizer_tools = new wxBoxSizer( wxHORIZONTAL );
	sizer_tools->Add( new wxMetroButton( m_lpanel, ID_CREATE_Uncertainties, "Create Uncertainties" ), 1, wxALL|wxEXPAND, 0 );
	sizer_tools->Add( m_delButton = new wxMetroButton( m_lpanel, ID_DELETE_Uncertainties, "Delete" ), 0, wxALL|wxEXPAND, 0 );
		
	m_props = new UncertaintiesProperties( m_lpanel, ID_Uncertainties_PROPS );

	wxBoxSizer *sizer_left = new wxBoxSizer( wxVERTICAL );
	sizer_left->Add( sizer_tools, 0, wxALL|wxEXPAND, 0 );
	sizer_left->Add( m_props, 1, wxALL|wxEXPAND, 0 );


	m_lpanel->SetSizer( sizer_left );
*/
	m_layout = new wxSnapLayout(this, wxID_ANY);
	m_layout->SetShowSizing( true );
//	splitter->SetMinimumPaneSize( 50 );
//	splitter->SplitVertically( m_lpanel, m_layout, (int)(260*wxGetScreenHDScale()) );
	main_sizer->Add(m_layout, 1, wxBOTTOM | wxLEFT | wxEXPAND, 0);
	SetSizer(main_sizer);
	main_sizer->SetSizeHints(this);
	
//	UpdateProperties();
}

UncertaintiesCtrl *UncertaintiesViewer::CreateNewUncertainties()
{
	UncertaintiesCtrl *gc = new UncertaintiesCtrl( m_layout, wxID_ANY );
	m_Uncertainties.push_back( gc );
	m_layout->Add( gc );
	return gc;
}

void UncertaintiesViewer::DeleteUncertainties( UncertaintiesCtrl *gc )
{
	std::vector<UncertaintiesCtrl*>::iterator it = std::find( m_Uncertainties.begin(), m_Uncertainties.end(), gc );
	if ( it != m_Uncertainties.end() )
	{
		if ( m_current == *it )
			m_current = 0;

		m_layout->Delete( *it );
		m_Uncertainties.erase( it );
	}
}

void UncertaintiesViewer::DeleteAll()
{
		for (std::vector<UncertaintiesCtrl*>::iterator it = m_Uncertainties.begin();
			it != m_Uncertainties.end();
			++it)
		{
			m_layout->Delete(*it);
			m_Uncertainties.erase(it);
		}
	m_current = 0;
}

void UncertaintiesViewer::SetUncertainties( std::vector<Uncertainties> &gl )
{
	DeleteAll();
	
	for( size_t i=0;i<gl.size();i++ )
	{
		UncertaintiesCtrl *gc = CreateNewUncertainties();
		gc->SetUncertainties(gl[i]);
	}
}

void UncertaintiesViewer::GetUncertainties( std::vector<Uncertainties> &gl )
{
	gl.clear();
	gl.reserve( m_Uncertainties.size() );
	for( size_t i=0;i<m_Uncertainties.size();i++ )
		gl.push_back( m_Uncertainties[i]->GetUncertainties() );
}

	
void UncertaintiesViewer::Setup( Simulation *sim )
{
	m_sim = sim;

	if ( !m_sim ) return;
	/*
	for (std::vector<UncertaintiesCtrl*>::iterator it = m_Uncertainties.begin();
		it != m_Uncertainties.end();
		++it)
	{
		Uncertainties g = (*it)->GetUncertainties();
		if (g.Title == "Figure2")
			(*it)->Figure2(m_sim);
		else if (g.Title == "Figure5")
			(*it)->Figure5(m_sim);
	}
	*/


	
	std::vector<UncertaintiesCtrl*> remove_list;

	for( std::vector<UncertaintiesCtrl*>::iterator it = m_Uncertainties.begin();
		it != m_Uncertainties.end();
		++it )
	{
		Uncertainties g = (*it)->GetUncertainties();
		if ((*it)->Display( m_sim, g ) < 0) remove_list.push_back(*it);
	}


	while (remove_list.size() > 0)
	{
		DeleteUncertainties(remove_list.back());
		remove_list.pop_back();
	}
	
}


UncertaintiesCtrl *UncertaintiesViewer::Current()
{
	return m_current;
}

void UncertaintiesViewer::UpdateUncertainties()
{
	if( !m_current || !m_sim) return;
	Uncertainties g = m_current->GetUncertainties();
//	m_props->Get( g );
	m_current->Display( m_sim, g );
}

void UncertaintiesViewer::OnCommand( wxCommandEvent &evt )
{
	if ( evt.GetId() == ID_CREATE_Uncertainties )
	{
		SetCurrent( CreateNewUncertainties() );
	}
	else if ( evt.GetId() == ID_DELETE_Uncertainties )
	{
		if ( m_current != 0 )
		{
			DeleteUncertainties( m_current );
			m_current = 0;
			SetCurrent( 0 );
		}
	}
	else if ( evt.GetId() == ID_Uncertainties_PROPS )
		UpdateUncertainties();
}

void UncertaintiesViewer::OnUncertaintiesSelect( wxCommandEvent &evt )
{
	if ( UncertaintiesCtrl *gc = dynamic_cast<UncertaintiesCtrl*>( evt.GetEventObject() ) )
		SetCurrent( gc );
}

void UncertaintiesViewer::SetCurrent(UncertaintiesCtrl *gc)
{
	if (m_current)
	{
		m_layout->ClearHighlights();
		m_current = 0;
	}

	m_current = gc;

	if (m_current)
		m_layout->Highlight(m_current);

}
