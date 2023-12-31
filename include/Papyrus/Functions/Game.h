#pragma once

namespace Papyrus::Game
{
	inline std::vector<RE::Actor*> GetActorsByProcessingLevel(IVM& a_vm, VMStackID a_stackID, std::monostate,
		std::int32_t a_level)
	{
		std::vector<RE::Actor*> result;

		if (const auto processLists = RE::ProcessLists::GetSingleton(); processLists) {
			RE::BSTArray<RE::ActorHandle>* arr = nullptr;

			switch (a_level) {
			case 0:
				arr = &processLists->highActorHandles;
				break;
			case 1:
				arr = &processLists->middleHighActorHandles;
				break;
			case 2:
				arr = &processLists->middleLowActorHandles;
				break;
			case 3:
				arr = &processLists->lowActorHandles;
				break;
			default:
				a_vm.PostError("Incorrect index", a_stackID, Severity::kError);
				break;
			}

			if (arr) {
				for (auto& actorHandle : *arr) {
					auto actorPtr = actorHandle.get();
					if (auto actor = actorPtr.get(); actor) {
						result.push_back(actor);
					}
				}
			}
		}

		return result;
	}

	inline std::int32_t GetNumActorsInHigh(std::monostate)
	{
		const auto processLists = RE::ProcessLists::GetSingleton();
		return processLists ? processLists->numberHighActors : -1;
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "GetActorsByProcessingLevel", GetActorsByProcessingLevel, true);
		a_vm.BindNativeMethod("Lighthouse", "GetNumActorsInHigh", GetNumActorsInHigh, true);

		logger::info("Game functions registered.");
	}
}
