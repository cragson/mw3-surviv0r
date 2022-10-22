#pragma once
#include "osmium/Cheat/Feature/feature.hpp"

#include "offsets.hpp"
#include "globals.hpp"

class ft_fovchanger : public feature
{
public:
	void on_first_activation() override {}

	void on_enable() override {}

	void on_disable() override {}

	void on_render() override {}

	void tick() override
	{
		const auto ptr = Globals::g_pProcess->read< std::uintptr_t >( Offsets::cgfov_ptr );

		const auto fov = Globals::g_pProcess->read< float >( ptr + 0xC );

		if( Globals::g_pMenu->get_value_of_setting< bool >( "Other", "Increased FoV" ) )
		{
			if( fov != 100.f )
				Globals::g_pProcess->write< float >( ptr + 0xC, 100.f );
		}
		else if( fov != 65.f )
			Globals::g_pProcess->write< float >( ptr + 0xC, 65.f );
	}
};
