#include "ft_better_armor.hpp"

#include "globals.hpp"
#include "offsets.hpp"

void ft_better_armor::tick()
{
	if( Globals::g_pProcess->read< int32_t >(
		Globals::g_pProcess->get_image_base( L"iw5sp.exe" ) + Offsets::survial_armor
	) < 100 )
		Globals::g_pProcess->write< int32_t >(
			Globals::g_pProcess->get_image_base( L"iw5sp.exe" ) + Offsets::survial_armor,
			6077
		);
}
