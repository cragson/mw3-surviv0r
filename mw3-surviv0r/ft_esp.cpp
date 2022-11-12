#include "ft_esp.hpp"
#include "globals.hpp"
#include "engine_math.hpp"
#include "menu.hpp"

#include <chrono>

void ft_esp::tick() {}

void ft_esp::on_render()
{
	const auto player_esp = Globals::g_pMenu->get_value_of_setting< bool >( "Visuals", "Player ESP" );
	const auto weapon_esp = Globals::g_pMenu->get_value_of_setting< bool >( "Visuals", "Weapon ESP" );

	Interfaces::g_IEntity->dump_entities();
	Interfaces::g_IEntity->apply_filter();

	if( !player_esp && !weapon_esp )
		return;

	for( const auto& pub : Interfaces::g_IEntity->m_entities )
	{
		if( pub->m_game_entity.m_iHealth <= 0 && pub->m_game_entity.m_iType == 13 )
			continue;

		if( Vector2 aa, bb; EngineMath::world_to_screen( pub->m_game_entity.m_vecPosition, aa ) &&
			EngineMath::world_to_screen( pub->m_game_entity.m_vecPositionUp, bb ) )
		{
			if( pub->m_game_entity.m_iType == 13 )
			{
				if( !player_esp )
					return;

				const auto is_friend = pub->m_centity.m_survival_team_ident1 && pub->m_centity.
						m_survival_team_ident2 == 2;

				const auto height = bb.y - aa.y;
				const auto width = height / 2 > 45 ? 45 : height / 2;

				const auto box_width = Globals::g_pMenu->get_value_of_setting< int32_t >("Visuals", "Box Width");

				Globals::g_pOverlay->draw_rect(
					aa.x - width / 2,
					aa.y,
					width,
					height,
					is_friend ? 0 : 255,
					is_friend ? 255 : 0,
					0,
					box_width
				);

				auto rel_health = ( 1.f * pub->m_game_entity.m_iHealth ) / ( 1.f * pub->m_game_entity.
					m_iMaximumHealth );
				const auto delta_green = static_cast< int32_t >( rel_health * 255.f );
				const auto delta_red = 255 - delta_green;

				// fix for downed enemies/ last stand
				if( pub->m_game_entity.m_iHealth == 1 && pub->m_game_entity.m_iMaximumHealth == 1 )
					rel_health = .01f;

				if( Globals::g_pMenu->get_value_of_setting< bool >( "Visuals", "Healthbar" ) )
				{
					constexpr auto health_bar_width = 10;

					Globals::g_pOverlay->draw_filled_rect(
						bb.x - ( width / 2 ) - health_bar_width - 3 + 15,
						aa.y,
						health_bar_width,
						bb.y - aa.y,
						0,
						0,
						0
					);

					Globals::g_pOverlay->draw_filled_rect(
						bb.x - ( width / 2 ) - health_bar_width - 3 + 15,
						aa.y,
						health_bar_width,
						static_cast< int32_t >( ( bb.y - aa.y ) * rel_health ),
						delta_red,
						delta_green,
						0
					);
				}
				if( Globals::g_pMenu->get_value_of_setting< bool >( "Visuals", "Snapline" ) )
					Globals::g_pOverlay->draw_line(
						Globals::g_pOverlay->get_overlay_width() / 2,
						0,
						bb.x,
						bb.y,
						is_friend ? 255 : delta_red,
						is_friend ? 0 :delta_green,
						is_friend ? 255 : 0,
						Globals::g_pMenu->get_value_of_setting< int32_t >( "Visuals", "Line Width")
					);

				if( Globals::g_pMenu->get_value_of_setting< bool >( "Visuals", "Distance" ) )
				{
					const auto dst = EngineMath::entity_distance_to_player( pub->m_game_entity.m_vecPosition ) / 50.f;

					Globals::g_pOverlay->draw_string(
						std::vformat( "[{:.2f}m]", std::make_format_args(dst) ),
						aa.x + ( width / 2 ) + 15,
						aa.y + 5,
						is_friend ? 0 : 255,
						is_friend ? 255 : 0,
						0
					);
				}
			}
			else if( weapon_esp && pub->m_game_entity.m_iType == 2 )
			{
				Globals::g_pOverlay->draw_line(
					Globals::g_pOverlay->get_overlay_width() / 2,
					Globals::g_pOverlay->get_overlay_height(),
					bb.x,
					bb.y,
					255,
					255,
					0
				);

				Globals::g_pOverlay->draw_filled_rect(
					bb.x - 5,
					bb.y - 5,
					10,
					10,
					255,
					255,
					0
				);
			}
		}
	}
}
