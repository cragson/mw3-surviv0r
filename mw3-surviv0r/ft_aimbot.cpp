#include "ft_aimbot.hpp"
#include "globals.hpp"
#include "utils.hpp"
#include "engine_math.hpp"

void ft_aimbot::tick() {}

void ft_aimbot::on_render()
{
	if( !Globals::g_pMenu->get_value_of_setting< bool >( "Aimbot", "active" ) )
		return;

	const auto fov = Globals::g_pMenu->get_value_of_setting< int32_t >( "Aimbot", "fov" );
	if( fov <= 0 )
		return;

	Globals::g_pOverlay->draw_rect(
		Globals::g_pOverlay->get_overlay_width() / 2 - ( fov / 2 ),
		Globals::g_pOverlay->get_overlay_height() / 2 - ( fov / 2 ),
		fov,
		fov,
		0,
		255,
		255
	);

	game_entity ent = {};

	Vector2 aim_bottom, aim_up = {};

	const auto width_mid = Globals::g_pOverlay->get_overlay_width() / 2;
	const auto height_mid = Globals::g_pOverlay->get_overlay_height() / 2;

	std::vector< std::uintptr_t > friends;

	for( auto i = 0; i < 2047; i++ )
	{
		const auto ptr = Offsets::entity_list + i * sizeof( centity );

		const auto ent = Globals::g_pProcess->read< centity >( ptr );

		if( ent.m_survival_team_ident1 && ent.m_survival_team_ident2 == 2 )
			friends.push_back( ent.m_clientnum );
	}

	if( utils::is_key_pressed( VK_LMENU ) )
	{
		for( auto i = 0; i < Interfaces::g_IEntity->get_entities_count(); i++ )
		{
			if( Interfaces::g_IEntity->get_entity_by_index( i, &ent ) )
			{
				if( ent.m_iType != 13 || ent.m_iHealth <= 0 )
					continue;

				if( std::ranges::find( friends.begin(), friends.end(), ent.m_iClientNum ) != friends.end() )
					continue;

				if( EngineMath::world_to_screen( ent.m_vecPosition, aim_bottom ) && EngineMath::world_to_screen(
					ent.m_vecPositionUp,
					aim_up
				) )
				{
					const auto aim_x = static_cast< int32_t >( aim_bottom.x + ( aim_up.x - aim_bottom.x ) );
					const auto aim_y = static_cast< int32_t >( aim_bottom.y + ( aim_up.y - aim_bottom.y ) );

					// check now if aim point is in fov
					const auto dx = aim_x - width_mid;
					const auto dy = aim_y - height_mid;
					const auto dst = sqrtf( dx * dx * 1.f + dy * dy * 1.f );

					Globals::g_pOverlay->draw_filled_rect(
						aim_x - 5,
						aim_y - 5,
						5,
						5,
						255,
						0,
						255
					);

					// enemy is in fov
					if( dst <= fov )
						SetCursorPos( aim_x, aim_y );
				}
			}
		}
	}
}
