#pragma once

namespace Papyrus::Weather
{
	inline RE::BSFixedString GetPrecipitationType(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESWeather* a_weather)
	{
		if (!a_weather) {
			a_vm.PostError("Weather is None", a_stackID, Severity::kError);
			return {};
		}

		if (!a_weather->precipitationData) {
			return "NULL";
		} else {
			return a_weather->precipitationData->GetFormEditorID();
		}
	}

	inline float GetWeatherFogData(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESWeather* a_weather,
		int a_dataIndex)
	{
		if (!a_weather) {
			a_vm.PostError("Weather is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		if (a_dataIndex < 0 || a_dataIndex > 17) {
			a_vm.PostError("Index value is outside the allowable range", a_stackID, Severity::kError);
			return 0.0f;
		}

		return a_weather->fogData[a_dataIndex];
	}

	inline void SetWeatherFogData(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESWeather* a_weather,
		int a_dataIndex,
		float a_value)
	{
		if (!a_weather) {
			a_vm.PostError("Weather is None", a_stackID, Severity::kError);
			return;
		}

		if (a_dataIndex < 0 || a_dataIndex > 17) {
			a_vm.PostError("Index value is outside the allowable range", a_stackID, Severity::kError);
			return;
		}

		a_weather->fogData[a_dataIndex] = a_value;
		return;
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "GetPrecipitationType", GetPrecipitationType, true);
		a_vm.BindNativeMethod("Lighthouse", "GetWeatherFogData", GetWeatherFogData, true);
		a_vm.BindNativeMethod("Lighthouse", "SetWeatherFogData", SetWeatherFogData, true);

		logger::info("Weather functions registered.");
	}
}
