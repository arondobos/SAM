#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <iostream>

#include <ssc/sscapi.h>

#include "SAM_api.h"
#include "ErrorHandler.h"
#include "SAM_Battwatts.h"

SAM_EXPORT SAM_Battwatts SAM_Battwatts_construct(const char* def, SAM_error* err){
	SAM_Battwatts result = nullptr;
	translateExceptions(err, [&]{
		result = ssc_data_create();
	});
	return result;
}

SAM_EXPORT int SAM_Battwatts_execute(SAM_Battwatts data, int verbosity, SAM_error* err){
	int n_err = 0;
	translateExceptions(err, [&]{
		n_err += SAM_module_exec("battwatts", data, verbosity, err);
	});
	return n_err;
}


SAM_EXPORT void SAM_Battwatts_destruct(SAM_Battwatts system)
{
	ssc_data_free(system);
}

SAM_EXPORT void SAM_Battwatts_PVWatts_system_use_lifetime_output_nset(SAM_Battwatts ptr, double number, SAM_error *err){
	translateExceptions(err, [&]{
		ssc_data_set_number(ptr, "system_use_lifetime_output", number);
	});
}

SAM_EXPORT void SAM_Battwatts_FinancialAnalysisParameters_analysis_period_nset(SAM_Battwatts ptr, double number, SAM_error *err){
	translateExceptions(err, [&]{
		ssc_data_set_number(ptr, "analysis_period", number);
	});
}

SAM_EXPORT void SAM_Battwatts_BatteryModelSimple_batt_simple_chemistry_nset(SAM_Battwatts ptr, double number, SAM_error *err){
	translateExceptions(err, [&]{
		ssc_data_set_number(ptr, "batt_simple_chemistry", number);
	});
}

SAM_EXPORT void SAM_Battwatts_BatteryModelSimple_batt_simple_dispatch_nset(SAM_Battwatts ptr, double number, SAM_error *err){
	translateExceptions(err, [&]{
		ssc_data_set_number(ptr, "batt_simple_dispatch", number);
	});
}

SAM_EXPORT void SAM_Battwatts_BatteryModelSimple_batt_simple_enable_nset(SAM_Battwatts ptr, double number, SAM_error *err){
	translateExceptions(err, [&]{
		ssc_data_set_number(ptr, "batt_simple_enable", number);
	});
}

SAM_EXPORT void SAM_Battwatts_BatteryModelSimple_batt_simple_kw_nset(SAM_Battwatts ptr, double number, SAM_error *err){
	translateExceptions(err, [&]{
		ssc_data_set_number(ptr, "batt_simple_kw", number);
	});
}

SAM_EXPORT void SAM_Battwatts_BatteryModelSimple_batt_simple_kwh_nset(SAM_Battwatts ptr, double number, SAM_error *err){
	translateExceptions(err, [&]{
		ssc_data_set_number(ptr, "batt_simple_kwh", number);
	});
}

SAM_EXPORT void SAM_Battwatts_BatteryModelSimple_batt_simple_meter_position_nset(SAM_Battwatts ptr, double number, SAM_error *err){
	translateExceptions(err, [&]{
		ssc_data_set_number(ptr, "batt_simple_meter_position", number);
	});
}

SAM_EXPORT void SAM_Battwatts_Common_ac_aset(SAM_Battwatts ptr, double* arr, int length, SAM_error *err){
	translateExceptions(err, [&]{
		ssc_data_set_array(ptr, "ac", arr, length);
	});
}

SAM_EXPORT void SAM_Battwatts_Common_dc_aset(SAM_Battwatts ptr, double* arr, int length, SAM_error *err){
	translateExceptions(err, [&]{
		ssc_data_set_array(ptr, "dc", arr, length);
	});
}

SAM_EXPORT void SAM_Battwatts_Common_inverter_efficiency_nset(SAM_Battwatts ptr, double number, SAM_error *err){
	translateExceptions(err, [&]{
		ssc_data_set_number(ptr, "inverter_efficiency", number);
	});
}

