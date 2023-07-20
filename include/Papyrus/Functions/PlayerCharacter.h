#pragma once

namespace Papyrus::PlayerCharacter
{
	inline std::vector<RE::TESObjectREFR*> GetAllMapMarkers(IVM& a_vm, VMStackID a_stackID, std::monostate)
	{
		std::vector<RE::TESObjectREFR*> result;

		if (const auto player = RE::PlayerCharacter::GetSingleton(); player) {
			auto mapMarkerHandles = player->currentMapMarkers;
			for (auto currentMapMarker : mapMarkerHandles) {
				result.push_back(currentMapMarker.get().get());
			}
			return result;
		}

		a_vm.PostError("Player is None", a_stackID, Severity::kError);
		return result;
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

	inline void TogglePipBoyLight(IVM& a_vm, VMStackID a_stackID, std::monostate)
	{
		if (const auto player = RE::PlayerCharacter::GetSingleton(); player) {
			player->TogglePipBoyLight();
			return;
		}

		a_vm.PostError("Player is None", a_stackID, Severity::kError);
		return;
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "GetAllMapMarkers", GetAllMapMarkers, true);
		a_vm.BindNativeMethod("Lighthouse", "GetFollowerCount", GetFollowerCount, true);
		a_vm.BindNativeMethod("Lighthouse", "IsInGodMode", IsInGodMode, true);
		a_vm.BindNativeMethod("Lighthouse", "IsImmortal", IsImmortal, true);
		a_vm.BindNativeMethod("Lighthouse", "IsPipboyLightOn", IsPipboyLightOn, true);
		a_vm.BindNativeMethod("Lighthouse", "IsPlayerDetectedByHostile", IsPlayerDetectedByHostile, true);
		a_vm.BindNativeMethod("Lighthouse", "IsThirdPersonModelShown", IsThirdPersonModelShown, true);
		a_vm.BindNativeMethod("Lighthouse", "TogglePipBoyLight", TogglePipBoyLight, true);

		logger::info("PlayerCharacter functions registered.");
	}
}
