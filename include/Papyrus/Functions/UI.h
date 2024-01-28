#pragma once

namespace Papyrus::UI
{
	/*
	fPipboyEffectColorB=0.9705
fPipboyEffectColorG=1.0000
fPipboyEffectColorR=0.9705
iHUDColorB=247
iHUDColorG=255
iHUDColorR=247
	*/
	/*
	inline std::vector<std::uint32_t> GetHUDRGB(IVM& a_vm, VMStackID a_stackID, std::monostate)
	{
		std::vector<std::uint32_t> result;

		if (auto iniSetting = RE::INISettingCollection::GetSingleton(); iniSetting) {
			result.push_back(iniSetting->GetSetting("iHUDColorR"sv)->GetInt());
			result.push_back(iniSetting->GetSetting("iHUDColorG"sv)->GetInt());
			result.push_back(iniSetting->GetSetting("iHUDColorB"sv)->GetInt());
			return result;
		} else {
			a_vm.PostError("Unable to access INI settings", a_stackID, Severity::kError);
			return result;
		}
	}

	inline void SetHUDRGB(IVM& a_vm, VMStackID a_stackID, std::monostate,
		std::vector<std::uint32_t> a_rgb)
	{
		if (a_rgb.size() < 3) {
			a_vm.PostError("RGB array is empty", a_stackID, Severity::kError);
			return;
		}

		if (auto iniSetting = RE::INISettingCollection::GetSingleton(); iniSetting) {
			iniSetting->GetSetting("iHUDColorR")->SetInt(a_rgb[0]);
			iniSetting->GetSetting("iHUDColorG")->SetInt(a_rgb[1]);
			iniSetting->GetSetting("iHUDColorB")->SetInt(a_rgb[2]);
			return;
		} else {
			a_vm.PostError("Unable to access INI settings", a_stackID, Severity::kError);
			return;
		}
	}
	*/

	inline void UpdateBarterMenu(IVM& a_vm, VMStackID a_stackID, std::monostate,
		bool a_inContainer)
	{
		if (const auto UI = RE::UI::GetSingleton(); UI) {
			const auto barterMenu = UI->GetMenu<RE::BarterMenu>();
			if (!barterMenu) {
				a_vm.PostError("Not in BarterMenu", a_stackID, Severity::kError);
				return;
			}
			barterMenu->UpdateList(a_inContainer);
		}
		a_vm.PostError("Unable to obtain UserInterface", a_stackID, Severity::kError);
		return;
	}

	inline void UpdateContainerMenu(IVM& a_vm, VMStackID a_stackID, std::monostate,
		bool a_inContainer)
	{
		if (const auto UI = RE::UI::GetSingleton(); UI) {
			const auto containerMenu = UI->GetMenu<RE::ContainerMenu>();
			if (!containerMenu) {
				a_vm.PostError("Not in ContainerMenu", a_stackID, Severity::kError);
				return;
			}
			containerMenu->UpdateList(a_inContainer);
		}
		a_vm.PostError("Unable to obtain UserInterface", a_stackID, Severity::kError);
		return;
	}

	inline void Bind(IVM& a_vm)
	{
		//a_vm.BindNativeMethod("Lighthouse", "GetHUDRGB", GetHUDRGB, true);
		//a_vm.BindNativeMethod("Lighthouse", "SetHUDRGB", SetHUDRGB, true);
		a_vm.BindNativeMethod("Lighthouse", "UpdateBarterMenu", UpdateBarterMenu, true);
		a_vm.BindNativeMethod("Lighthouse", "UpdateContainerMenu", UpdateContainerMenu, true);

		logger::info("UI functions registered.");
	}
}
