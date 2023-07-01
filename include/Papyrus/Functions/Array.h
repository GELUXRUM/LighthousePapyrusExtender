#pragma once

namespace Papyrus::Array
{
	template <typename T>
	inline std::vector<T> CreateArray(std::monostate,
		std::uint32_t a_arrSize,
		T a_arrFill)
	{
		std::vector<T> newArray(a_arrSize, a_arrFill);

		return newArray;
	}

	template <typename T>
	inline std::vector<T> ResizeArray(std::monostate,
		std::vector<T> a_sourceArray,
		std::uint32_t a_arrSize,
		T a_arrFill)
	{
		a_sourceArray.resize(a_arrSize, a_arrFill);
		return a_sourceArray;
	}

	inline std::vector<float> SortArrayFloat(IVM& a_vm, VMStackID a_stackID, std::monostate,
		std::vector<float> a_arrayToSort,
		bool a_sortDescending,
		int a_startIndex,
		int a_endIndex)
	{
		if (a_endIndex < 0) {
			a_endIndex = static_cast<int>(a_arrayToSort.size()) - 1;
		}

		if (a_startIndex < 0 || a_endIndex >= a_arrayToSort.size() || a_startIndex >= a_endIndex) {
			a_vm.PostError("Function arguments are either incorrect or have conflicting values", a_stackID, Severity::kError);
			return a_arrayToSort;
		}

		if (a_sortDescending) {
			std::sort(a_arrayToSort.begin() + a_startIndex, a_arrayToSort.begin() + a_endIndex + 1, std::greater<float>());
		} else {
			std::sort(a_arrayToSort.begin() + a_startIndex, a_arrayToSort.begin() + a_endIndex + 1);
		}

		return a_arrayToSort;
	}

	inline std::vector<int> SortArrayInt(IVM& a_vm, VMStackID a_stackID, std::monostate,
		std::vector<int> a_arrayToSort,
		bool a_sortDescending,
		int a_startIndex,
		int a_endIndex)
	{
		// Convenience thing in case finding the length is a pain
		if (a_endIndex < 0) {
			// Cast as int because compiler cries about data loss. Boo hoo stfu...
			a_endIndex = static_cast<int>(a_arrayToSort.size()) - 1;
		}
		if (a_startIndex < 0 || a_endIndex >= a_arrayToSort.size() || a_startIndex >= a_endIndex) {
			a_vm.PostError("Function arguments are either incorrect or have conflicting values", a_stackID, Severity::kError);
			return a_arrayToSort;
		}
		if (a_sortDescending) {
			std::sort(a_arrayToSort.begin() + a_startIndex, a_arrayToSort.begin() + a_endIndex + 1, std::greater<int>());
		} else {
			std::sort(a_arrayToSort.begin() + a_startIndex, a_arrayToSort.begin() + a_endIndex + 1);
		}

		return a_arrayToSort;
	}

	inline std::vector<std::string> SortArrayString(IVM& a_vm, VMStackID a_stackID, std::monostate,
		std::vector<std::string> a_arrayToSort,
		bool a_sortDescending,
		int a_startIndex,
		int a_endIndex)
	{
		if (a_endIndex < 0) {
			a_endIndex = static_cast<int>(a_arrayToSort.size()) - 1;
		}

		if (a_startIndex < 0 || a_endIndex >= a_arrayToSort.size() || a_startIndex >= a_endIndex) {
			a_vm.PostError("Function arguments are either incorrect or have conflicting values", a_stackID, Severity::kError);
			return a_arrayToSort;
		}

		if (a_sortDescending) {
			std::sort(a_arrayToSort.begin() + a_startIndex, a_arrayToSort.begin() + a_endIndex + 1, std::greater<std::string>());
		} else {
			std::sort(a_arrayToSort.begin() + a_startIndex, a_arrayToSort.begin() + a_endIndex + 1);
		}

		return a_arrayToSort;
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "CreateArrayActor", CreateArray<RE::Actor*>, true);
		a_vm.BindNativeMethod("Lighthouse", "CreateArrayBool", CreateArray<bool>, true);
		a_vm.BindNativeMethod("Lighthouse", "CreateArrayCOBJ", CreateArray<RE::BGSConstructibleObject*>, true);
		a_vm.BindNativeMethod("Lighthouse", "CreateArrayFloat", CreateArray<float>, true);
		a_vm.BindNativeMethod("Lighthouse", "CreateArrayForm", CreateArray<RE::TESForm*>, true);
		a_vm.BindNativeMethod("Lighthouse", "CreateArrayInt", CreateArray<int>, true);
		a_vm.BindNativeMethod("Lighthouse", "CreateArrayRef", CreateArray<RE::TESObjectREFR*>, true);
		a_vm.BindNativeMethod("Lighthouse", "CreateArrayString", CreateArray<RE::BSFixedString>, true);
		a_vm.BindNativeMethod("Lighthouse", "ResizeArrayActor", ResizeArray<RE::Actor*>, true);
		a_vm.BindNativeMethod("Lighthouse", "ResizeArrayBool", ResizeArray<bool>, true);
		a_vm.BindNativeMethod("Lighthouse", "ResizeArrayCOBJ", ResizeArray<RE::BGSConstructibleObject*>, true);
		a_vm.BindNativeMethod("Lighthouse", "ResizeArrayFloat", ResizeArray<float>, true);
		a_vm.BindNativeMethod("Lighthouse", "ResizeArrayForm", ResizeArray<RE::TESForm*>, true);
		a_vm.BindNativeMethod("Lighthouse", "ResizeArrayInt", ResizeArray<int>, true);
		a_vm.BindNativeMethod("Lighthouse", "ResizeArrayString", ResizeArray<RE::BSFixedString>, true);
		a_vm.BindNativeMethod("Lighthouse", "ResizeArrayRef", ResizeArray<RE::TESObjectREFR*>, true);
		a_vm.BindNativeMethod("Lighthouse", "SortArrayFloat", SortArrayFloat, true);
		a_vm.BindNativeMethod("Lighthouse", "SortArrayInt", SortArrayInt, true);
		a_vm.BindNativeMethod("Lighthouse", "SortArrayString", SortArrayString, true);

		logger::info("Array functions registered.");
	}
}
