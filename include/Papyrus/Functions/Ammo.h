#pragma once

namespace Papyrus::Ammo
{
	inline float GetAmmoDamage(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESAmmo* a_ammo)
	{
		if (!a_ammo) {
			a_vm.PostError("Ammo is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		return a_ammo->data.damage;
	}

	inline RE::BGSProjectile* GetAmmoProjectile(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESAmmo* a_ammo)
	{
		if (!a_ammo) {
			a_vm.PostError("Ammo is None", a_stackID, Severity::kError);
			return nullptr;
		}

		return a_ammo->data.projectile;
	}

	inline void SetAmmoDamage(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESAmmo* a_ammo,
		float a_damage)
	{
		if (!a_ammo) {
			a_vm.PostError("Ammo is None", a_stackID, Severity::kError);
			return;
		}

		a_ammo->data.damage = a_damage;
	}

	inline void SetAmmoProjectile(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESAmmo* a_ammo,
		RE::BGSProjectile* a_projectile)
	{
		if (!a_ammo) {
			a_vm.PostError("Ammo is None", a_stackID, Severity::kError);
			return;
		}

		if (!a_projectile) {
			a_vm.PostError("Projectile is None", a_stackID, Severity::kError);
			return;
		}

		a_ammo->data.projectile = a_projectile;
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "GetAmmoDamage", GetAmmoDamage, true);
		a_vm.BindNativeMethod("Lighthouse", "GetAmmoProjectile", GetAmmoProjectile, true);
		a_vm.BindNativeMethod("Lighthouse", "SetAmmoDamage", SetAmmoDamage, true);
		a_vm.BindNativeMethod("Lighthouse", "SetAmmoProjectile", SetAmmoProjectile, true);

		logger::info("Ammo functions registered.");
	}
}
