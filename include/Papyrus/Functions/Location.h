#pragma once

namespace Papyrus::Location
{
	inline RE::BGSLocation* GetParentLocation(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSLocation* a_childLocation)
	{
		if (!a_childLocation) {
			a_vm.PostError("Location is None", a_stackID, Severity::kError);
			return nullptr;
		}

		return a_childLocation->parentLoc;
	}

	inline void SetParentLocation(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSLocation* a_childLocation,
		RE::BGSLocation* a_newParentLocation)
	{
		if (!a_childLocation) {
			a_vm.PostError("Child Location is None", a_stackID, Severity::kError);
			return;
		}

		if (!a_newParentLocation) {
			a_vm.PostError("New Parent Location is None", a_stackID, Severity::kError);
			return;
		}

		a_childLocation->parentLoc = a_newParentLocation;
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "GetParentLocation", GetParentLocation, true);
		a_vm.BindNativeMethod("Lighthouse", "SetParentLocation", SetParentLocation, true);

		logger::info("Location functions registered.");
	}
}
