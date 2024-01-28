#include "Papyrus/Manager.h"

#include "Papyrus/Functions/ActiveEffect.h"
#include "Papyrus/Functions/Actor.h"
#include "Papyrus/Functions/ActorBase.h"
#include "Papyrus/Functions/ActorValue.h"
#include "Papyrus/Functions/Ammo.h"
#include "Papyrus/Functions/Armor.h"
#include "Papyrus/Functions/Array.h"
#include "Papyrus/Functions/Book.h"
#include "Papyrus/Functions/Cell.h"
#include "Papyrus/Functions/CombatStyle.h"
#include "Papyrus/Functions/Debug.h"
#include "Papyrus/Functions/Faction.h"
#include "Papyrus/Functions/Form.h"
#include "Papyrus/Functions/Game.h"
#include "Papyrus/Functions/Hazard.h"
#include "Papyrus/Functions/Keyword.h"
#include "Papyrus/Functions/LeveledList.h"
#include "Papyrus/Functions/Light.h"
#include "Papyrus/Functions/Location.h"
#include "Papyrus/Functions/Math.h"
#include "Papyrus/Functions/ObjectReference.h"
#include "Papyrus/Functions/PlayerCharacter.h"
#include "Papyrus/Functions/Projectile.h"
#include "Papyrus/Functions/String.h"
#include "Papyrus/Functions/UI.h"
#include "Papyrus/Functions/VATS.h"
#include "Papyrus/Functions/Weapon.h"
#include "Papyrus/Functions/Weather.h"

namespace Papyrus
{
	bool RegisterFunctions(IVM* a_vm)
	{
		if (!a_vm) {
			logger::info("Fail LMAO");
		}

		logger::info("{:*^30}", "FUNCTIONS"sv);

		ActiveEffect::Bind(*a_vm);
		Actor::Bind(*a_vm);
		ActorBase::Bind(*a_vm);
		ActorValue::Bind(*a_vm);
		Ammo::Bind(*a_vm);
		Armor::Bind(*a_vm);
		Array::Bind(*a_vm);
		Book::Bind(*a_vm);
		Cell::Bind(*a_vm);
		CombatStyle::Bind(*a_vm);
		Debug::Bind(*a_vm);
		Faction::Bind(*a_vm);
		Form::Bind(*a_vm);
		Game::Bind(*a_vm);
		Hazard::Bind(*a_vm);
		Keyword::Bind(*a_vm);
		LeveledList::Bind(*a_vm);
		Light::Bind(*a_vm);
		Location::Bind(*a_vm);
		Math::Bind(*a_vm);
		ObjectReference::Bind(*a_vm);
		PlayerCharacter::Bind(*a_vm);
		Projectile::Bind(*a_vm);
		String::Bind(*a_vm);
		UI::Bind(*a_vm);
		VATS::Bind(*a_vm);
		//Weapon::Bind(*a_vm);
		Weather::Bind(*a_vm);

		return true;
	}
}
