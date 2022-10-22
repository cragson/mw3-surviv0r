#include "ft_infinite_ammo.hpp"

#include "globals.hpp"
#include "offsets.hpp"

void ft_infinite_ammo::tick()
{
	if( !Globals::g_pMenu->get_value_of_setting< bool >( "Other", "Infinite Ammo" ) )
		return;

	constexpr auto iloveasm = []( const std::uintptr_t address )
	{
		if( Globals::g_pProcess->read< int32_t >( address ) < 3 )
			Globals::g_pProcess->write< int32_t >( address, 137 );
	};

	iloveasm( Globals::g_pProcess->get_image_base( L"iw5sp.exe" ) + Offsets::primary_ammo_clip );
	iloveasm( Globals::g_pProcess->get_image_base( L"iw5sp.exe" ) + Offsets::secondary_ammo_clip );
	iloveasm( Globals::g_pProcess->get_image_base( L"iw5sp.exe" ) + Offsets::primary_ammo_mag );
	iloveasm( Globals::g_pProcess->get_image_base( L"iw5sp.exe" ) + Offsets::secondary_ammo_mag );
	iloveasm( Globals::g_pProcess->get_image_base( L"iw5sp.exe" ) + Offsets::primary_m320_clip );
	iloveasm( Globals::g_pProcess->get_image_base( L"iw5sp.exe" ) + Offsets::secondary_m320_clip );
	iloveasm( Globals::g_pProcess->get_image_base( L"iw5sp.exe" ) + Offsets::primary_grenade_ammo );
	iloveasm( Globals::g_pProcess->get_image_base( L"iw5sp.exe" ) + Offsets::secondary_grenade_ammo );
	iloveasm( Globals::g_pProcess->get_image_base( L"iw5sp.exe" ) + Offsets::c4_ammo );
}
