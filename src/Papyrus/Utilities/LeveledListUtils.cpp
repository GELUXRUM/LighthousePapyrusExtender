#include <Papyrus\Utilities\LeveledListUtils.h>

namespace Util
{
	RE::TESLeveledList* GetLeveledList(RE::TESForm* frm)
	{
		if (frm == nullptr) {
			return nullptr;
		}

		RE::TESLeveledList* ll;

		auto levChar = frm->As<RE::TESLevCharacter>();
		if (levChar != nullptr) {
			ll = levChar;
			return ll;
		}

		auto levItem = frm->As<RE::TESLevItem>();
		if (levItem != nullptr) {
			ll = levItem;
			return ll;
		}

		auto levSpell = frm->As<RE::TESLevSpell>();
		if (levSpell != nullptr) {
			ll = levSpell;
			return ll;
		}

		return nullptr;
	}
}
