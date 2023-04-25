#pragma once

#include "osmium/Cheat/Feature/feature.hpp"


class esp_data
{
public:
	int32_t ax, by;
	int32_t health, health_max;
	bool was_drawn;
};

class ft_esp : public feature
{
public:
	void on_first_activation() override {}

	void on_enable() override {}

	void on_disable() override {}

	void tick() override;

	void on_render() override;

	void on_shutdown() override {}
};
