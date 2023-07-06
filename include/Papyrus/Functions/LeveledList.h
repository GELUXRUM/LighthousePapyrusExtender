#pragma once

#include "Papyrus/Utilities/LeveledListUtils.h"

namespace Papyrus::LeveledList
{
	inline RE::TESGlobal* GetChanceNoneGlobal(IVM& a_vm, VMStackID a_stackID, std::monostate, RE::TESLevItem* leveledList)
	{
		if (!leveledList) {
			a_vm.PostError("LeveledList is None", a_stackID, Severity::kError);
			return nullptr;
		}

		return leveledList->chanceGlobal;
	}

	inline int GetLeveledListChanceNone(IVM& a_vm, VMStackID a_stackID, std::monostate, RE::TESLevItem* leveledList)
	{
		if (!leveledList) {
			a_vm.PostError("LeveledList is None", a_stackID, Severity::kError);
			return 0;
		}

		return leveledList->GetChanceNone();
	}

	using LeveledObject = RE::BSScript::structure_wrapper<"Lighthouse", "LeveledObject">;

	inline std::vector<LeveledObject> GetLeveledListObjects(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESForm* frm)
	{
		std::vector<LeveledObject> res;

		if (!frm) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return res;
		}

		auto ll = Util::GetLeveledList(frm);
		if (ll == nullptr) {
			return res;
		}

		int32_t total = (ll->baseListCount + ll->scriptListCount);
		for (int i = 0; i < total; i++) {
			RE::LEVELED_OBJECT* obj;
			if (i < ll->baseListCount) {
				obj = &ll->leveledLists[i];
			} else {
				obj = ll->scriptAddedLists[i - (ll->baseListCount - 1)];
			}

			LeveledObject lo;
			lo.insert("chanceNone", static_cast<int32_t>(obj->chanceNone));
			lo.insert("count", static_cast<int32_t>(obj->count));
			lo.insert("object", obj->form);
			lo.insert("level", static_cast<int32_t>(obj->level));
			res.push_back(lo);
		}

		return res;
	}

	inline bool GetUseAll(IVM& a_vm, VMStackID a_stackID, std::monostate, RE::TESLevItem* leveledList)
	{
		if (!leveledList) {
			a_vm.PostError("LeveledList is None", a_stackID, Severity::kError);
			return false;
		}

		return leveledList->GetUseAll();
	}

	inline void SetChanceNoneGlobal(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESLevItem* a_leveledList,
		RE::TESGlobal* a_global)
	{
		if (!a_leveledList) {
			a_vm.PostError("LeveledList is None", a_stackID, Severity::kError);
			return;
		}

		a_leveledList->chanceGlobal = a_global;
	}

	inline void SetLeveledListChanceNone(IVM& a_vm, VMStackID a_stackID, std::monostate, RE::TESLevItem* a_leveledList, int a_chance)
	{
		if (!a_leveledList) {
			a_vm.PostError("LeveledList is None", a_stackID, Severity::kError);
			return;
		}

		if (a_chance < 0 || a_chance > 100) {
			a_vm.PostError("Chance value is outside the allowable range", a_stackID, Severity::kError);
			return;
		}

		a_leveledList->chanceNone = static_cast<int8_t>(a_chance);
	}
	
	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "GetChanceNoneGlobal", GetChanceNoneGlobal, true);
		a_vm.BindNativeMethod("Lighthouse", "GetLeveledListChanceNone", GetLeveledListChanceNone, true);
		//a_vm.BindNativeMethod("Lighthouse", "GetLeveledListObjects", GetLeveledListObjects, true);
		a_vm.BindNativeMethod("Lighthouse", "GetUseAll", GetUseAll, true);
		a_vm.BindNativeMethod("Lighthouse", "SetChanceNoneGlobal", SetChanceNoneGlobal, true);
		a_vm.BindNativeMethod("Lighthouse", "SetLeveledListChanceNone", SetLeveledListChanceNone, true);

		logger::info("Leveled List/Item functions registered.");
	}
}
