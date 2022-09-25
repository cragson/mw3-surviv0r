#include "ft_super_jump.hpp"

#include "globals.hpp"
#include "offsets.hpp"
#include "utils.hpp"

void ft_super_jump::tick()
{
	if( utils::is_key_pressed( VK_SPACE ) && Globals::g_pProcess->read< float >(
		Globals::g_pProcess->get_image_base( L"iw5sp.exe" ) + Offsets::survival_super_jump
	) <= 12.f )
		Globals::g_pProcess->write< float >(
			Globals::g_pProcess->get_image_base( L"iw5sp.exe" ) + Offsets::survival_super_jump,
			840.f
		);
}
