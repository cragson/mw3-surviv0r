#pragma once
#include "osmium/Cheat/Feature/feature.hpp"

#include "offsets.hpp"
#include "globals.hpp"

class ft_funmode : public feature
{
public:
	void on_first_activation() override {}

	void on_render() override {}

	void on_enable() override {}

	void on_disable() override {}

	void on_shutdown() override {}

	void tick() override
	{
		const auto speedptr = Globals::g_pProcess->read< std::uintptr_t >( Offsets::speed_ptr );

		const auto speed = Globals::g_pProcess->read< int32_t >( speedptr + 0xC );

		const auto gravityptr = Globals::g_pProcess->read< std::uintptr_t >( Offsets::gravity_ptr );

		const auto gravity = Globals::g_pProcess->read< float >( gravityptr + 0xC );

		if( Globals::g_pMenu->get_value_of_setting< bool >( "Other", "Increased Speed" ) )
		{
			if( speed != 420 )
				Globals::g_pProcess->write< int32_t >( speedptr + 0xC, 420 );
		}
		else if( speed != 190 )
			Globals::g_pProcess->write< int32_t >( speedptr + 0xC, 190 );

		if( Globals::g_pMenu->get_value_of_setting< bool >( "Other", "Decreased Gravity" ) )
		{
			if( gravity != 420.f )
				Globals::g_pProcess->write< float >( gravityptr + 0xC, 420.f );
		}
		else if( gravity != 800.f )
			Globals::g_pProcess->write< float >( gravityptr + 0xC, 800.f );
	}
};
