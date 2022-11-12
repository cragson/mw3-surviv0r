#pragma once

#include "osmium/Cheat/Feature/feature.hpp"

class ft_aimbot : public feature
{
public:

	ft_aimbot() : m_aim_x(-1), m_aim_y(-1) {}

	void on_first_activation() override {}

	void on_enable() override {}

	void on_disable() override {}

	void tick() override;

	void on_render() override;

private:

	int32_t m_aim_x;
	int32_t m_aim_y;
};
