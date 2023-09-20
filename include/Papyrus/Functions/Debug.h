#pragma once

namespace Papyrus::Debug
{
	// BIG NEXUS IS WATCHING YOU
	inline void CrashTheGame(IVM& a_vm, VMStackID a_stackID, std::monostate,
		std::string a_modName,
		std::string a_crashReason)
	{
		if (a_modName.empty()) {
			a_vm.PostError("Mod name cannot be empty!", a_stackID, Severity::kError);
			return;
		}

		if (a_crashReason.empty()) {
			a_vm.PostError("Reason for invoking a CTD cannot be empty!", a_stackID, Severity::kError);
			return;
		}

		std::string callerScriptName{};

		// big thanks to Snapdragon <3
		auto fullVM = static_cast<RE::BSScript::Internal::VirtualMachine*>(&a_vm);
		RE::BSTSmartPointer<RE::BSScript::Stack> stack;
		if (fullVM->GetStackByID(a_stackID, stack)) {
			callerScriptName = stack->top->previousFrame->owningObjectType->GetName();
		}
		
		// required by Nexus to prevent abuse from trolls
		std::string finalMessageString = "The script \"" + callerScriptName + ".pex\" from the mod \"" + a_modName + "\" is invoking a crash to desktop for the following reason: \n\n\"" + a_crashReason + "\"\n\nNote that the mod's name and reason are provided by whoever invoked the CTD and may not be truthful!";

		F4SE::WinAPI::MessageBox(nullptr, finalMessageString.c_str(), "Lighthouse Papyrus Extender", 0x00001000);

		REL::Relocation<RE::NiPointer<RE::PlayerCharacter>*> player{ REL::ID(303410) };
		*player = nullptr;

		return;
	}

	inline void DoNothing(std::monostate)
	{
		return;
	}

	inline std::string GetGameDirectory(IVM& a_vm, VMStackID a_stackID, std::monostate)
	{
		try {
			std::filesystem::path currentPath = std::filesystem::current_path();
			std::string currentPathStr = currentPath.string();
			return currentPathStr;
		} catch (const std::exception& ex) {
			std::string exceptionMessage = std::string("Exception caught: ") + ex.what();
			std::cerr << exceptionMessage;
			a_vm.PostError(exceptionMessage, a_stackID, Severity::kError);
			return "NULL";
		}
	}

	inline std::vector<int> GetLighthouseVersion(std::monostate)
	{
		std::vector<int> versionArray = { 1, 6, 0 };
		return versionArray;
	}

	inline std::vector<int> GetSystemTime(std::monostate)
	{
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		std::tm now_tm;
		localtime_s(&now_tm, &now_c);

		std::vector<int> time_components{
			now_tm.tm_year + 1900,
			now_tm.tm_mon + 1,
			now_tm.tm_mday,
			now_tm.tm_hour,
			now_tm.tm_min,
			now_tm.tm_sec
		};

		return time_components;
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "CrashTheGame", CrashTheGame, true);
		a_vm.BindNativeMethod("Lighthouse", "DoNothing", DoNothing, true);
		a_vm.BindNativeMethod("Lighthouse", "GetGameDirectory", GetGameDirectory, true);
		a_vm.BindNativeMethod("Lighthouse", "GetLighthouseVersion", GetLighthouseVersion, true);
		a_vm.BindNativeMethod("Lighthouse", "GetSystemTime", GetSystemTime, true);

		logger::info("Debug functions registered.");
	}
}
