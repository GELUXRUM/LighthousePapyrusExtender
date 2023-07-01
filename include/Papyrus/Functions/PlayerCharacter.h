#pragma once

namespace Papyrus::PlayerCharacter
{
	// this works, but the menu doesn't get updated/refreshed automatically
	// probably requires to RE the FavoritesMenu class into CLib, but I'm lazy
	// until then this will just stay here and won't be available in-game
	inline void ClearFavourites(IVM& a_vm, VMStackID a_stackID, std::monostate)
	{
		if (const auto player = RE::PlayerCharacter::GetSingleton(); player) {
			auto playerInventory = player->inventoryList->data;
			for (auto currentItem : playerInventory) {
				if (currentItem.stackData.get()->extra->IsFavorite()) {
					currentItem.stackData.get()->extra->ClearFavorite();
				}
			}
			return;
		}

		a_vm.PostError("Player is None", a_stackID, Severity::kError);
		return;
	}

	inline uint32_t GetFollowerCount(IVM& a_vm, VMStackID a_stackID, std::monostate)
	{
		if (const auto player = RE::PlayerCharacter::GetSingleton(); player) {
			return player->teammateCount;
		}

		a_vm.PostError("Player is None", a_stackID, Severity::kError);
		return 0;
	}

	inline bool IsInGodMode(IVM& a_vm, VMStackID a_stackID, std::monostate)
	{
		if (const auto player = RE::PlayerCharacter::GetSingleton(); player) {
			return player->IsGodMode();
		}

		a_vm.PostError("Player is None", a_stackID, Severity::kError);
		return false;
	}

	inline bool IsImmortal(IVM& a_vm, VMStackID a_stackID, std::monostate)
	{
		if (const auto player = RE::PlayerCharacter::GetSingleton(); player) {
			return player->IsImmortal();
		}

		a_vm.PostError("Player is None", a_stackID, Severity::kError);
		return false;
	}

	inline bool IsPipboyLightOn(IVM& a_vm, VMStackID a_stackID, std::monostate)
	{
		if (const auto player = RE::PlayerCharacter::GetSingleton(); player) {
			return player->IsPipboyLightOn();
		}

		a_vm.PostError("Player is None", a_stackID, Severity::kError);
		return false;
	}

	inline bool IsPlayerDetectedByHostile(std::monostate)
	{
		// TODO: add error logger
		return (RE::PlayerCharacter::GetSingleton() != nullptr) ? RE::PlayerCharacter::GetSingleton()->hostileDetection : false;
	}

	inline bool IsThirdPersonModelShown(IVM& a_vm, VMStackID a_stackID, std::monostate)
	{
		if (const auto player = RE::PlayerCharacter::GetSingleton(); player) {
			return player->is3rdPersonModelShown;
		}

		a_vm.PostError("Player is None", a_stackID, Severity::kError);
		return 0;
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "ClearFavourites", ClearFavourites, true);
		a_vm.BindNativeMethod("Lighthouse", "GetFollowerCount", GetFollowerCount, true);
		a_vm.BindNativeMethod("Lighthouse", "IsInGodMode", IsInGodMode, true);
		a_vm.BindNativeMethod("Lighthouse", "IsImmortal", IsImmortal, true);
		a_vm.BindNativeMethod("Lighthouse", "IsPipboyLightOn", IsPipboyLightOn, true);
		a_vm.BindNativeMethod("Lighthouse", "IsPlayerDetectedByHostile", IsPlayerDetectedByHostile, true);
		a_vm.BindNativeMethod("Lighthouse", "IsThirdPersonModelShown", IsThirdPersonModelShown, true);

		logger::info("PlayerCharacter functions registered.");
	}
}
