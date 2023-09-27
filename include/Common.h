#pragma once

namespace Papyrus
{
	using VM = RE::BSScript::Internal::VirtualMachine;
	using IVM = RE::BSScript::IVirtualMachine;
	using VMStackID = std::uint32_t;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	#define ARGS [[maybe_unused]] IVM& a_vm, [[maybe_unused]] VMStackID a_stackID, std::monostate
}
