#pragma once

namespace Papyrus::Armor
{
	int32_t GetArmorHealth(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectARMO* a_armor)
	{
		if (!a_armor) {
			a_vm.PostError("Armor is None", a_stackID, Severity::kError);
			return -1;
		}

		auto armorData = a_armor->GetBaseInstanceData();

		return armorData->GetHealth();
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "GetArmorHealth", GetArmorHealth, true);

		logger::info("Armor functions registered.");
	}
}
