#pragma once

namespace Papyrus::Location
{
	/*
	inline void AddKeywordToLocation(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSLocation* a_location,
		RE::BGSKeyword* a_keyword)
	{
		if (!a_location) {
			a_vm.PostError("Location is None", a_stackID, Severity::kError);
			return;
		}

		if (!a_keyword) {
			a_vm.PostError("Keyword is None", a_stackID, Severity::kError);
			return;
		}

		if (a_location->HasKeyword(a_keyword) == false) {
			a_location->AddKeyword(a_keyword);
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

	inline std::string GetLocationName(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSLocation* a_location)
	{
		if (!a_location) {
			a_vm.PostError("Location is None", a_stackID, Severity::kError);
			return "";
		}

		return a_location->fullName.c_str();
	}

	inline void Bind(IVM& a_vm)
	{
		//a_vm.BindNativeMethod("Lighthouse", "AddKeywordToLocation", AddKeywordToLocation, true);
		a_vm.BindNativeMethod("Lighthouse", "GetChildLocations", GetChildLocations, true);
		a_vm.BindNativeMethod("Lighthouse", "GetLocationName", GetLocationName, true);

		logger::info("Location functions registered.");
	}
}
