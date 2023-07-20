#include "Papyrus/Utilities/FunctionArgs.h"

#pragma once

namespace Util
{
	template <typename T, class... Args>
	static void CallPapyrusFunctionOnForm(T* a_form, std::string a_scriptName, std::string a_funcName, Args... _args)
	{
		auto* vm = RE::GameVM::GetSingleton()->GetVM().get();
		auto& handlePolicy = vm->GetObjectHandlePolicy();
		auto scrapFunc = (Papyrus::FunctionArgs{ vm, _args... }).get();

		uint64_t handle = handlePolicy.GetHandleForObject(RE::BSScript::GetVMTypeID<T>(), a_form);
		vm->DispatchMethodCall(handle, a_scriptName, a_funcName, scrapFunc, nullptr);

		handlePolicy.ReleaseHandle(handle);
	}

	template <class... Args>
	static void CallGlobalPapyrusFunction(std::string a_scriptName, std::string a_funcName, Args... _args)
	{
		auto* vm = RE::GameVM::GetSingleton()->GetVM().get();
		auto scrapFunc = (Papyrus::FunctionArgs{ vm, _args... }).get();

		vm->DispatchStaticCall(a_scriptName, a_funcName, scrapFunc, nullptr);
	}

	template <class... Args>
	static void SendPapyrusEvent(std::string a_eventName, Args... _args)
	{
		struct PapyrusEventData
		{
			RE::BSScript::IVirtualMachine* vm;
			RE::BSTThreadScrapFunction<bool(RE::BSScrapArray<RE::BSScript::Variable>&)> scrapFunc;
		};

		PapyrusEventData evntData;
		auto const papyrus = F4SE::GetPapyrusInterface();
		auto* vm = RE::GameVM::GetSingleton()->GetVM().get();

		evntData.scrapFunc = (Papyrus::FunctionArgs{ vm, _args... }).get();
		evntData.vm = vm;

		papyrus->GetExternalEventRegistrations(a_eventName, &evntData, [](uint64_t handle, const char* scriptName, const char* callbackName, void* dataPtr) {
			PapyrusEventData* d = static_cast<PapyrusEventData*>(dataPtr);
			d->vm->DispatchMethodCall(handle, scriptName, callbackName, d->scrapFunc, nullptr);
		});
	}
}
