#pragma once

namespace Papyrus::Location
{
	/*
	inline void AddKeywordToLocation(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSLocation* a_Location,
		RE::BGSKeyword* a_keyword)
	{
		if (!a_Location) {
			a_vm.PostError("Location is None", a_stackID, Severity::kError);
			return;
		}

		if (!a_keyword) {
			a_vm.PostError("Keyword is None", a_stackID, Severity::kError);
			return;
		}

		if (a_Location->HasKeyword(a_keyword) == false) {
			a_Location->AddKeyword(a_keyword);
		}
	}
	*/

	inline std::vector<RE::BGSLocation*> GetChildLocations(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSLocation* a_parentLocation)
	{
		std::vector<RE::BGSLocation*> result;

		if (!a_parentLocation) {
			a_vm.PostError("Location is None", a_stackID, Severity::kError);
			return result;
		}

		if (auto dataHandler = RE::TESDataHandler::GetSingleton(); dataHandler) {
			for (auto currentLocation : dataHandler->GetFormArray<RE::BGSLocation>()) {
				if (currentLocation != a_parentLocation && currentLocation->parentLoc == a_parentLocation) {
					result.push_back(currentLocation);
				}
			}
		}
		return result;
	}

	inline void Bind(IVM& a_vm)
	{
		//a_vm.BindNativeMethod("Lighthouse", "AddKeywordToLocation", AddKeywordToLocation, true);
		a_vm.BindNativeMethod("Lighthouse", "GetChildLocations", GetChildLocations, true);

		logger::info("Location functions registered.");
	}
}
