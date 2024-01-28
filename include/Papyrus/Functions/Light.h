#pragma once

namespace Papyrus::Light
{
	inline float GetLightFade(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectLIGH* a_light)
	{
		if (!a_light) {
			a_vm.PostError("Light is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		return a_light->fade;
	}

	inline float GetLightFOV(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectLIGH* a_light)
	{
		if (!a_light) {
			a_vm.PostError("Light is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		return a_light->data.fov;
	}

	inline std::uint32_t GetLightRadius(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectLIGH* a_light)
	{
		if (!a_light) {
			a_vm.PostError("Light is None", a_stackID, Severity::kError);
			return 0;
		}

		return a_light->data.radius;
	}

	inline std::vector<std::uint32_t> GetLightRGB(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectLIGH* a_light)
	{
		std::vector<std::uint32_t> result(3, 0);

		if (!a_light) {
			a_vm.PostError("Light is None", a_stackID, Severity::kError);
			return result;
		}

		const auto color = a_light->data.color;
		result[0] = color.red;
		result[1] = color.green;
		result[2] = color.blue;

		return result;
	}

	inline std::uint32_t GetLightType(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectLIGH* a_light)
	{
		using FLAGS = RE::TES_LIGHT_FLAGS;

		if (!a_light) {
			a_vm.PostError("Light is None", a_stackID, Severity::kError);
			return 0;
		}

		const auto flags = a_light->data.flags;

		// kNonShadowBox | kNonShadowSpot | kOmniShadow | kHemiShadow | kSpotShadow

		if (flags.none(FLAGS::kNonShadowBox) && flags.none(FLAGS::kNonShadowSpot) && flags.none(FLAGS::kOmniShadow) && flags.none(FLAGS::kHemiShadow) && flags.none(FLAGS::kSpotShadow)) {  // Omni
			return 3;
		}
		if (flags.any(FLAGS::kNonShadowBox)) {
			return 1;
		}
		if (flags.any(FLAGS::kNonShadowSpot)) {
			return 2;
		}
		if (flags.any(FLAGS::kHemiShadow)) {
			return 4;
		}
		if (flags.any(FLAGS::kOmniShadow)) {
			return 5;
		}
		if (flags.any(FLAGS::kSpotShadow)) {
			return 6;
		}

		return 0;
	}

	inline float GetRefLightFOV(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_lightObject)
	{
		if (!a_lightObject) {
			a_vm.PostError("Ref is None", a_stackID, Severity::kError);
			return 1.0f;
		}

		const auto base = a_lightObject->GetObjectReference();
		const auto light = base ? base->As<RE::TESObjectLIGH>() : nullptr;
		if (!light) {
			a_vm.PostError("Ref is not a Light form", a_stackID, Severity::kError);
			return 1.0f;
		}

		const auto xLightData = a_lightObject->extraList.get()->GetByType<RE::ExtraLightData>();
		return xLightData ? xLightData->data.fov : 1.0f;
	}

	inline float GetRefLightFade(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_lightObject)
	{
		if (!a_lightObject) {
			a_vm.PostError("Ref is None", a_stackID, Severity::kError);
			return 1.0f;
		}

		const auto base = a_lightObject->GetObjectReference();
		const auto light = base ? base->As<RE::TESObjectLIGH>() : nullptr;
		if (!light) {
			a_vm.PostError("Ref is not a Light form", a_stackID, Severity::kError);
			return 1.0f;
		}

		const auto xLightData = a_lightObject->extraList.get()->GetByType<RE::ExtraLightData>();
		return xLightData ? xLightData->data.fade : 1.0f;
	}

	inline float GetRefLightEndDistanceCap(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_lightObject)
	{
		if (!a_lightObject) {
			a_vm.PostError("Ref is None", a_stackID, Severity::kError);
			return 1.0f;
		}

		const auto base = a_lightObject->GetObjectReference();
		const auto light = base ? base->As<RE::TESObjectLIGH>() : nullptr;
		if (!light) {
			a_vm.PostError("Ref is not a Light form", a_stackID, Severity::kError);
			return 1.0f;
		}

		const auto xLightData = a_lightObject->extraList.get()->GetByType<RE::ExtraLightData>();
		return xLightData ? xLightData->data.endDistanceCap : 1.0f;
	}

	inline float GetRefLightShadowDepthBias(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_lightObject)
	{
		if (!a_lightObject) {
			a_vm.PostError("Ref is None", a_stackID, Severity::kError);
			return 1.0f;
		}

		const auto base = a_lightObject->GetObjectReference();
		const auto light = base ? base->As<RE::TESObjectLIGH>() : nullptr;
		if (!light) {
			a_vm.PostError("Ref is not a Light form", a_stackID, Severity::kError);
			return 1.0f;
		}

		const auto xLightData = a_lightObject->extraList.get()->GetByType<RE::ExtraLightData>();
		return xLightData ? xLightData->data.shadowDepthBias : 1.0f;
	}

	inline float GetRefLightSpotNear(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_lightObject)
	{
		if (!a_lightObject) {
			a_vm.PostError("Ref is None", a_stackID, Severity::kError);
			return 1.0f;
		}

		const auto base = a_lightObject->GetObjectReference();
		const auto light = base ? base->As<RE::TESObjectLIGH>() : nullptr;
		if (!light) {
			a_vm.PostError("Ref is not a Light form", a_stackID, Severity::kError);
			return 1.0f;
		}

		const auto xLightData = a_lightObject->extraList.get()->GetByType<RE::ExtraLightData>();
		return xLightData ? xLightData->data.spotNear : 1.0f;
	}

	inline float GetRefLightVolumetricIntensity(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_lightObject)
	{
		if (!a_lightObject) {
			a_vm.PostError("Ref is None", a_stackID, Severity::kError);
			return 1.0f;
		}

		const auto base = a_lightObject->GetObjectReference();
		const auto light = base ? base->As<RE::TESObjectLIGH>() : nullptr;
		if (!light) {
			a_vm.PostError("Ref is not a Light form", a_stackID, Severity::kError);
			return 1.0f;
		}

		const auto xLightData = a_lightObject->extraList.get()->GetByType<RE::ExtraLightData>();
		return xLightData ? xLightData->data.volumetricIntensity : 1.0f;
	}

	inline void SetLightFade(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectLIGH* a_light,
		float a_fade)
	{
		if (!a_light) {
			a_vm.PostError("Light is None", a_stackID, Severity::kError);
			return;
		}

		a_light->fade = a_fade;
	}

	inline void SetLightFOV(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectLIGH* a_light,
		float a_fov)
	{
		if (!a_light) {
			a_vm.PostError("Light is None", a_stackID, Severity::kError);
			return;
		}

		a_light->data.fov = a_fov;
	}

	inline void SetLightRadius(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectLIGH* a_light,
		float a_radius)
	{
		if (!a_light) {
			a_vm.PostError("Light is None", a_stackID, Severity::kError);
			return;
		}

		a_light->data.radius = static_cast<std::uint32_t>(a_radius);
	}

	inline void SetLightRGB(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectLIGH* a_light,
		std::vector<std::int32_t> a_rgb)
	{
		if (!a_light) {
			a_vm.PostError("Light is None", a_stackID, Severity::kError);
			return;
		}

		if (a_rgb.size() < 3) {
			a_vm.PostError("RGB array is empty", a_stackID, Severity::kError);
			return;
		}

		auto& color = a_light->data.color;
		color.red = static_cast<std::uint8_t>(a_rgb[0]);

		color.green = static_cast<std::uint8_t>(a_rgb[1]);

		color.blue  = static_cast<std::uint8_t>(a_rgb[2]);
	}

	inline void SetLightType(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectLIGH* a_light,
		std::uint32_t a_type)
	{
		using FLAGS = RE::TES_LIGHT_FLAGS;

		if (!a_light) {
			a_vm.PostError("Light is None", a_stackID, Severity::kError);
			return;
		}

		auto& flags = a_light->data.flags;
		switch (a_type) {
		case 1:
			{
				flags.reset(FLAGS::kNonShadowSpot, FLAGS::kOmniShadow, FLAGS::kHemiShadow, FLAGS::kSpotShadow);
				flags.set(FLAGS::kNonShadowBox);
			}
			break;
		case 2:
			{
				flags.reset(FLAGS::kNonShadowBox, FLAGS::kOmniShadow, FLAGS::kHemiShadow, FLAGS::kSpotShadow);
				flags.set(FLAGS::kNonShadowSpot);
			}
			break;
		case 3:
			{
				flags.reset(FLAGS::kNonShadowBox, FLAGS::kNonShadowSpot, FLAGS::kOmniShadow, FLAGS::kHemiShadow, FLAGS::kSpotShadow);
			}
			break;
		case 4:
			{
				flags.reset(FLAGS::kNonShadowBox, FLAGS::kNonShadowSpot, FLAGS::kOmniShadow, FLAGS::kSpotShadow);
				flags.set(FLAGS::kHemiShadow);
			}
			break;
		case 5:
			{
				flags.reset(FLAGS::kNonShadowBox, FLAGS::kNonShadowSpot, FLAGS::kHemiShadow, FLAGS::kSpotShadow);
				flags.set(FLAGS::kOmniShadow);
			}
			break;
		case 6:
			{
				flags.reset(FLAGS::kNonShadowBox, FLAGS::kNonShadowSpot, FLAGS::kOmniShadow, FLAGS::kHemiShadow);
				flags.set(FLAGS::kSpotShadow);
			}
		default:
			break;
		}

	}
	
	inline void SetRefLightFade(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_lightObject,
		float a_fade)
	{
		if (!a_lightObject) {
			a_vm.PostError("Ref is None", a_stackID, Severity::kError);
			return;
		}

		const auto base = a_lightObject->GetObjectReference();
		const auto light = base ? base->As<RE::TESObjectLIGH>() : nullptr;
		if (!light) {
			a_vm.PostError("Ref is not a Light form", a_stackID, Severity::kError);
			return;
		}

		if (const auto xLightData = a_lightObject->extraList->GetByType<RE::ExtraLightData>(); xLightData) {
			xLightData->data.fade = a_fade;
		} else {
			if (const auto newLightData = new RE::ExtraLightData(); newLightData) {
				newLightData->data.fade = a_fade;
				a_lightObject->extraList->AddExtra(newLightData);
			}
		}
	}

	inline void SetRefLightFOV(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_lightObject,
		float a_fov)
	{
		if (!a_lightObject) {
			a_vm.PostError("Ref is None", a_stackID, Severity::kError);
			return;
		}

		const auto base = a_lightObject->GetObjectReference();
		const auto light = base ? base->As<RE::TESObjectLIGH>() : nullptr;
		if (!light) {
			a_vm.PostError("Ref is not a Light form", a_stackID, Severity::kError);
			return;
		}

		if (const auto xLightData = a_lightObject->extraList->GetByType<RE::ExtraLightData>(); xLightData) {
			xLightData->data.fov = a_fov;
		} else {
			if (const auto newLightData = new RE::ExtraLightData(); newLightData) {
				newLightData->data.fov = a_fov;
				a_lightObject->extraList->AddExtra(newLightData);
			}
		}
	}

	inline void SetRefLightEndDistanceCap(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_lightObject,
		float a_endDistanceCap)
	{
		if (!a_lightObject) {
			a_vm.PostError("Ref is None", a_stackID, Severity::kError);
			return;
		}

		const auto base = a_lightObject->GetObjectReference();
		const auto light = base ? base->As<RE::TESObjectLIGH>() : nullptr;
		if (!light) {
			a_vm.PostError("Ref is not a Light form", a_stackID, Severity::kError);
			return;
		}

		if (const auto xLightData = a_lightObject->extraList->GetByType<RE::ExtraLightData>(); xLightData) {
			xLightData->data.endDistanceCap = a_endDistanceCap;
		} else {
			if (const auto newLightData = new RE::ExtraLightData(); newLightData) {
				newLightData->data.endDistanceCap = a_endDistanceCap;
				a_lightObject->extraList->AddExtra(newLightData);
			}
		}
	}

	inline void SetRefLightShadowDepthBias(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_lightObject,
		float a_depthBias)
	{
		if (!a_lightObject) {
			a_vm.PostError("Ref is None", a_stackID, Severity::kError);
			return;
		}

		const auto base = a_lightObject->GetObjectReference();
		const auto light = base ? base->As<RE::TESObjectLIGH>() : nullptr;
		if (!light) {
			a_vm.PostError("Ref is not a Light form", a_stackID, Severity::kError);
			return;
		}

		if (const auto xLightData = a_lightObject->extraList->GetByType<RE::ExtraLightData>(); xLightData) {
			xLightData->data.shadowDepthBias = a_depthBias;
		} else {
			if (const auto newLightData = new RE::ExtraLightData(); newLightData) {
				newLightData->data.shadowDepthBias = a_depthBias;
				a_lightObject->extraList->AddExtra(newLightData);
			}
		}
	}

	inline void SetRefLightSpotNear(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_lightObject,
		float a_spotNear)
	{
		if (!a_lightObject) {
			a_vm.PostError("Ref is None", a_stackID, Severity::kError);
			return;
		}

		const auto base = a_lightObject->GetObjectReference();
		const auto light = base ? base->As<RE::TESObjectLIGH>() : nullptr;
		if (!light) {
			a_vm.PostError("Ref is not a Light form", a_stackID, Severity::kError);
			return;
		}

		if (const auto xLightData = a_lightObject->extraList->GetByType<RE::ExtraLightData>(); xLightData) {
			xLightData->data.spotNear = a_spotNear;
		} else {
			if (const auto newLightData = new RE::ExtraLightData(); newLightData) {
				newLightData->data.spotNear = a_spotNear;
				a_lightObject->extraList->AddExtra(newLightData);
			}
		}
	}

	inline void SetRefLightVolumetricIntensity(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::TESObjectREFR* a_lightObject,
		float a_volumetricIntensity)
	{
		if (!a_lightObject) {
			a_vm.PostError("Ref is None", a_stackID, Severity::kError);
			return;
		}

		const auto base = a_lightObject->GetObjectReference();
		const auto light = base ? base->As<RE::TESObjectLIGH>() : nullptr;
		if (!light) {
			a_vm.PostError("Ref is not a Light form", a_stackID, Severity::kError);
			return;
		}

		if (const auto xLightData = a_lightObject->extraList->GetByType<RE::ExtraLightData>(); xLightData) {
			xLightData->data.volumetricIntensity = a_volumetricIntensity;
		} else {
			if (const auto newLightData = new RE::ExtraLightData(); newLightData) {
				newLightData->data.volumetricIntensity = a_volumetricIntensity;
				a_lightObject->extraList->AddExtra(newLightData);
			}
		}
	}

	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "GetLightFade", GetLightFade, true);
		a_vm.BindNativeMethod("Lighthouse", "GetLightFOV", GetLightFOV, true);
		a_vm.BindNativeMethod("Lighthouse", "GetLightRadius", GetLightRadius, true);
		a_vm.BindNativeMethod("Lighthouse", "GetLightRGB", GetLightRGB, true);
		a_vm.BindNativeMethod("Lighthouse", "GetLightType", GetLightType, true);
		a_vm.BindNativeMethod("Lighthouse", "GetRefLightFOV", GetRefLightFOV, true);
		a_vm.BindNativeMethod("Lighthouse", "GetRefLightFade", GetRefLightFade, true);
		a_vm.BindNativeMethod("Lighthouse", "GetRefLightEndDistanceCap", GetRefLightEndDistanceCap, true);
		a_vm.BindNativeMethod("Lighthouse", "GetRefLightShadowDepthBias", GetRefLightShadowDepthBias, true);
		a_vm.BindNativeMethod("Lighthouse", "GetRefLightSpotNear", GetRefLightSpotNear, true);
		a_vm.BindNativeMethod("Lighthouse", "GetRefLightVolumetricIntensity", GetRefLightVolumetricIntensity, true);
		a_vm.BindNativeMethod("Lighthouse", "SetLightFade", SetLightFade, true);
		a_vm.BindNativeMethod("Lighthouse", "SetLightFOV", SetLightFOV, true);
		a_vm.BindNativeMethod("Lighthouse", "SetLightRadius", SetLightRadius, true);
		a_vm.BindNativeMethod("Lighthouse", "SetLightRGB", SetLightRGB, true);
		a_vm.BindNativeMethod("Lighthouse", "SetLightType", SetLightType, true);
		a_vm.BindNativeMethod("Lighthouse", "SetRefLightFade", SetRefLightFade, true);
		a_vm.BindNativeMethod("Lighthouse", "SetRefLightFOV", SetRefLightFOV, true);
		a_vm.BindNativeMethod("Lighthouse", "SetRefLightEndDistanceCap", SetRefLightEndDistanceCap, true);
		a_vm.BindNativeMethod("Lighthouse", "SetRefLightShadowDepthBias", SetRefLightShadowDepthBias, true);
		a_vm.BindNativeMethod("Lighthouse", "SetRefLightSpotNear", SetRefLightSpotNear, true);
		a_vm.BindNativeMethod("Lighthouse", "SetRefLightVolumetricIntensity", SetRefLightVolumetricIntensity, true);

		logger::info("Light functions registered.");
	}
}
