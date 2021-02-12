#pragma once
#include "Settings.h"
#include <map>

using SettingType = std::variant<int, float, bool, ic::TimeStepType, std::string>;

namespace ic {
	class GameSettings : public Settings {
	public:
		GameSettings();
		SettingType getSetting(const std::string& settingname) const override;
		void setSetting(const std::string& settingName, const SettingType settingVal) override;
		std::map<std::string, SettingType> settingsmap;
	};
}