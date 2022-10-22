#include "ft_watermark.hpp"

#include "game_structs.hpp"
#include "globals.hpp"

#include "offsets.hpp"


void ft_watermark::on_render()
{
	Globals::g_pOverlay->draw_rect( 10, 20, 173, 21, 255, 0, 0 );

	Globals::g_pOverlay->draw_string( "osmium: MW3 Surviv0r", 12, 22, 255, 255, 255 );

	if( Globals::g_pMenu->get_value_of_setting< bool >( "Visuals", "Crosshair" ) )
	{
		const auto mid_w = Globals::g_pOverlay->get_overlay_width() / 2;
		const auto mid_h = Globals::g_pOverlay->get_overlay_height() / 2;

		Globals::g_pOverlay->draw_line( mid_w, mid_h - 10, mid_w, mid_h + 10, 255, 0, 0 );
		Globals::g_pOverlay->draw_line( mid_w - 10, mid_h, mid_w + 10, mid_h, 255, 0, 0 );
	}
}
