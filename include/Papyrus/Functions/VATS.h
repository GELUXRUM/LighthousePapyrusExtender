#pragma once

namespace Papyrus::VATS
{
	inline float GetVATSCriticalCharge(IVM& a_vm, VMStackID a_stackID, std::monostate)
	{
		if (const auto player = RE::PlayerCharacter::GetSingleton(); player) {			
			return player->vatsCriticalCharge;
		}

		a_vm.PostError("Player is None", a_stackID, Severity::kError);
		return 0.0f;
	}

	inline void SetVATSCriticalCharge(IVM& a_vm, VMStackID a_stackID, std::monostate,
		float a_charge)
	{
		if (const auto player = RE::PlayerCharacter::GetSingleton(); player){
			if (a_charge < 0 || a_charge > 100) {
				a_vm.PostError("Value is outside the allowable range", a_stackID, Severity::kError);
				return;
			}

			player->vatsCriticalCharge = a_charge;

			return;
		}

		a_vm.PostError("Player is None", a_stackID, Severity::kError);
		return;
	}

	inline void SetVATSCriticalCount(IVM& a_vm, VMStackID a_stackID, std::monostate,
		std::uint32_t a_count)
	{
		if (const auto player = RE::PlayerCharacter::GetSingleton(); player) {
			if (a_count < 0) {
				a_vm.PostError("Value cannot be negative", a_stackID, Severity::kError);
				return;
			}

			player->SetVATSCriticalCount(a_count);

			return;
		}

		a_vm.PostError("Player is None", a_stackID, Severity::kError);
		return;
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "GetVATSCriticalCharge", GetVATSCriticalCharge, true);
		a_vm.BindNativeMethod("Lighthouse", "SetVATSCriticalCharge", SetVATSCriticalCharge, true);
		a_vm.BindNativeMethod("Lighthouse", "SetVATSCriticalCount", SetVATSCriticalCount, true);

		logger::info("VATS functions registered.");
	}
}
