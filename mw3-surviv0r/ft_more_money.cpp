#include "ft_more_money.hpp"

#include "globals.hpp"
#include "offsets.hpp"

void ft_more_money::on_enable()
{
	Globals::g_pProcess->write< int32_t >(
		Globals::g_pProcess->get_image_base( L"iw5sp.exe" ) + Offsets::survival_money,
		60777
	);

	printf( "[#] Got you some money bro\n" );

	this->disable();
}
