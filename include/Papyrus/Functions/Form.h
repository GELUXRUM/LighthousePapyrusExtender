#pragma once

namespace Papyrus::Form
{
	inline void ClearRecordFlag(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		std::uint32_t a_flag)
	{
		if (!a_form) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return;
		}

		a_form->formFlags &= ~a_flag;
	}

	inline RE::TESForm* GetFormByEditorID(std::monostate,
		RE::BSFixedString a_editorID)
	{
		return (RE::TESForm::GetFormByEditorID(a_editorID) != nullptr) ? RE::TESForm::GetFormByEditorID(a_editorID) : nullptr;
	}

	inline RE::BSFixedString GetFormEditorID(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return {};
		}

		return a_form->GetFormEditorID();
	}

	uint32_t GetFormType(std::monostate, RE::TESForm* a_form)
	{
		return (a_form) ? static_cast<uint32_t>(a_form->GetFormType()) : 0;
	}


	inline bool IsRecordFlagSet(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		std::uint32_t a_flag)
	{
		if (!a_form) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return false;
		}

		return (a_form->formFlags & a_flag) != 0;
	}

	inline void SetRecordFlag(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		std::uint32_t a_flag)
	{
		if (!a_form) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return;
		}

		a_form->formFlags |= a_flag;
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "ClearRecordFlag", ClearRecordFlag, true);
		a_vm.BindNativeMethod("Lighthouse", "GetFormByEditorID", GetFormByEditorID, true);
		a_vm.BindNativeMethod("Lighthouse", "GetFormEditorID", GetFormEditorID, true);
		a_vm.BindNativeMethod("Lighthouse", "GetFormType", GetFormType, true);
		a_vm.BindNativeMethod("Lighthouse", "IsRecordFlagSet", IsRecordFlagSet, true);
		a_vm.BindNativeMethod("Lighthouse", "SetRecordFlag", SetRecordFlag, true);

		logger::info("Form functions registered.");
	}
}
