#pragma once

namespace Papyrus::Faction
{
	inline RE::TESObjectREFR* GetFactionVendorContainerRef(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESFaction* a_faction)
	{
		if (!a_faction) {
			a_vm.PostError("Faction is None", a_stackID, Severity::kError);
			return nullptr;
		}

		RE::TESObjectREFR* vendorContainer = a_faction->vendorData.merchantContainer;

		if (!vendorContainer) {
			a_vm.PostError("Faction has no vendor container", a_stackID, Severity::kError);
			return nullptr;
		}

		return vendorContainer;
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "GetFactionVendorContainerRef", GetFactionVendorContainerRef, true);

		logger::info("Faction functions registered.");
	}
}
