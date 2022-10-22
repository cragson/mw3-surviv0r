#include "ft_esp.hpp"
#include "globals.hpp"
#include "engine_math.hpp"
#include "menu.hpp"

void ft_esp::tick() {}

void ft_esp::on_render()
{
	const auto player_esp = Globals::g_pMenu->get_value_of_setting< bool >( "Visuals", "Player ESP" );
	const auto weapon_esp = Globals::g_pMenu->get_value_of_setting< bool >( "Visuals", "Weapon ESP" );

	if( !player_esp && !weapon_esp )
		return;

	if( Interfaces::g_IEntity->dump_entities() )
	{
		Interfaces::g_IEntity->apply_filter();

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

					// S1
					Globals::g_pOverlay->draw_line(
						bb.x - ( width / 2 ),
						bb.y,
						bb.x + ( width / 2 ),
						bb.y,
						is_friend ? 0 : 255,
						is_friend ? 255 : 0,
						0
					);

					// S2
					Globals::g_pOverlay->draw_line(
						bb.x + ( width / 2 ),
						bb.y,
						bb.x + ( width / 2 ),
						bb.y - height,
						is_friend ? 0 : 255,
						is_friend ? 255 : 0,
						0
					);

					// S3
					Globals::g_pOverlay->draw_line(
						aa.x - ( width / 2 ),
						aa.y,
						aa.x + ( width / 2 ),
						aa.y,
						is_friend ? 0 : 255,
						is_friend ? 255 : 0,
						0
					);

					// S4
					Globals::g_pOverlay->draw_line(
						bb.x - ( width / 2 ),
						bb.y,
						bb.x - ( width / 2 ),
						bb.y - height,
						is_friend ? 0 : 255,
						is_friend ? 255 : 0,
						0
					);

					auto rel_health = ( 1.f * pub->m_game_entity.m_iHealth ) / ( 1.f * pub->m_game_entity.
						m_iMaximumHealth );
					const auto delta_green = static_cast< int32_t >( rel_health * 255.f );
					const auto delta_red = 255 - delta_green;

					// fix for downed enemies/ last stand
					if( pub->m_game_entity.m_iHealth == 1 && pub->m_game_entity.m_iMaximumHealth == 1 )
						rel_health = .01f;

					constexpr auto health_bar_width = 10;

					Globals::g_pOverlay->draw_filled_rect(
						bb.x - ( width / 2 ) - health_bar_width - 3,
						aa.y,
						health_bar_width,
						bb.y - aa.y,
						0,
						0,
						0
					);

					Globals::g_pOverlay->draw_filled_rect(
						bb.x - ( width / 2 ) - health_bar_width - 3,
						aa.y,
						health_bar_width,
						static_cast< int32_t >( ( bb.y - aa.y ) * rel_health ),
						delta_red,
						delta_green,
						0
					);

					Globals::g_pOverlay->draw_line(
						Globals::g_pOverlay->get_overlay_width() / 2,
						0,
						bb.x,
						bb.y,
						delta_red,
						delta_green,
						0
					);

					const auto dst = EngineMath::entity_distance_to_player( pub->m_game_entity.m_vecPosition ) / 100.f;

					Globals::g_pOverlay->draw_string(
						std::format( "[{:.2f}m]", dst ),
						aa.x + ( width / 2 ) + 15,
						bb.y,
						is_friend ? 0 : 255,
						is_friend ? 255 : 0,
						0
					);
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
}