SAM_EXPORT void SAM_Battwatts_Common_inverter_model_nset(SAM_Battwatts ptr, double number, SAM_error *err){
	translateExceptions(err, [&]{
		ssc_data_set_number(ptr, "inverter_model", number);
	});
}

SAM_EXPORT void SAM_Battwatts_ElectricLoadOther_load_aset(SAM_Battwatts ptr, double* arr, int length, SAM_error *err){
	translateExceptions(err, [&]{
		ssc_data_set_array(ptr, "load", arr, length);
	});
}

SAM_EXPORT double SAM_Battwatts_PVWatts_system_use_lifetime_output_nget(SAM_Battwatts ptr, SAM_error *err){
	double result;
	translateExceptions(err, [&]{
	if (!ssc_data_get_number(ptr, "system_use_lifetime_output", &result))
		make_access_error("SAM_Battwatts", "system_use_lifetime_output");
	});
	return result;
}



SAM_EXPORT double SAM_Battwatts_FinancialAnalysisParameters_analysis_period_nget(SAM_Battwatts ptr, SAM_error *err){
	double result;
	translateExceptions(err, [&]{
	if (!ssc_data_get_number(ptr, "analysis_period", &result))
		make_access_error("SAM_Battwatts", "analysis_period");
	});
	return result;
}



SAM_EXPORT double SAM_Battwatts_BatteryModelSimple_batt_simple_chemistry_nget(SAM_Battwatts ptr, SAM_error *err){
	double result;
	translateExceptions(err, [&]{
	if (!ssc_data_get_number(ptr, "batt_simple_chemistry", &result))
		make_access_error("SAM_Battwatts", "batt_simple_chemistry");
	});
	return result;
}



SAM_EXPORT double SAM_Battwatts_BatteryModelSimple_batt_simple_dispatch_nget(SAM_Battwatts ptr, SAM_error *err){
	double result;
	translateExceptions(err, [&]{
	if (!ssc_data_get_number(ptr, "batt_simple_dispatch", &result))
		make_access_error("SAM_Battwatts", "batt_simple_dispatch");
	});
	return result;
}



SAM_EXPORT double SAM_Battwatts_BatteryModelSimple_batt_simple_enable_nget(SAM_Battwatts ptr, SAM_error *err){
	double result;
	translateExceptions(err, [&]{
	if (!ssc_data_get_number(ptr, "batt_simple_enable", &result))
		make_access_error("SAM_Battwatts", "batt_simple_enable");
	});
	return result;
}



SAM_EXPORT double SAM_Battwatts_BatteryModelSimple_batt_simple_kw_nget(SAM_Battwatts ptr, SAM_error *err){
	double result;
	translateExceptions(err, [&]{
	if (!ssc_data_get_number(ptr, "batt_simple_kw", &result))
		make_access_error("SAM_Battwatts", "batt_simple_kw");
	});
	return result;
}



SAM_EXPORT double SAM_Battwatts_BatteryModelSimple_batt_simple_kwh_nget(SAM_Battwatts ptr, SAM_error *err){
	double result;
	translateExceptions(err, [&]{
	if (!ssc_data_get_number(ptr, "batt_simple_kwh", &result))
		make_access_error("SAM_Battwatts", "batt_simple_kwh");
	});
	return result;
}



SAM_EXPORT double SAM_Battwatts_BatteryModelSimple_batt_simple_meter_position_nget(SAM_Battwatts ptr, SAM_error *err){
	double result;
	translateExceptions(err, [&]{
	if (!ssc_data_get_number(ptr, "batt_simple_meter_position", &result))
		make_access_error("SAM_Battwatts", "batt_simple_meter_position");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Common_ac_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "ac", length);
	if (!result)
		make_access_error("SAM_Battwatts", "ac");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Common_dc_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "dc", length);
	if (!result)
		make_access_error("SAM_Battwatts", "dc");
	});
	return result;
}



SAM_EXPORT double SAM_Battwatts_Common_inverter_efficiency_nget(SAM_Battwatts ptr, SAM_error *err){
	double result;
	translateExceptions(err, [&]{
	if (!ssc_data_get_number(ptr, "inverter_efficiency", &result))
		make_access_error("SAM_Battwatts", "inverter_efficiency");
	});
	return result;
}



