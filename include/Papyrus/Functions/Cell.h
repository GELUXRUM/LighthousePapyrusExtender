#pragma once

namespace Papyrus::Cell
{
	inline bool GetCanWaitInCell(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectCELL* a_cell)
	{
		if (!a_cell) {
			a_vm.PostError("Cell is None", a_stackID, Severity::kError);
			return false;
		}

		return !a_cell->GetCantWaitHere();
	}

	inline bool IsExterior(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectCELL* a_cell)
	{
		if (!a_cell) {
			a_vm.PostError("Cell is None", a_stackID, Severity::kError);
			return false;
		}

		return a_cell->IsExterior();
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "GetCanWaitInCell", GetCanWaitInCell, true);
		a_vm.BindNativeMethod("Lighthouse", "IsExterior", IsExterior, true);

		logger::info("Cell functions registered.");
	}
}
