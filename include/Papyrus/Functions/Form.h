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

	inline bool IsContainerFlagSet(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		std::uint32_t a_flag)
	{
		if (!a_form) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return false;
		}

		if (a_form->GetFormType() != RE::ENUM_FORM_ID::kCONT) {
			a_vm.PostError("Form is not of CONT type", a_stackID, Severity::kError);
			return false;
		}

		auto thisContainer = (RE::TESObjectCONT*)a_form;

		//(a_form->formFlags & a_flag) != 0
		return (thisContainer->flags & a_flag) != 0;
	}

	inline RE::BSTArray<RE::TESForm*> GetFormArrayByType(IVM& a_vm, VMStackID a_stackID, std::monostate,
		std::uint32_t a_formType)
	{
		if (a_formType <= 159) {
			return RE::TESDataHandler::GetSingleton()->formArrays[a_formType];
		}

		a_vm.PostError("Incorrect Form type value passed", a_stackID, Severity::kError);
		return {};
	}

	inline std::uint32_t GetFormType(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return {};
		}

		return static_cast<std::uint32_t>(a_form->GetFormType());
	}

	inline std::string GetFormEditorID(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form)
	{
		if (!a_form) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return {};
		}

		return a_form->GetFormEditorID();
	}

	inline std::vector<RE::BGSConstructibleObject*> GetParentCOBJs(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		RE::BGSKeyword* a_workshopKeyword,
		RE::BGSKeyword* a_categoryKeyword)
	{
		std::vector<RE::BGSConstructibleObject*> result;

		if (!a_form) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return result;
		}

		if (auto dataHandler = RE::TESDataHandler::GetSingleton(); dataHandler) {
			auto cobjArray = dataHandler->GetFormArray<RE::BGSConstructibleObject>();
			for (auto thisCOBJ : cobjArray) {
				if (a_categoryKeyword != nullptr && thisCOBJ->filterKeywords.HasKeyword(a_categoryKeyword) == false) {
					continue;
				} else if (a_workshopKeyword != nullptr && thisCOBJ->benchKeyword != a_workshopKeyword) {
					continue;
				}

				// the record may be a FormList that contains a_form
				if (thisCOBJ->createdItem != nullptr) {
					if (RE::BGSListForm* formList = thisCOBJ->createdItem->As<RE::BGSListForm>(); formList) {
						for (auto listElement : formList->arrayOfForms) {
							if (listElement == a_form) {
								result.push_back(thisCOBJ);
								break;
							}
						}
					} else {
						if (thisCOBJ->createdItem == a_form) {
							result.push_back(thisCOBJ);
						}
					}
				}
			}
		}

		return result;
	}

	/*
	inline RE::TESForm* GetMagicEffectAssociatedForm(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::EffectSetting* a_magicEffect)
	{
		if (!a_magicEffect) {
			a_vm.PostError("MagicEffect is None", a_stackID, Severity::kError);
			return nullptr;
		}
		
		RE::TESForm* associatedForm = a_magicEffect->data.associatedForm;
		
		return (associatedForm == nullptr) ? nullptr : associatedForm;
	}
	*/

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
		a_vm.BindNativeMethod("Lighthouse", "GetFormArrayByType", GetFormArrayByType, true);
		a_vm.BindNativeMethod("Lighthouse", "GetFormType", GetFormType, true);
		a_vm.BindNativeMethod("Lighthouse", "GetFormEditorID", GetFormEditorID, true);
		a_vm.BindNativeMethod("Lighthouse", "GetParentCOBJs", GetParentCOBJs, true);
		//a_vm.BindNativeMethod("Lighthouse", "GetMagicEffectAssociatedForm", GetMagicEffectAssociatedForm, true);
		a_vm.BindNativeMethod("Lighthouse", "IsContainerFlagSet", IsContainerFlagSet, true);
		a_vm.BindNativeMethod("Lighthouse", "IsDynamicForm", IsDynamicForm, true);
		a_vm.BindNativeMethod("Lighthouse", "IsFormInMod", IsFormInMod, true);
		a_vm.BindNativeMethod("Lighthouse", "IsRecordFlagSet", IsRecordFlagSet, true);
		a_vm.BindNativeMethod("Lighthouse", "SetRecordFlag", SetRecordFlag, true);

		logger::info("Form functions registered.");
	}
}
