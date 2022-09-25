#include "ft_airstuck.hpp"

#include "globals.hpp"
#include "offsets.hpp"

void ft_airstuck::tick()
{
	Globals::g_pProcess->write< float >(
		Globals::g_pProcess->get_image_base( L"iw5sp.exe" ) + Offsets::survival_y_coord,
		1000.f
	);
}
