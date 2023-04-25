#include "ft_aimbot.hpp"
#include "globals.hpp"
#include "utils.hpp"
#include "engine_math.hpp"

void ft_aimbot::tick()
{
	if( !Globals::g_pMenu->get_value_of_setting< bool >( "Aimbot", "Active" ) )
		return;

	const auto fov = Globals::g_pMenu->get_value_of_setting< int32_t >( "Aimbot", "FoV" );
	if( fov <= 0 )
		return;

	if( utils::is_key_pressed( VK_LMENU ) )
	{
		const auto width_mid  = Globals::g_pOverlay->get_overlay_width() / 2;
		const auto height_mid = Globals::g_pOverlay->get_overlay_height() / 2;

		for( const auto& pub : Interfaces::g_IEntity->m_entities )
		{
			if( pub->m_game_entity.m_iType != 13 || pub->m_game_entity.m_iHealth <= 0 )
				continue;

			if( pub->m_centity.m_survival_team_ident1 && pub->m_centity.m_survival_team_ident2 == 2 )
				continue;

			Vector2 aim_bottom, aim_up = {};

			if( EngineMath::world_to_screen( pub->m_game_entity.m_vecPosition, aim_bottom ) &&
				EngineMath::world_to_screen( pub->m_game_entity.m_vecPositionUp, aim_up ) )
			{
				const auto aim_x = static_cast< int32_t >( aim_up.x );
				const auto aim_y = static_cast< int32_t >( aim_up.y );

				// check now if aim point is in fov
				const auto dx  = aim_x - width_mid;
				const auto dy  = aim_y - height_mid;
				const auto dst = sqrtf( dx * dx * 1.f + dy * dy * 1.f );

				// enemy is in fov
				if( dst <= fov )
				{
					SetCursorPos( aim_x, aim_y );
				}
			}
		}
	}
}

void ft_aimbot::on_render()
{
	if( !Globals::g_pMenu->get_value_of_setting< bool >( "Aimbot", "Active" ) )
		return;

	const auto fov = Globals::g_pMenu->get_value_of_setting< int32_t >( "Aimbot", "FoV" );
	if( fov <= 0 )
		return;

	const auto width_mid  = Globals::g_pOverlay->get_overlay_width() / 2;
	const auto height_mid = Globals::g_pOverlay->get_overlay_height() / 2;

	Globals::g_pOverlay->draw_rect( Globals::g_pOverlay->get_overlay_width() / 2 - ( fov / 2 ),
	                                Globals::g_pOverlay->get_overlay_height() / 2 - ( fov / 2 ), fov, fov, 0, 255, 255
	);
}
