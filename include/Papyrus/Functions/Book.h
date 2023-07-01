#pragma once

namespace Papyrus::Book
{
	inline RE::BGSNote* GetCurrentHolotape(IVM& a_vm, VMStackID a_stackID, std::monostate)
	{
		const auto player = RE::PlayerCharacter::GetSingleton();

		if (!player) {
			a_vm.PostError("Player is None", a_stackID, Severity::kError);
			return nullptr;	
		}
		
		return player->currHolotape;
	}

	inline bool IsHolotapePlaying(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSNote* a_holotape)
	{
		const auto player = RE::PlayerCharacter::GetSingleton();

		if (!player) {
			a_vm.PostError("Player is None", a_stackID, Severity::kError);
			return false;
		}

		if (!a_holotape) {
			a_vm.PostError("Holotape is None", a_stackID, Severity::kError);
			return false;
		}

		return player->IsHolotapePlaying(a_holotape);
	}

	inline void PauseHolotape(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSNote* a_holotape)
	{
		const auto player = RE::PlayerCharacter::GetSingleton();

		if (!player) {
			a_vm.PostError("Player is None", a_stackID, Severity::kError);
			return;
		}

		if (!a_holotape) {
			a_vm.PostError("Holotape is None", a_stackID, Severity::kError);
			return;
		}

		if (!(player->IsHolotapePlaying(a_holotape))) {
			a_vm.PostError("Can't pause the Holotape because it's not playing", a_stackID, Severity::kError);
			return;
		}

		player->PauseHolotape(a_holotape);
		
		return;
	}

	inline void PlayHolotape(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSNote* a_holotape)
	{
		const auto player = RE::PlayerCharacter::GetSingleton();

		if (!player) {
			a_vm.PostError("Player is None", a_stackID, Severity::kError);
			return;
		}

		if (!a_holotape) {
			a_vm.PostError("Holotape is None", a_stackID, Severity::kError);
			return;
		}

		player->PlayHolotape(a_holotape);

		return;
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "GetCurrentHolotape", GetCurrentHolotape, true);
		a_vm.BindNativeMethod("Lighthouse", "IsHolotapePlaying", IsHolotapePlaying, true);
		a_vm.BindNativeMethod("Lighthouse", "PauseHolotape", PauseHolotape, true);
		a_vm.BindNativeMethod("Lighthouse", "PlayHolotape", PlayHolotape, true);

		logger::info("Book functions registered.");
	}
}
