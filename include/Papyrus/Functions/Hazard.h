#pragma once

namespace Papyrus::Hazard
{
	inline void ClearHazardFlag(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard,
		std::uint32_t a_flag)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return;
		}

		a_hazard->data.flags.reset(static_cast<RE::BGSHazardData::BGSHazardFlags>(a_flag));
	}

	inline RE::BSFixedString GetHazardArt(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return {};
		}

		return a_hazard->GetModel();
	}

	inline RE::TESImageSpaceModifier* GetHazardIMOD(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return nullptr;
		}

		return a_hazard->formImageSpaceModifying;
	}

	inline float GetHazardIMODRadius(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		return a_hazard->data.imageSpaceRadius;
	}

	inline RE::BGSImpactDataSet* GetHazardIPDS(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return nullptr;
		}

		return a_hazard->data.impactDataSet;
	}

	inline float GetHazardLifetime(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		return a_hazard->data.lifetime;
	}

	inline RE::TESObjectLIGH* GetHazardLight(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return nullptr;
		}

		return a_hazard->data.light;
	}

	inline std::int32_t GetHazardLimit(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return -1;
		}

		return a_hazard->data.limit;
	}

	inline float GetHazardRadius(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		return a_hazard->data.radius;
	}

	inline RE::BGSSoundDescriptorForm* GetHazardSound(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return nullptr;
		}

		return a_hazard->data.sound;
	}

	inline RE::SpellItem* GetHazardSpell(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return nullptr;
		}

		return a_hazard->data.spell;
	}

	inline float GetHazardTargetInterval(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		return a_hazard->data.targetInterval;
	}

	inline bool IsHazardFlagSet(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard, 
		std::uint32_t a_flag)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return false;
		}

		return a_hazard->data.flags.all(static_cast<RE::BGSHazardData::BGSHazardFlags>(a_flag));
	}

	inline void SetHazardArt(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard,
		RE::BSFixedString a_path)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return;
		}

		a_hazard->SetModel(a_path.data());
	}

	inline void SetHazardFlag(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard,
		std::uint32_t a_flag)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return;
		}

		a_hazard->data.flags.set(static_cast<RE::BGSHazardData::BGSHazardFlags>(a_flag));
	}

	inline void SetHazardIMOD(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard,
		RE::TESImageSpaceModifier* a_imod)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return;
		}

		a_hazard->formImageSpaceModifying = a_imod;
	}

	inline void SetHazardIMODRadius(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard,
		float a_radius)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return;
		}

		a_hazard->data.imageSpaceRadius = a_radius;
	}

	inline void SetHazardIPDS(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard,
		RE::BGSImpactDataSet* a_ipds)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return;
		}

		a_hazard->data.impactDataSet = a_ipds;
	}

	inline void SetHazardLifetime(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard,
		float a_lifetime)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return;
		}

		a_hazard->data.lifetime = a_lifetime;
	}

	inline void SetHazardLight(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard,
		RE::TESObjectLIGH* a_light)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return;
		}

		a_hazard->data.light = a_light;
	}

	inline void SetHazardLimit(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard,
		std::uint32_t a_limit)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return;
		}

		a_hazard->data.limit = a_limit;
	}

	inline void SetHazardRadius(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard,
		float a_radius)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return;
		}

		a_hazard->data.radius = a_radius;
	}

	inline void SetHazardSound(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard,
		RE::BGSSoundDescriptorForm* a_sound)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return;
		}

		a_hazard->data.sound = a_sound;
	}

	inline void SetHazardSpell(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard,
		RE::SpellItem* a_spell)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return;
		}

		a_hazard->data.spell = a_spell;
	}

	inline void SetHazardTargetInterval(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::BGSHazard* a_hazard,
		float a_interval)
	{
		if (!a_hazard) {
			a_vm.PostError("Hazard is None", a_stackID, Severity::kError);
			return;
		}

		a_hazard->data.targetInterval = a_interval;
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "ClearHazardFlag", ClearHazardFlag, true);
		a_vm.BindNativeMethod("Lighthouse", "GetHazardArt", GetHazardArt, true);
		a_vm.BindNativeMethod("Lighthouse", "GetHazardIMOD", GetHazardIMOD, true);
		a_vm.BindNativeMethod("Lighthouse", "GetHazardIMODRadius", GetHazardIMODRadius, true);
		a_vm.BindNativeMethod("Lighthouse", "GetHazardIPDS", GetHazardIPDS, true);
		a_vm.BindNativeMethod("Lighthouse", "GetHazardLifetime", GetHazardLifetime, true);
		a_vm.BindNativeMethod("Lighthouse", "GetHazardLight", GetHazardLight, true);
		a_vm.BindNativeMethod("Lighthouse", "GetHazardLimit", GetHazardLimit, true);
		a_vm.BindNativeMethod("Lighthouse", "GetHazardRadius", GetHazardRadius, true);
		a_vm.BindNativeMethod("Lighthouse", "GetHazardSound", GetHazardSound, true);
		a_vm.BindNativeMethod("Lighthouse", "GetHazardSpell", GetHazardSpell, true);
		a_vm.BindNativeMethod("Lighthouse", "GetHazardTargetInterval", GetHazardTargetInterval, true);
		a_vm.BindNativeMethod("Lighthouse", "IsHazardFlagSet", IsHazardFlagSet, true);
		a_vm.BindNativeMethod("Lighthouse", "SetHazardArt", SetHazardArt, true);
		a_vm.BindNativeMethod("Lighthouse", "SetHazardIMOD", SetHazardIMOD, true);
		a_vm.BindNativeMethod("Lighthouse", "SetHazardIMODRadius", SetHazardIMODRadius, true);
		a_vm.BindNativeMethod("Lighthouse", "SetHazardIPDS", SetHazardIPDS, true);
		a_vm.BindNativeMethod("Lighthouse", "SetHazardLifetime", SetHazardLifetime, true);
		a_vm.BindNativeMethod("Lighthouse", "SetHazardLight", SetHazardLight, true);
		a_vm.BindNativeMethod("Lighthouse", "SetHazardLimit", SetHazardLimit, true);
		a_vm.BindNativeMethod("Lighthouse", "SetHazardRadius", SetHazardRadius, true);
		a_vm.BindNativeMethod("Lighthouse", "SetHazardSound", SetHazardSound, true);
		a_vm.BindNativeMethod("Lighthouse", "SetHazardSpell", SetHazardSpell, true);
		a_vm.BindNativeMethod("Lighthouse", "SetHazardTargetInterval", SetHazardTargetInterval, true);

		logger::info("Hazard functions registered.");
	}

}
