#pragma once

namespace Papyrus::Keyword
{

	inline RE::TESObjectREFR* FindClosestReferenceWithKeyword(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_originRef,
		std::vector<RE::TESObjectREFR*> a_refArray,
		RE::BGSKeyword* a_keyword)
	{
		if (!a_originRef) {
			a_vm.PostError("Ref is None", a_stackID, Severity::kError);
			return nullptr;
		}

		if (a_refArray.empty()) {
			a_vm.PostError("Array is empty", a_stackID, Severity::kError);
			return nullptr;
		}
		// Get the position of originRef
		auto originPos = a_originRef->GetPosition();
		// Initialize variables for closest reference and smallest distance
		RE::TESObjectREFR* closestRef = nullptr;
		float smallestDistance = std::numeric_limits<float>::max();
		float distance{ 0.0f };
		// Loop through each reference in the array
		for (auto currentRef : a_refArray) {
			// Check if there is a Keyword to look for
			if (!a_keyword) {
				// Check if it has the required Keyword
				if (currentRef->HasKeyword(a_keyword)) {
					// Calculate the distance for the current reference
					distance = originPos.GetDistance(currentRef->GetPosition());
					// If the current distance is smaller than the smallest distance found so far,
					// update the smallest distance and closest reference variables
					if (distance < smallestDistance) {
						smallestDistance = distance;
						closestRef = currentRef;
					}
				}
			// If Keyword is NULL, just don't check for it
			} else {
				// Calculate the distance for the current reference
				distance = originPos.GetDistance(currentRef->GetPosition());
				// If the current distance is smaller than the smallest distance found so far,
				// update the smallest distance and closest reference variables
				if (distance < smallestDistance) {
					smallestDistance = distance;
					closestRef = currentRef;
				}
			}
		}
		return closestRef;
	}

	inline bool IsKeywordInNPCForm(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESForm* a_form,
		RE::BGSKeyword* a_keyword)
	{
		// Check if form isn't null
		if (!a_form ) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return false;
		}

		if (!a_keyword) {
			a_vm.PostError("Keyword is None", a_stackID, Severity::kError);
			return false;
		}

		if (a_form->GetFormType() == RE::ENUM_FORM_ID::kNPC_) {
			a_vm.PostError("Form must be of NPC_ type", a_stackID, Severity::kError);
			return false;
		}

		// Cast as pointer to RE::TESNPC*
		auto formToNPC = (RE::TESNPC*)a_form;
		// Get the keyword's EditorID in the correct format for later
		auto keywordEditorID = static_cast<std::string_view>(a_keyword->GetFormEditorID());
		// Check if keyword is present
		return formToNPC->ContainsKeyword(keywordEditorID);
	}

	std::vector<RE::BGSKeyword*> RemoveKeywordFromArray(IVM& a_vm, VMStackID a_stackID, std::monostate,
		std::vector<RE::BGSKeyword*> a_keywordArray,
		RE::BGSKeyword* a_keyword)
	{
		if (!a_keyword) {
			a_vm.PostError("Keyword is None", a_stackID, Severity::kError);
			return a_keywordArray;
		}

		auto arrayIndex = std::find(a_keywordArray.begin(), a_keywordArray.end(), a_keyword);
		if (arrayIndex != a_keywordArray.end()) {
			a_keywordArray.erase(arrayIndex);
		}

		return a_keywordArray;
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "FindClosestReferenceWithKeyword", FindClosestReferenceWithKeyword, true);
		a_vm.BindNativeMethod("Lighthouse", "IsKeywordInNPCForm", IsKeywordInNPCForm, true);
		a_vm.BindNativeMethod("Lighthouse", "RemoveKeywordFromArray", RemoveKeywordFromArray, true);

		logger::info("Keyword functions registered.");
	}
}
