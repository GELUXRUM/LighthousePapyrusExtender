#pragma once

namespace Papyrus::ActorValue
{
	float GetFormBaseValue(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		RE::ActorValueInfo* a_actorValue)
	{
		if (!a_form) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		if (a_form->GetFormType() != RE::ENUM_FORM_ID::kNPC_) {
			a_vm.PostError("Form is not of NPC_ type", a_stackID, Severity::kError);
			return 0.0f;
		}

		auto formToNPC = (RE::TESNPC*)a_form;

		return formToNPC->GetActorValue(*a_actorValue);
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "GetFormBaseValue", GetFormBaseValue, true);

		logger::info("ActorValue functions registered.");
	}
}