SAM_EXPORT double SAM_Battwatts_Common_inverter_model_nget(SAM_Battwatts ptr, SAM_error *err){
	double result;
	translateExceptions(err, [&]{
	if (!ssc_data_get_number(ptr, "inverter_model", &result))
		make_access_error("SAM_Battwatts", "inverter_model");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_ElectricLoadOther_load_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "load", length);
	if (!result)
		make_access_error("SAM_Battwatts", "load");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_annual_export_to_grid_energy_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "annual_export_to_grid_energy", length);
	if (!result)
		make_access_error("SAM_Battwatts", "annual_export_to_grid_energy");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_annual_import_to_grid_energy_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "annual_import_to_grid_energy", length);
	if (!result)
		make_access_error("SAM_Battwatts", "annual_import_to_grid_energy");
	});
	return result;
}



SAM_EXPORT double SAM_Battwatts_Outputs_average_battery_conversion_efficiency_nget(SAM_Battwatts ptr, SAM_error *err){
	double result;
	translateExceptions(err, [&]{
	if (!ssc_data_get_number(ptr, "average_battery_conversion_efficiency", &result))
		make_access_error("SAM_Battwatts", "average_battery_conversion_efficiency");
	});
	return result;
}



SAM_EXPORT double SAM_Battwatts_Outputs_average_battery_roundtrip_efficiency_nget(SAM_Battwatts ptr, SAM_error *err){
	double result;
	translateExceptions(err, [&]{
	if (!ssc_data_get_number(ptr, "average_battery_roundtrip_efficiency", &result))
		make_access_error("SAM_Battwatts", "average_battery_roundtrip_efficiency");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_DOD_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_DOD", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_DOD");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_DOD_cycle_average_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_DOD_cycle_average", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_DOD_cycle_average");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_I_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_I", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_I");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_SOC_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_SOC", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_SOC");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_annual_charge_energy_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_annual_charge_energy", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_annual_charge_energy");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_annual_charge_from_grid_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_annual_charge_from_grid", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_annual_charge_from_grid");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_annual_charge_from_pv_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_annual_charge_from_pv", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_annual_charge_from_pv");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_annual_discharge_energy_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_annual_discharge_energy", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_annual_discharge_energy");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_annual_energy_loss_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_annual_energy_loss", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_annual_energy_loss");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_annual_energy_system_loss_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_annual_energy_system_loss", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_annual_energy_system_loss");
	});
	return result;
}



SAM_EXPORT double SAM_Battwatts_Outputs_batt_bank_installed_capacity_nget(SAM_Battwatts ptr, SAM_error *err){
	double result;
	translateExceptions(err, [&]{
	if (!ssc_data_get_number(ptr, "batt_bank_installed_capacity", &result))
		make_access_error("SAM_Battwatts", "batt_bank_installed_capacity");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_bank_replacement_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_bank_replacement", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_bank_replacement");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_capacity_percent_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_capacity_percent", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_capacity_percent");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_capacity_percent_calendar_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_capacity_percent_calendar", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_capacity_percent_calendar");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_capacity_percent_cycle_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_capacity_percent_cycle", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_capacity_percent_cycle");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_capacity_thermal_percent_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_capacity_thermal_percent", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_capacity_thermal_percent");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_conversion_loss_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_conversion_loss", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_conversion_loss");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_cost_to_cycle_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_cost_to_cycle", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_cost_to_cycle");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_cycles_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_cycles", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_cycles");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_dispatch_sched_mget(SAM_Battwatts ptr, int* nrows, int* ncols, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_matrix(ptr, "batt_dispatch_sched", nrows, ncols);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_dispatch_sched");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_power_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_power", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_power");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_power_target_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_power_target", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_power_target");
	});
	return result;
}



