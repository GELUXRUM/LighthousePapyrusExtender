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

	inline std::string GetCellName(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectCELL* a_cell)
	{
		if (!a_cell) {
			a_vm.PostError("Cell is None", a_stackID, Severity::kError);
			return "";
		}

		return a_cell->fullName.c_str();
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

	inline void SetCellName(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectCELL* a_cell,
		std::string a_name)
	{
		if (!a_cell) {
			a_vm.PostError("Cell is None", a_stackID, Severity::kError);
			return;
		}

		a_cell->fullName = a_name;

		return;
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "GetCanWaitInCell", GetCanWaitInCell, true);
		a_vm.BindNativeMethod("Lighthouse", "GetCellName", GetCellName, true);
		a_vm.BindNativeMethod("Lighthouse", "IsExterior", IsExterior, true);
		a_vm.BindNativeMethod("Lighthouse", "SetCellName", SetCellName, true);

		logger::info("Cell functions registered.");
	}
}
