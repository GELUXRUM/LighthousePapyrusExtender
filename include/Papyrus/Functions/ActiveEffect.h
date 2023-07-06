#pragma once

namespace Papyrus::ActiveEffect
{
	inline float GetDuration(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		RE::TESForm* a_effectForm)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		if (!a_effectForm) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		if (a_effectForm->formType != RE::ENUM_FORM_ID::kActiveEffect) {
			a_vm.PostError("Form is not of ActiveEffect type", a_stackID, Severity::kError);
			return 0.0f;
		}

		RE::ActiveEffectList* aeList = a_actor->GetActiveEffectList();
		if (!aeList) {
			return 0.0f;
		}
		for (auto it = aeList->data.begin(); it != aeList->data.end(); ++it) {
			if (it->get() && it->get()->effect) {
				RE::EffectSetting* avEffectSetting = *(RE::EffectSetting**)((uint64_t)(it->get()->effect) + 0x10);
				if (avEffectSetting && avEffectSetting == a_effectForm) {
					return it->get()->duration;
				}
			}
		}
		return 0.0f;
	}

	inline float GetElapsedTime(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		RE::TESForm* a_effectForm)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		if (!a_effectForm) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		RE::ActiveEffectList* aeList = a_actor->GetActiveEffectList();
		if (!aeList) {
			return 0.0f;
		}
		for (auto it = aeList->data.begin(); it != aeList->data.end(); ++it) {
			if (it->get() && it->get()->effect) {
				RE::EffectSetting* avEffectSetting = *(RE::EffectSetting**)((uint64_t)(it->get()->effect) + 0x10);
				if (avEffectSetting && avEffectSetting == a_effectForm) {
					return it->get()->elapsed;
				}
			}
		}
		return 0.0f;
	}

	inline float GetMagnitude(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		RE::TESForm* a_effectForm)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		if (!a_effectForm) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return 0.0f;
		}

		RE::ActiveEffectList* aeList = a_actor->GetActiveEffectList();
		if (!aeList) {
			return 0.0f;
		}
		for (auto it = aeList->data.begin(); it != aeList->data.end(); ++it) {
			if (it->get() && it->get()->effect) {
				RE::EffectSetting* avEffectSetting = *(RE::EffectSetting**)((uint64_t)(it->get()->effect) + 0x10);
				if (avEffectSetting && avEffectSetting == a_effectForm) {
					return it->get()->magnitude;
				}
			}
		}
		return 0.0f;
	}

	inline void SetDuration(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		RE::TESForm* a_effectForm,
		float a_duration)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return;
		}

		if (!a_effectForm) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return;
		}

		RE::ActiveEffectList* aeList = a_actor->GetActiveEffectList();
		if (!aeList) {
			return;
		}
		for (auto it = aeList->data.begin(); it != aeList->data.end(); ++it) {
			if (it->get() && it->get()->effect) {
				RE::EffectSetting* avEffectSetting = *(RE::EffectSetting**)((uint64_t)(it->get()->effect) + 0x10);
				if (avEffectSetting && avEffectSetting == a_effectForm) {
					it->get()->duration = a_duration;
					return;
				}
			}
		}
		return;
	}

	inline void SetElapsedTime(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		RE::TESForm* a_effectForm,
		float a_elapsed)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return;
		}

		if (!a_effectForm) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return;
		}

		RE::ActiveEffectList* aeList = a_actor->GetActiveEffectList();
		if (!aeList) {
			return;
		}
		for (auto it = aeList->data.begin(); it != aeList->data.end(); ++it) {
			if (it->get() && it->get()->effect) {
				RE::EffectSetting* avEffectSetting = *(RE::EffectSetting**)((uint64_t)(it->get()->effect) + 0x10);
				if (avEffectSetting && avEffectSetting == a_effectForm) {
					it->get()->elapsed = a_elapsed;
					return;
				}
			}
		}
		return;
	}

	inline void SetMagnitude(IVM& a_vm, VMStackID a_stackID, std::monostate,
		RE::Actor* a_actor,
		RE::TESForm* a_effectForm,
		float a_magnitude)
	{
		if (!a_actor) {
			a_vm.PostError("Actor is None", a_stackID, Severity::kError);
			return;
		}

		if (!a_effectForm) {
			a_vm.PostError("Form is None", a_stackID, Severity::kError);
			return;
		}

		RE::ActiveEffectList* aeList = a_actor->GetActiveEffectList();
		if (!aeList) {
			return;
		}
		for (auto it = aeList->data.begin(); it != aeList->data.end(); ++it) {
			if (it->get() && it->get()->effect) {
				RE::EffectSetting* avEffectSetting = *(RE::EffectSetting**)((uint64_t)(it->get()->effect) + 0x10);
				if (avEffectSetting && avEffectSetting == a_effectForm) {
					it->get()->magnitude = a_magnitude;
					return;
				}
			}
		}
		return;
	}
	
	inline void Bind(IVM& a_vm)
	{
		a_vm.BindNativeMethod("Lighthouse", "GetDuration", GetDuration, true);
		a_vm.BindNativeMethod("Lighthouse", "GetElapsedTime", GetElapsedTime, true);
		a_vm.BindNativeMethod("Lighthouse", "GetMagnitude", GetMagnitude, true);
		//a_vm.BindNativeMethod("Lighthouse", "SetDuration", SetDuration, true);
		//a_vm.BindNativeMethod("Lighthouse", "SetElapsedTime", SetElapsedTime, true);
		//a_vm.BindNativeMethod("Lighthouse", "SetMagnitude", SetMagnitude, true);

		logger::info("ActiveEffect functions registered.");
	}
}