SAM_EXPORT double SAM_Battwatts_Outputs_batt_pv_charge_percent_nget(SAM_Battwatts ptr, SAM_error *err){
	double result;
	translateExceptions(err, [&]{
	if (!ssc_data_get_number(ptr, "batt_pv_charge_percent", &result))
		make_access_error("SAM_Battwatts", "batt_pv_charge_percent");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_q0_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_q0", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_q0");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_q1_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_q1", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_q1");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_q2_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_q2", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_q2");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_qmax_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_qmax", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_qmax");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_qmaxI_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_qmaxI", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_qmaxI");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_qmax_thermal_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_qmax_thermal", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_qmax_thermal");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_revenue_charge_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_revenue_charge", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_revenue_charge");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_revenue_clipcharge_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_revenue_clipcharge", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_revenue_clipcharge");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_revenue_discharge_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_revenue_discharge", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_revenue_discharge");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_revenue_gridcharge_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_revenue_gridcharge", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_revenue_gridcharge");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_system_loss_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_system_loss", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_system_loss");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_temperature_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_temperature", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_temperature");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_to_grid_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_to_grid", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_to_grid");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_to_load_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_to_load", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_to_load");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_voltage_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_voltage", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_voltage");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_batt_voltage_cell_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "batt_voltage_cell", length);
	if (!result)
		make_access_error("SAM_Battwatts", "batt_voltage_cell");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_fuelcell_to_batt_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "fuelcell_to_batt", length);
	if (!result)
		make_access_error("SAM_Battwatts", "fuelcell_to_batt");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_gen_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "gen", length);
	if (!result)
		make_access_error("SAM_Battwatts", "gen");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_grid_power_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "grid_power", length);
	if (!result)
		make_access_error("SAM_Battwatts", "grid_power");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_grid_power_target_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "grid_power_target", length);
	if (!result)
		make_access_error("SAM_Battwatts", "grid_power_target");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_grid_to_batt_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "grid_to_batt", length);
	if (!result)
		make_access_error("SAM_Battwatts", "grid_to_batt");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_grid_to_load_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "grid_to_load", length);
	if (!result)
		make_access_error("SAM_Battwatts", "grid_to_load");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_market_sell_rate_series_yr1_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "market_sell_rate_series_yr1", length);
	if (!result)
		make_access_error("SAM_Battwatts", "market_sell_rate_series_yr1");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_monthly_batt_to_grid_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "monthly_batt_to_grid", length);
	if (!result)
		make_access_error("SAM_Battwatts", "monthly_batt_to_grid");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_monthly_batt_to_load_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "monthly_batt_to_load", length);
	if (!result)
		make_access_error("SAM_Battwatts", "monthly_batt_to_load");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_monthly_grid_to_batt_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "monthly_grid_to_batt", length);
	if (!result)
		make_access_error("SAM_Battwatts", "monthly_grid_to_batt");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_monthly_grid_to_load_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "monthly_grid_to_load", length);
	if (!result)
		make_access_error("SAM_Battwatts", "monthly_grid_to_load");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_monthly_pv_to_batt_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "monthly_pv_to_batt", length);
	if (!result)
		make_access_error("SAM_Battwatts", "monthly_pv_to_batt");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_monthly_pv_to_grid_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "monthly_pv_to_grid", length);
	if (!result)
		make_access_error("SAM_Battwatts", "monthly_pv_to_grid");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_monthly_pv_to_load_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "monthly_pv_to_load", length);
	if (!result)
		make_access_error("SAM_Battwatts", "monthly_pv_to_load");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_pv_to_batt_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "pv_to_batt", length);
	if (!result)
		make_access_error("SAM_Battwatts", "pv_to_batt");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_pv_to_grid_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "pv_to_grid", length);
	if (!result)
		make_access_error("SAM_Battwatts", "pv_to_grid");
	});
	return result;
}



SAM_EXPORT double* SAM_Battwatts_Outputs_pv_to_load_aget(SAM_Battwatts ptr, int* length, SAM_error *err){
	double* result = nullptr;
	translateExceptions(err, [&]{
	result = ssc_data_get_array(ptr, "pv_to_load", length);
	if (!result)
		make_access_error("SAM_Battwatts", "pv_to_load");
	});
	return result;
}



