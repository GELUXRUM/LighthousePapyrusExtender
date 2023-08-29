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

	std::uint32_t GetFormType(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return {};
		}

		return static_cast<std::uint32_t>(a_form->GetFormType());
	}

	std::string GetFormEditorID(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return {};
		}

		return a_form->GetFormEditorID();
	}

	inline bool IsDynamicForm(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return false;
		}

		if (a_form->GetFormID() >= 0xFF000000) {
			return true;
		}

		return false;
	}

	inline bool IsFormInMod(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		std::string a_modName)
	{
		if (!a_form) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return false;
		}

		auto tesFile = RE::TESDataHandler::GetSingleton()->LookupModByName(a_modName);
		return tesFile ? tesFile->IsFormInMod(a_form->GetFormID()) : false;
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
		a_vm.BindNativeMethod("Lighthouse", "GetFormType", GetFormType, true);
		a_vm.BindNativeMethod("Lighthouse", "GetFormEditorID", GetFormEditorID, true);
		a_vm.BindNativeMethod("Lighthouse", "IsDynamicForm", IsDynamicForm, true);
		a_vm.BindNativeMethod("Lighthouse", "IsFormInMod", IsFormInMod, true);
		a_vm.BindNativeMethod("Lighthouse", "IsRecordFlagSet", IsRecordFlagSet, true);
		a_vm.BindNativeMethod("Lighthouse", "SetRecordFlag", SetRecordFlag, true);

		logger::info("Form functions registered.");
	}
}
