#pragma once

namespace Papyrus::Projectile
{
	inline float GetProjectileDataValue(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSProjectile* a_projectile,
		int a_indexValue)
	{
		if (!a_projectile) {
			a_vm.PostError("Projectile is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		switch (a_indexValue) {
		case 1:
			return a_projectile->data.gravity;
		case 2:
			return a_projectile->data.speed;
		case 3:
			return a_projectile->data.range;
		case 4:
			return a_projectile->data.explosionProximity;
		case 5:
			return a_projectile->data.explosionTimer;
		case 6:
			return a_projectile->data.muzzleFlashDuration;
		case 7:
			return a_projectile->data.fadeOutTime;
		case 8:
			return a_projectile->data.force;
		case 9:
			return a_projectile->data.coneSpread;
		case 10:
			return a_projectile->data.collisionRadius;
		case 11:
			return a_projectile->data.lifetime;
		case 12:
			return a_projectile->data.relaunchInterval;
		default:
			a_vm.PostError("Incorrect index", a_stackID, Severity::kError);
			return 0.0f;
		}
	}

	inline void SetProjectileDataValue(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSProjectile* a_projectile,
		int a_indexValue,
		float a_value)
	{
		if (!a_projectile) {
			a_vm.PostError("Projectile is None", a_stackID, Severity::kError);
			return;
		}

		switch (a_indexValue) {
		case 1:
			a_projectile->data.gravity = a_value;
			return;
		case 2:
			a_projectile->data.speed = a_value;
			return;
		case 3:
			a_projectile->data.range = a_value;
			return;
		case 4:
			a_projectile->data.explosionProximity = a_value;
			return;
		case 5:
			a_projectile->data.explosionTimer = a_value;
			return;
		case 6:
			a_projectile->data.muzzleFlashDuration = a_value;
			return;
		case 7:
			a_projectile->data.fadeOutTime = a_value;
			return;
		case 8:
			a_projectile->data.force = a_value;
			return;
		case 9:
			a_projectile->data.coneSpread = a_value;
			return;
		case 10:
			a_projectile->data.collisionRadius = a_value;
			return;
		case 11:
			a_projectile->data.lifetime = a_value;
			return;
		case 12:
			a_projectile->data.relaunchInterval = a_value;
			return;
		default:
			a_vm.PostError("Incorrect index", a_stackID, Severity::kError);
			return;
		}
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "GetProjectileDataValue", GetProjectileDataValue, true);
		a_vm.BindNativeMethod("Lighthouse", "SetProjectileDataValue", SetProjectileDataValue, true);

		logger::info("Projectile functions registered.");
	}
}
