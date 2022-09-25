#include "ft_xp_lover.hpp"

#include "globals.hpp"
#include "offsets.hpp"
#include "utils.hpp"

void ft_xp_lover::tick()
{
	if( utils::is_key_pressed( VK_UP ) )
		Globals::g_pProcess->write< int32_t >(
			Globals::g_pProcess->get_image_base( L"iw5sp.exe" ) + Offsets::survival_xp,
			Globals::g_pProcess->read< int32_t >(
				Globals::g_pProcess->get_image_base( L"iw5sp.exe" ) + Offsets::survival_xp
			) + 10000
		);
}
