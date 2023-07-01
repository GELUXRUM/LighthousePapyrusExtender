#pragma once

namespace Papyrus::CombatStyle
{
	// TODO: Update this for all Combat Style sections
	inline void SetCombatStyleValue(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESCombatStyle* a_combatStyle,
		int a_indexValue,
		float a_value)
	{
		if (!a_combatStyle) {
			a_vm.PostError("CombatStyle is None", a_stackID, Severity::kError);
			return;
		}

		if (a_value < 0) {
			a_vm.PostError("Value cannot be negative", a_stackID, Severity::kError);
			return;
		}

		switch (a_indexValue) {
		case 1:
			a_combatStyle->generalData.offensiveMult = a_value;
			break;
		case 2:
			a_combatStyle->generalData.defensiveMult = a_value;
			break;
		case 3:
			a_combatStyle->generalData.groupOffensiveMult = a_value;
			break;
		case 4:
			a_combatStyle->generalData.meleeScoreMult = a_value;
			break;
		case 5:
			a_combatStyle->generalData.magicScoreMult = a_value;
			break;
		case 6:
			a_combatStyle->generalData.rangedScoreMult = a_value;
			break;
		case 7:
			a_combatStyle->generalData.shoutScoreMult = a_value;
			break;
		case 8:
			a_combatStyle->generalData.unarmedScoreMult = a_value;
			break;
		case 9:
			a_combatStyle->generalData.staffScoreMult = a_value;
			break;
		case 10:
			a_combatStyle->generalData.avoidThreatChance = a_value;
			break;
		case 11:
			a_combatStyle->generalData.dodgeThreatChance = a_value;
			break;
		case 12:
			a_combatStyle->generalData.evadeThreatChance = a_value;
			break;
		default:
			a_vm.PostError("Incorrect index", a_stackID, Severity::kError);
			return;
		}
	}

	inline void SetFormCombatStyle(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		RE::TESCombatStyle* a_combatStyle)
	{
		if (!a_form) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return;
		}

		if (!a_combatStyle) {
			a_vm.PostError("CombatStyle is None", a_stackID, Severity::kError);
			return;
		}

		if (a_form->GetFormType() == RE::ENUM_FORM_ID::kNPC_) {
			a_vm.PostError("Form is not of NPC_ type", a_stackID, Severity::kError);
			return;
		}

		auto baseNPC = (RE::TESNPC*)a_form;
		baseNPC->SetCombatStyle(a_combatStyle);
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "SetCombatStyleValue", SetCombatStyleValue, true);
		a_vm.BindNativeMethod("Lighthouse", "SetFormCombatStyle", SetFormCombatStyle, true);

		logger::info("CombatStyle functions registered.");
	}
}
