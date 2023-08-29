#pragma once

namespace Papyrus::ActorBase
{
	inline RE::TESCombatStyle* GetActorBaseCombatStyle(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESNPC* a_actorBase)
	{
		if (!a_actorBase) {
			a_vm.PostError("ActorBase is None", a_stackID, Severity::kError);
			return nullptr;
		}

		return a_actorBase->GetCombatStyle();
	}

	inline RE::TESLevItem* GetDeathItem(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESNPC* a_actorBase)
	{
		if (!a_actorBase) {
			a_vm.PostError("ActorBase is None", a_stackID, Severity::kError);
			return nullptr;
		}

		return a_actorBase->deathItem;
	}

	inline std::vector<RE::TESFaction*> GetFactions(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESNPC* a_actorBase)
	{
		std::vector<RE::TESFaction*> result;

		if (!a_actorBase) {
			a_vm.PostError("ActorBase is None", a_stackID, Severity::kError);
			return result;
		}
		auto factionArray = a_actorBase->factions;

		for (auto currentFaction : factionArray) {
			result.push_back(currentFaction.faction);
		}

		return result;
	}

	inline std::uint32_t GetPerkCount(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESNPC* a_actorBase)
	{
		if (!a_actorBase) {
			a_vm.PostError("ActorBase is None", a_stackID, Severity::kError);
			return 0;
		}

		return a_actorBase->perkCount;
	}

	inline std::vector<RE::TESNPC*> GetRelationships(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESNPC* a_actorBase,
		RE::BGSAssociationType* a_assocType)
	{
		if (!a_actorBase) {
			a_vm.PostError("ActorBase is None", a_stackID, Severity::kError);
			return {};
		}

		std::vector<RE::TESNPC*> actorbases;
		if (a_actorBase->relationships) {
			for (const auto& relationship : *a_actorBase->relationships) {
				if (relationship && (!a_assocType || relationship->assocType == a_assocType)) {
					auto parentNPC = relationship->npc1;
					if (parentNPC == a_actorBase) {
						parentNPC = relationship->npc2;
					}
					actorbases.push_back(parentNPC);
				}
			}
		}
		return actorbases;
	}

	inline bool HasAutoCalcStats(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESNPC* a_actorBase)
	{
		if (!a_actorBase) {
			a_vm.PostError("ActorBase is None", a_stackID, Severity::kError);
			return false;
		}

		return a_actorBase->HasAutoCalcStats();
	}

	inline bool HasPCLevelMult(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESNPC* a_actorBase)
	{
		if (!a_actorBase) {
			a_vm.PostError("ActorBase is None", a_stackID, Severity::kError);
			return false;
		}

		return a_actorBase->HasPCLevelMult();
	}

	inline void SetDeathItem(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESNPC* a_actorBase,
		RE::TESLevItem* a_DeathItem)
	{
		if (!a_actorBase) {
			a_vm.PostError("ActorBase is None", a_stackID, Severity::kError);
			return;
		}

		a_actorBase->deathItem = a_DeathItem;
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "GetActorBaseCombatStyle", GetActorBaseCombatStyle, true);
		a_vm.BindNativeMethod("Lighthouse", "GetDeathItem", GetDeathItem, true);
		a_vm.BindNativeMethod("Lighthouse", "GetFactions", GetFactions, true);
		a_vm.BindNativeMethod("Lighthouse", "GetPerkCount", GetPerkCount, true);
		a_vm.BindNativeMethod("Lighthouse", "GetRelationships", GetRelationships, true);
		a_vm.BindNativeMethod("Lighthouse", "HasAutoCalcStats", HasAutoCalcStats, true);
		a_vm.BindNativeMethod("Lighthouse", "HasPCLevelMult", HasPCLevelMult, true);
		a_vm.BindNativeMethod("Lighthouse", "SetDeathItem", SetDeathItem, true);

		logger::info("ActorBase functions registered.");
	}
}
