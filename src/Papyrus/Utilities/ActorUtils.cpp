#include <Papyrus\Utilities\ActorUtils.h>

namespace Util
{
	RE::TESNPC* GetBaseNPC(RE::Actor* currActor)
	{
		RE::BSExtraData* extraLvlCreature = currActor->extraList->GetByType(RE::EXTRA_DATA_TYPE::kLeveledCreature);
		if (extraLvlCreature) {
			return *(RE::TESNPC**)((uintptr_t)extraLvlCreature + 0x18);
		}
		return currActor->GetNPC();
	}
}
