#pragma once

#include "Papyrus/Utilities/ActorUtils.h"

namespace Papyrus::Actor
{
	inline bool AreHostileActorsInRange(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		std::uint32_t a_maxDistance)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		auto originPos = a_actor->GetPosition();

		const auto processLists = RE::ProcessLists::GetSingleton();
		if (!processLists) {
			a_vm.PostError("Unable to obtain list of Actors", a_stackID, Severity::kError);
			return false;
		}

		for (const auto& actorHandle : processLists->highActorHandles) {
			const auto actorPtr = actorHandle.get();
			const auto currentActor = actorPtr.get();

			if (!currentActor) {
				continue;
			}

			if (currentActor->IsDead(true)) {
				continue;
			}

			if (currentActor->GetHostileToActor(a_actor)) {
				if (originPos.GetDistance(currentActor->GetPosition()) <= a_maxDistance) {
					return true;
				}
			}
		}

		return false;
	}

	inline void DrinkPotion(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		RE::AlchemyItem* a_alchemyItem)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return;
		}

		if (!a_alchemyItem) {
			a_vm.PostError("AlchemyItem is None", a_stackID, Severity::kError);
			return;
		}

		a_actor->DrinkPotion(a_alchemyItem, 0);
		
		return;
	}

	inline void ExitCover(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return;
		}

		a_actor->ExitCover();

		return;
	}

	inline std::vector<RE::EffectSetting*> GetActiveEffects(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		bool a_includeInactive)
	{
		std::vector<RE::EffectSetting*> result;

		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return result;
		}

		const RE::BSTArray<RE::BSTSmartPointer<RE::ActiveEffect>> effectsList = a_actor->GetActiveEffectList()->data;
		
		if (effectsList.empty()) {
			a_vm.PostError("Actor has no active effects", a_stackID, Severity::kInfo);
			return result;
		}

		for (const auto& currentEffect : effectsList) {
											// this bit below looks so scuffed lmao
			if (auto mgef = currentEffect ? currentEffect->effect->effectSetting : nullptr; mgef) {
				if (!a_includeInactive && (currentEffect->flags.all(RE::ActiveEffect::Flags::kInactive) || currentEffect->flags.all(RE::ActiveEffect::Flags::kDispelled))) {
					continue;
				}
				result.push_back(mgef);
			}
		}

		return result;
	}

	inline std::vector<RE::TESFaction*> GetActorFactionsFromList(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		std::vector<RE::TESFaction*> a_factionList)
	{
		std::vector<RE::TESFaction*> result;

		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return result;
		}

		if (a_factionList.size() == 0) {
			a_vm.PostError("List has no factions", a_stackID, Severity::kInfo);
			return result;
		}

		for (auto currentFaction : a_factionList) {
			if (a_actor->IsInFaction(currentFaction) == true) {
				result.push_back(currentFaction);
			}
		}

		return result;
	}

	inline int GetActorGunState(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return -1;
		}

		return static_cast<std::uint32_t>(a_actor->gunState);
	}

	inline std::vector<RE::Actor*> GetActorsByVerticalDistance(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		std::uint32_t a_upDistance,
		std::uint32_t a_upntDistance,
		std::uint32_t a_maxRadius,
		bool a_includeDead)
	{
		std::vector<RE::Actor*> result;

		if (!a_ref) {
			a_vm.PostError("Ref is None", a_stackID, Severity::kError);
			return result;
		}

		float zPos{ a_ref->GetPositionZ() };
		float zPosMax{ zPos + a_upDistance };
		float zPosMin{ zPos - a_upntDistance };

		const auto processLists = RE::ProcessLists::GetSingleton();
		if (!processLists) {
			a_vm.PostError("Unable to obtain list of Actors", a_stackID, Severity::kError);
			return result;
		}

		for (const auto& actorHandle : processLists->highActorHandles) {
			const auto actorPtr = actorHandle.get();
			const auto currentActor = actorPtr.get();

			if (!currentActor) {
				continue;
			}

			if (!a_includeDead && currentActor->IsDead(true)) {
				continue;
			}

			if (a_ref->GetPosition().GetDistance(currentActor->GetPosition()) <= a_maxRadius) {
				// reuse zPos for efficiency
				zPos = currentActor->GetPositionZ();
				if (zPos >= zPosMin && zPos <= zPosMax) {
					result.push_back(currentActor);
				}
			}
		}

		return result;
	}

	inline std::vector<RE::Actor*> GetActorsInRange(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		std::uint32_t a_maxDistance,
		bool a_includeDead)
	{
		std::vector<RE::Actor*> result;

		if (!a_ref) {
			a_vm.PostError("Ref is None", a_stackID, Severity::kError);
			return result;
		}

		auto originPos{ a_ref->GetPosition() };

		const auto processLists = RE::ProcessLists::GetSingleton();
		if (!processLists) {
			a_vm.PostError("Unable to obtain list of Actors", a_stackID, Severity::kError);
			return result;
		}

		for (const auto& actorHandle : processLists->highActorHandles) {
			const auto actorPtr = actorHandle.get();
			const auto currentActor = actorPtr.get();

			if (!currentActor) {
				continue;
			}

			if (!a_includeDead && currentActor->IsDead(true)) {
				continue;
			}

			if (a_ref->GetPosition().GetDistance(currentActor->GetPosition()) <= a_maxDistance) {
				result.push_back(currentActor);
			}
		}

		return result;
	}

	inline std::vector<RE::Actor*> GetActorsTargetingActor(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		std::vector<RE::Actor*> result;

		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return result;
		}

		auto targetHandle = a_actor->GetHandle();

		if (const auto processLists = RE::ProcessLists::GetSingleton(); processLists){
			for (auto& actorHandle : processLists->highActorHandles) {
				const auto actorPtr = actorHandle.get();
				const auto currentActor = actorPtr.get();
				if (currentActor->IsInCombat() && currentActor->currentCombatTarget == targetHandle) {
					result.push_back(currentActor);
				}
			}
		}

		return result;
	}

	inline RE::TESForm* GetArmorFormOnBipedSlot(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		std::uint32_t a_bipedSlot)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return nullptr;
		}

		return a_actor->biped->object[a_bipedSlot].parent.object;
	}

	inline RE::Actor* GetClosestActorWithKeyword(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_ref,
		RE::BGSKeyword* a_keyword,
		bool a_ignorePlayer,
		bool a_includeDead)
	{
		if (!a_ref) {
			a_vm.PostError("Ref is None", a_stackID, Severity::kError);
			return nullptr;
		}

		if (!a_keyword) {
			a_vm.PostError("Keyword is None", a_stackID, Severity::kError);
			return nullptr;
		}

		auto originPos{ a_ref->GetPosition() };
		RE::Actor* closestActor{ nullptr };
		float smallestDistance = std::numeric_limits<float>::max();
		float currentDistance{ 0.0f };

		const auto processLists = RE::ProcessLists::GetSingleton();
		if (!processLists) {
			a_vm.PostError("Unable to obtain list of Actors", a_stackID, Severity::kError);
			return nullptr;
		}

		for (const auto& actorHandle : processLists->highActorHandles) {
			const auto actorPtr = actorHandle.get();
			const auto currentActor = actorPtr.get();

			if (!currentActor) {
				continue;
			}

			if (!a_includeDead && currentActor->IsDead(true)) {
				continue;
			}

			if (currentActor->HasKeyword(a_keyword) == false) {
				continue;
			}

			currentDistance = originPos.GetDistance(currentActor->GetPosition());
			if (currentDistance < smallestDistance) {
				smallestDistance = currentDistance;
				closestActor = currentActor;
			}
		}

		if (!a_ignorePlayer) {
			auto player = RE::PlayerCharacter::GetSingleton();
			if (originPos.GetDistance(player->GetPosition()) < smallestDistance) {
				closestActor = player;
			}
		}

		return closestActor;
	}

	inline RE::TESCombatStyle* GetCombatStyle(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return nullptr;
		}

		return a_actor->GetCombatStyle();
	}

	inline std::vector<RE::Actor*> GetCommandedActors(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		std::vector<RE::Actor*> result;
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return result;
		}

		if (const auto middleHigh = a_actor->currentProcess->middleHigh) {
			for (auto& commandedActorData : middleHigh->commandedActors) {
				const auto commandedActor = commandedActorData.commandedActor.get();
				if (commandedActor) {
					result.push_back(commandedActor.get());
				}
			}
		}

		return result;
	}

	inline RE::TESPackage* GetRunningPackage(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return nullptr;
		}

		auto currentProcess = a_actor->currentProcess;

		return currentProcess->GetPackageThatIsRunning();
	}

	inline float GetEncumbranceRate(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		auto actorValuePtr = RE::ActorValue::GetSingleton();
		auto carryWeight = a_actor->GetActorValue(*actorValuePtr->carryWeight);

		if (carryWeight < 1.0f) {
			carryWeight = 1;
		}

		auto inventoryWeight = a_actor->GetWeightInContainer();

		float encumbranceRate{ 100 * (inventoryWeight / carryWeight) };

		return encumbranceRate;
	}

	inline float GetEquippedWeight(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		return a_actor->equippedWeight;
	}

	inline std::vector<RE::Actor*> GetHighActorsByRace(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESRace* a_race,
		bool a_includeDead)
	{
		std::vector<RE::Actor*> result;

		if (!a_race) {
			a_vm.PostError("Race is None", a_stackID, Severity::kError);
			return result;
		}

		if (const auto processLists = RE::ProcessLists::GetSingleton(); processLists) {
			for (const auto& actorHandle : processLists->highActorHandles) {
				const auto actorPtr = actorHandle.get();
				const auto currentActor = actorPtr.get();
				if (currentActor->race == a_race) {
					if (a_includeDead == true) {
						result.push_back(currentActor);
					} else {
						if (!(currentActor->IsDead(true))) {
							result.push_back(currentActor);
						}
					}
				}
			}
		}

		return result;
	}

	inline std::vector<RE::Actor*> GetHighActorsHostileToActor(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		bool a_includeDead)
	{
		std::vector<RE::Actor*> result;

		if (a_actor) {
			if (const auto processLists = RE::ProcessLists::GetSingleton(); processLists) {
				for (const auto& actorHandle : processLists->highActorHandles) {
					const auto actorPtr = actorHandle.get();
					const auto currentActor = actorPtr.get();
					if (currentActor->GetHostileToActor(a_actor)) {
						if (a_includeDead == true) {
							result.push_back(currentActor);
						} else {
							if (!(currentActor->IsDead(true))) {
								result.push_back(currentActor);
							}
						}
					}
				}
			}

			return result;
		}

		a_vm.PostError("Actor is None", a_stackID, Severity::kError);
		return result;
	}

	inline std::vector<RE::Actor*> GetHighActorsInCombat(std::monostate)
	{
		std::vector<RE::Actor*> result;

		if (const auto processLists = RE::ProcessLists::GetSingleton(); processLists) {
			for (const auto& actorHandle : processLists->highActorHandles) {
				const auto actorPtr = actorHandle.get();
				const auto currentActor = actorPtr.get();
				if (currentActor->IsInCombat()) {
					result.push_back(currentActor);
				}
			}
		}

		return result;
	}

	inline std::vector<RE::Actor*> GetHighDeadActors(std::monostate,
		bool a_notEssential)
	{
		std::vector<RE::Actor*> result;

		if (const auto processLists = RE::ProcessLists::GetSingleton(); processLists) {
			for (const auto& actorHandle : processLists->highActorHandles) {
				const auto actorPtr = actorHandle.get();
				const auto currentActor = actorPtr.get();
				if (currentActor->IsDead(a_notEssential)) {
					result.push_back(currentActor);
				}
			}
		}

		return result;
	}

	inline std::vector<RE::Actor*> GetHostileActorsInRange(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		int a_maxDistance,
		bool a_includePlayer)
	{
		std::vector<RE::Actor*> result;

		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return result;
		}

		auto originPos = a_actor->GetPosition();

		const auto processLists = RE::ProcessLists::GetSingleton();
		if (!processLists) {
			a_vm.PostError("Unable to obtain list of Actors", a_stackID, Severity::kError);
			return result;
		}
		
		if (a_includePlayer) {
			RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
			if (a_actor == player) {
				result.push_back(player);
			} else if (a_actor->GetHostileToActor(player)) {
				if (originPos.GetDistance(player->GetPosition()) <= a_maxDistance) {
					result.push_back(player);
				}
			}
		}

		for (const auto& actorHandle : processLists->highActorHandles) {
			const auto actorPtr = actorHandle.get();
			const auto currentActor = actorPtr.get();

			if (!currentActor) {
				continue;
			}

			if (currentActor == a_actor) {
				continue;
			}

			if (currentActor->IsDead(true)) {
				continue;
			}

			if (currentActor->GetHostileToActor(a_actor) == false) {
				continue;
			}

			if (originPos.GetDistance(currentActor->GetPosition()) <= a_maxDistance) {
					result.push_back(currentActor);
			}
		}

		return result;
	}

	inline std::int32_t GetKnockState(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return -1;
		}

		return a_actor->knockState;
	}

	inline std::int32_t GetLifeState(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return -1;
		}

		return a_actor->lifeState;
	}

	inline bool GetOffersServices(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		return a_actor->GetOfferBarter();
	}

	inline float GetTimeDead(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		const auto currentProcess = a_actor->currentProcess;
		const auto timeOfDeath = currentProcess ? currentProcess->deathTime : 0.0f;

		if (timeOfDeath > 0.0f) {
			if (const auto calendar = RE::Calendar::GetSingleton(); calendar) {
				const auto g_gameDaysPassed = calendar->gameDaysPassed;
				return g_gameDaysPassed ? floorf(g_gameDaysPassed->value * 24.0f) - timeOfDeath : 0.0f;
			}
		}

		return 0.0f;
	}

	inline float GetTimeOfDeath(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		const auto currentProcess = a_actor->currentProcess;
		const auto timeOfDeath = currentProcess ? currentProcess->deathTime : 0.0f;

		return timeOfDeath > 0.0f ? timeOfDeath / 24.0f : 0.0f;
	}

	inline RE::TESObjectREFR* GetVendorContainerRef(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return nullptr;
		}

		if (RE::TESFaction* vendorFaction = a_actor->vendorFaction; vendorFaction) {
			if (RE::TESObjectREFR* vendorContainer = a_actor->vendorFaction->vendorData.merchantContainer; vendorContainer) {
				return vendorContainer;
			} else {
				a_vm.PostError("Actor has no vendor container", a_stackID, Severity::kError);
				return nullptr;
			}
		} else {
			a_vm.PostError("Actor has no vendor faction", a_stackID, Severity::kError);
			return nullptr;
		}
	}

	inline RE::TESFaction* GetVendorFaction(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return nullptr;
		}

		return a_actor->vendorFaction;
	}

	inline int GetWeaponAmmoCapacity(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return 0;
		}

		RE::BSAutoLock lock{ a_actor->currentProcess->middleHigh->equippedItemsLock };

		if (a_actor->currentProcess->middleHigh->equippedItems.size() == 0) {
			return 0;
		}

		RE::EquippedItem& equippedWeapon = a_actor->currentProcess->middleHigh->equippedItems[0];
		RE::TESObjectWEAP::InstanceData* weaponInstance = (RE::TESObjectWEAP::InstanceData*)equippedWeapon.item.instanceData.get();
		RE::EquippedWeaponData* weaponData = (RE::EquippedWeaponData*)equippedWeapon.data.get();

		if (equippedWeapon.equipIndex.index == 0 && weaponData && weaponInstance) {
			return weaponInstance->ammoCapacity;
		}

		return 0;
	}

	inline int GetWeaponAmmoCount(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return 0;
		}

		RE::BSAutoLock lock{ a_actor->currentProcess->middleHigh->equippedItemsLock };

		if (a_actor->currentProcess->middleHigh->equippedItems.size() == 0) {
			return 0;
		}

		RE::EquippedItem& equippedWeapon = a_actor->currentProcess->middleHigh->equippedItems[0];
		RE::TESObjectWEAP::InstanceData* weaponInstance = (RE::TESObjectWEAP::InstanceData*)equippedWeapon.item.instanceData.get();
		RE::EquippedWeaponData* weaponData = (RE::EquippedWeaponData*)equippedWeapon.data.get();

		if (equippedWeapon.equipIndex.index == 0 && weaponData && weaponInstance) {
			return weaponData->ammoCount;
		}

		return 0;
	}

	inline RE::TESAmmo* GetWeaponAmmoType(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return nullptr;
		}

		RE::BSAutoLock lock{ a_actor->currentProcess->middleHigh->equippedItemsLock };

		if (a_actor->currentProcess->middleHigh->equippedItems.size() == 0) {
			return nullptr;
		}

		RE::EquippedItem& equippedWeapon = a_actor->currentProcess->middleHigh->equippedItems[0];
		RE::TESObjectWEAP::InstanceData* weaponInstance = (RE::TESObjectWEAP::InstanceData*)equippedWeapon.item.instanceData.get();
		RE::EquippedWeaponData* weaponData = (RE::EquippedWeaponData*)equippedWeapon.data.get();

		if (equippedWeapon.equipIndex.index == 0 && weaponData && weaponInstance) {
			return weaponInstance->ammo;
		}

		return nullptr;
	}

	inline int GetWeaponMagCount(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		bool a_roundDown)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return 0;
		}

		RE::BSAutoLock lock{ a_actor->currentProcess->middleHigh->equippedItemsLock };

		if (a_actor->currentProcess->middleHigh->equippedItems.size() == 0) {
			return 0;
		}

		RE::EquippedItem& equippedWeapon = a_actor->currentProcess->middleHigh->equippedItems[0];
		RE::TESObjectWEAP::InstanceData* weaponInstance = (RE::TESObjectWEAP::InstanceData*)equippedWeapon.item.instanceData.get();
		RE::EquippedWeaponData* weaponData = (RE::EquippedWeaponData*)equippedWeapon.data.get();

		if (equippedWeapon.equipIndex.index == 0 && weaponData && weaponInstance) {
			RE::TESForm* ammoForm = (RE::TESForm*)weaponInstance->ammo;
			for (RE::BGSInventoryItem inventoryItem : a_actor->inventoryList->data) {
				if (inventoryItem.object == ammoForm) {
					std::uint32_t ammoCapacity = weaponInstance->ammoCapacity;
					std::uint32_t itemCount = inventoryItem.GetCount();
					float result = static_cast<float>(itemCount) / static_cast<float>(ammoCapacity);
					if (result == static_cast<int>(result)) {
						return static_cast<int>(result);
					} else {
						if (a_roundDown) {
							return static_cast<int>(std::floor(result));
						} else {
							return static_cast<int>(std::ceil(result));
						}
					}
				}
			}
				
		}

		return 0;
	}

	inline bool HasActiveMagicEffect(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		RE::EffectSetting* a_mgef)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		if (!a_mgef) {
			a_vm.PostError("MagicEffect is None", a_stackID, Severity::kError);
			return false;
		}

		const RE::BSTArray<RE::BSTSmartPointer<RE::ActiveEffect>> effectsList = a_actor->GetActiveEffectList()->data;

		if (effectsList.empty()) {
			a_vm.PostError("Actor has no active effects", a_stackID, Severity::kInfo);
			return false;
		}

		for (const auto& currentEffect : effectsList) {
			if (auto mgef = currentEffect ? currentEffect->effect->effectSetting : nullptr; mgef) {
				// ignore effect if it has any of the inactive flags
				if (currentEffect->flags.all(RE::ActiveEffect::Flags::kInactive) || currentEffect->flags.all(RE::ActiveEffect::Flags::kDispelled)) {
					continue;
				// otherwise check if the mgef is the same as the one passed to the function
				} else if (mgef == a_mgef) {
					return true;
				}
			}
		}

		return false;
	}

	inline bool HasFactionFromList(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		std::vector<RE::TESFaction*> a_factionList)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		if (a_factionList.size() == 0) {
			a_vm.PostError("Empty faction array passed", a_stackID, Severity::kInfo);
			return false;
		}

		for (auto currentFaction : a_factionList) {
			if (a_actor->IsInFaction(currentFaction) == true) {
				return true;
			}
		}

		return false;
	}

	inline bool IsCrippled(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		return a_actor->IsCrippled();
	}

	inline bool IsFleeing(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		return a_actor->currentProcess->middleHigh->fleeing;
	}

	inline bool IsFollowing(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		return a_actor->IsFollowing();
	}

	inline bool IsFollowingActor(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		RE::Actor* a_actorTarget)
	{
		if (!a_actor) {
			a_vm.PostError("Follower Actor is None", a_stackID, Severity::kError);
			return false;
		}

		if (!a_actorTarget) {
			a_vm.PostError("Follow target Actor is None", a_stackID, Severity::kError);
			return false;
		}

		if (a_actor->IsFollowing() == false) {
			return false;
		}

		if (a_actor->currentProcess->followTarget.get().get()->GetObjectReference() == a_actorTarget->GetObjectReference()) {
			return true;
		}

		return false;
	}

	inline bool IsInKillMove(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		return static_cast<uint32_t>(a_actor->boolFlags.get()) & static_cast<uint32_t>(RE::Actor::BOOL_FLAGS::kIsInKillMove);
	}

	inline bool IsJumping(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		return a_actor->IsJumping();
	}

	inline bool IsKeywordOnArmorIndex(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		RE::BGSKeyword* a_keyword,
		std::uint32_t a_indexSlot)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		if (!a_keyword) {
			a_vm.PostError("Keyword is None", a_stackID, Severity::kError);
			return false;
		}
		
		auto armorAtSlot = a_actor->biped->object[a_indexSlot].parent.object;

		if (armorAtSlot) {
			return a_actor->biped->object[a_indexSlot].parent.instanceData.get()->GetKeywordData()->HasKeyword(a_keyword);
		} else {
			a_vm.PostError("Nothing equipped at provided index", a_stackID, Severity::kError);
			return false;
		}
	}

	inline bool IsKeywordOnWeapon(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		RE::BGSKeyword* a_keyword)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		if (!a_keyword) {
			a_vm.PostError("Keyword is None", a_stackID, Severity::kError);
			return false;
		}

		RE::BSAutoLock lock{ a_actor->currentProcess->middleHigh->equippedItemsLock };

		if (a_actor->currentProcess->middleHigh->equippedItems.size() == 0) {
			return false;
		}

		RE::EquippedItem& equippedWeapon = a_actor->currentProcess->middleHigh->equippedItems[0];
		RE::TESObjectWEAP::InstanceData* weaponInstance = (RE::TESObjectWEAP::InstanceData*)equippedWeapon.item.instanceData.get();
		RE::EquippedWeaponData* weaponData = (RE::EquippedWeaponData*)equippedWeapon.data.get();

		if (equippedWeapon.equipIndex.index == 0 && weaponData && weaponInstance) {
			if (weaponInstance->keywords) {
				return weaponInstance->keywords->HasKeyword(a_keyword);
			}
			a_vm.PostError("Instance Keywords are None", a_stackID, Severity::kError);
		}

		return false;
	}

	inline bool IsPathing(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		return a_actor->IsPathing();
	}

	inline bool IsPathingComplete(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		return a_actor->IsPathingComplete();
	}

	inline bool IsPathValid(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		return a_actor->IsPathValid();
	}

	inline bool IsQuadruped(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		return a_actor->IsQuadruped();
	}

	inline bool IsStaggered(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		return a_actor->staggered;
	}

	inline bool IsTakingHealthDamage(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		return a_actor->IsTakingHealthDamageFromActiveEffect();
	}

	inline bool IsTakingRadDamage(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		return a_actor->IsTakingRadDamageFromActiveEffect();
	}

	inline bool IsTresspassing(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		return static_cast<uint32_t>(a_actor->boolFlags.get()) & static_cast<uint32_t>(RE::Actor::BOOL_FLAGS::kIsTresspassing);
	}

	inline bool IsUnderwater(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return false;
		}

		return static_cast<uint32_t>(a_actor->boolFlags.get()) & static_cast<uint32_t>(RE::Actor::BOOL_FLAGS::kUnderwater);
	}

	inline std::vector<RE::Actor*> RemoveActorFromArray(IVM& a_vm, VMStackID a_stackID, std::monostate,
		std::vector<RE::Actor*> a_actorArray,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return a_actorArray;
		}

		auto arrayIndex = std::find(a_actorArray.begin(), a_actorArray.end(), a_actor);
		if (arrayIndex != a_actorArray.end()) {
			a_actorArray.erase(arrayIndex);
		}

		return a_actorArray;
	}

	inline void ResetInventory(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		bool a_leveledOnly)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return;
		}

		a_actor->ResetInventory(a_leveledOnly);
	}

	inline void SetActorAttackingDisabled(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		bool a_enable)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return;
		}

		if (a_enable) {
			a_actor->boolFlags.set(RE::Actor::BOOL_FLAGS::kAttackingDisabled);
		} else {
			a_actor->boolFlags.reset(RE::Actor::BOOL_FLAGS::kAttackingDisabled);
		}
	}

	inline void SetDoNotShowOnStealthMeter(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		bool a_enable)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return;
		}

		if (a_actor->IsPlayer() == true) {
			a_vm.PostError("Actor cannot be Player", a_stackID, Severity::kError);
			return;
		}

		if (a_enable) {
			a_actor->boolFlags.set(RE::Actor::BOOL_FLAGS::kDoNotShowOnStealthMeter);
		} else {
			a_actor->boolFlags.reset(RE::Actor::BOOL_FLAGS::kDoNotShowOnStealthMeter);
		}
	}

	inline void SetWeaponAmmoCount(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		std::uint32_t a_count)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return;
		}

		RE::BSAutoLock lock{ a_actor->currentProcess->middleHigh->equippedItemsLock };

		if (a_actor->currentProcess->middleHigh->equippedItems.size() == 0) {
			return;
		}

		RE::EquippedItem& equippedWeapon = a_actor->currentProcess->middleHigh->equippedItems[0];
		RE::TESObjectWEAP::InstanceData* weaponInstance = (RE::TESObjectWEAP::InstanceData*)equippedWeapon.item.instanceData.get();
		RE::EquippedWeaponData* weaponData = (RE::EquippedWeaponData*)equippedWeapon.data.get();

		if (equippedWeapon.equipIndex.index == 0 && weaponData && weaponInstance) {
			weaponData->ammoCount = a_count;
		}

		return;
	}

	inline void StowWeapon(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return;
		}

		RE::BSAutoLock lock{ a_actor->currentProcess->middleHigh->equippedItemsLock };

		if (a_actor->currentProcess->middleHigh->equippedItems.size() == 0) {
			return;
		}

		RE::EquippedItem& equippedWeapon = a_actor->currentProcess->middleHigh->equippedItems[0];

		if (equippedWeapon.equipIndex.index == 0) {
			a_actor->DrawWeaponMagicHands(false);
		}
		
		return;
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "AreHostileActorsInRange", AreHostileActorsInRange, true);
		a_vm.BindNativeMethod("Lighthouse", "DrinkPotion", DrinkPotion, true);
		a_vm.BindNativeMethod("Lighthouse", "ExitCover", ExitCover, true);
		a_vm.BindNativeMethod("Lighthouse", "GetActiveEffects", GetActiveEffects, true);
		a_vm.BindNativeMethod("Lighthouse", "GetActorFactionsFromList", GetActorFactionsFromList, true);
		a_vm.BindNativeMethod("Lighthouse", "GetActorGunState", GetActorGunState, true);
		a_vm.BindNativeMethod("Lighthouse", "GetActorsByVerticalDistance", GetActorsByVerticalDistance, true);
		a_vm.BindNativeMethod("Lighthouse", "GetActorsInRange", GetActorsInRange, true);
		a_vm.BindNativeMethod("Lighthouse", "GetActorsTargetingActor", GetActorsTargetingActor, true);
		a_vm.BindNativeMethod("Lighthouse", "GetArmorFormOnBipedSlot", GetArmorFormOnBipedSlot, true);
		a_vm.BindNativeMethod("Lighthouse", "GetClosestActorWithKeyword", GetClosestActorWithKeyword, true);
		a_vm.BindNativeMethod("Lighthouse", "GetCombatStyle", GetCombatStyle, true);
		a_vm.BindNativeMethod("Lighthouse", "GetCommandedActors", GetCommandedActors, true);
		a_vm.BindNativeMethod("Lighthouse", "GetRunningPackage", GetRunningPackage, true);
		a_vm.BindNativeMethod("Lighthouse", "GetEncumbranceRate", GetEncumbranceRate, true);
		a_vm.BindNativeMethod("Lighthouse", "GetEquippedWeight", GetEquippedWeight, true);
		a_vm.BindNativeMethod("Lighthouse", "GetHighActorsByRace", GetHighActorsByRace, true);
		a_vm.BindNativeMethod("Lighthouse", "GetHighActorsHostileToActor", GetHighActorsHostileToActor, true);
		a_vm.BindNativeMethod("Lighthouse", "GetHighActorsInCombat", GetHighActorsInCombat, true);
		a_vm.BindNativeMethod("Lighthouse", "GetHighDeadActors", GetHighDeadActors, true);
		a_vm.BindNativeMethod("Lighthouse", "GetHostileActorsInRange", GetHostileActorsInRange, true);
		a_vm.BindNativeMethod("Lighthouse", "GetKnockState", GetKnockState, true);
		a_vm.BindNativeMethod("Lighthouse", "GetLifeState", GetLifeState, true);
		a_vm.BindNativeMethod("Lighthouse", "GetOffersServices", GetOffersServices, true);
		a_vm.BindNativeMethod("Lighthouse", "GetTimeDead", GetTimeDead, true);
		a_vm.BindNativeMethod("Lighthouse", "GetTimeOfDeath", GetTimeOfDeath, true);
		a_vm.BindNativeMethod("Lighthouse", "GetVendorContainerRef", GetVendorContainerRef, true);
		a_vm.BindNativeMethod("Lighthouse", "GetVendorFaction", GetVendorFaction, true);
		a_vm.BindNativeMethod("Lighthouse", "GetWeaponAmmoCapacity", GetWeaponAmmoCapacity, true);
		a_vm.BindNativeMethod("Lighthouse", "GetWeaponAmmoCount", GetWeaponAmmoCount, true);
		a_vm.BindNativeMethod("Lighthouse", "GetWeaponAmmoType", GetWeaponAmmoType, true);
		a_vm.BindNativeMethod("Lighthouse", "GetWeaponMagCount", GetWeaponMagCount, true);
		a_vm.BindNativeMethod("Lighthouse", "HasActiveMagicEffect", HasActiveMagicEffect, true);
		a_vm.BindNativeMethod("Lighthouse", "HasFactionFromList", HasFactionFromList, true);
		a_vm.BindNativeMethod("Lighthouse", "IsCrippled", IsCrippled, true);
		a_vm.BindNativeMethod("Lighthouse", "IsFleeing", IsFleeing, true);
		a_vm.BindNativeMethod("Lighthouse", "IsFollowing", IsFollowing, true);
		a_vm.BindNativeMethod("Lighthouse", "IsFollowingActor", IsFollowingActor, true);
		a_vm.BindNativeMethod("Lighthouse", "IsInKillMove", IsInKillMove, true);
		a_vm.BindNativeMethod("Lighthouse", "IsJumping", IsJumping, true);
		a_vm.BindNativeMethod("Lighthouse", "IsKeywordOnArmorIndex", IsKeywordOnArmorIndex, true);
		a_vm.BindNativeMethod("Lighthouse", "IsKeywordOnWeapon", IsKeywordOnWeapon, true);
		a_vm.BindNativeMethod("Lighthouse", "IsPathing", IsPathing, true);
		a_vm.BindNativeMethod("Lighthouse", "IsPathingComplete", IsPathingComplete, true);
		a_vm.BindNativeMethod("Lighthouse", "IsPathValid", IsPathValid, true);
		a_vm.BindNativeMethod("Lighthouse", "IsQuadruped", IsQuadruped, true);
		a_vm.BindNativeMethod("Lighthouse", "IsStaggered", IsStaggered, true);
		a_vm.BindNativeMethod("Lighthouse", "IsTakingHealthDamage", IsTakingHealthDamage, true);
		a_vm.BindNativeMethod("Lighthouse", "IsTakingRadDamage", IsTakingRadDamage, true);
		a_vm.BindNativeMethod("Lighthouse", "IsTresspassing", IsTresspassing, true);
		a_vm.BindNativeMethod("Lighthouse", "IsUnderwater", IsUnderwater, true);
		a_vm.BindNativeMethod("Lighthouse", "RemoveActorFromArray", RemoveActorFromArray, true);
		a_vm.BindNativeMethod("Lighthouse", "ResetInventory", ResetInventory, true);
		a_vm.BindNativeMethod("Lighthouse", "SetActorAttackingDisabled", SetActorAttackingDisabled, true);
		a_vm.BindNativeMethod("Lighthouse", "SetDoNotShowOnStealthMeter", SetDoNotShowOnStealthMeter, true);
		a_vm.BindNativeMethod("Lighthouse", "SetWeaponAmmoCount", SetWeaponAmmoCount, true);
		a_vm.BindNativeMethod("Lighthouse", "StowWeapon", StowWeapon, true);

		logger::info("Actor functions registered.");
	}
}
