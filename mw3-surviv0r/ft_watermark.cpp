#include "ft_watermark.hpp"

#include "globals.hpp"

void ft_watermark::on_render()
{
	Globals::g_pOverlay->draw_rect( 10, 20, 165, 21, 255, 0, 0 );

	Globals::g_pOverlay->draw_string( "osmium: MW3 Surviv0r", 10, 22, 255, 255, 255 );
}
