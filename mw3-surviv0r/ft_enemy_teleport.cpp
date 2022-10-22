#include "ft_enemy_teleport.hpp"

#include "offsets.hpp"
#include "globals.hpp"

void ft_enemy_teleport::tick()
{
	if( !Globals::g_pMenu->get_value_of_setting< bool >( "Other", "Teleport Enemies to Player" ) )
		return;

	std::vector< std::uintptr_t > friends;

	for( auto i = 0; i < 2047; i++ )
	{
		const auto ptr = Offsets::entity_list + i * sizeof( centity );

		const auto ent = Globals::g_pProcess->read< centity >( ptr );

		if( ent.m_survival_team_ident1 && ent.m_survival_team_ident2 == 2 )
			friends.push_back( ent.m_clientnum );
	}

	const auto MAX_ENT_COUNT = Interfaces::g_IEntity->get_entities_count();

	game_entity ent = {};

	auto player_coords = Globals::g_pProcess->read< Vector3 >( Offsets::refdef + 0x18 );

	// add offset
	player_coords.x += 300.f;

	for( auto i = 1; i < MAX_ENT_COUNT; i++ )
	{
		if( Interfaces::g_IEntity->get_entity_by_index( i, &ent ) )
		{
			if( ent.m_iHealth <= 0 )
				continue;

			if( std::ranges::find( friends.begin(), friends.end(), ent.m_iClientNum ) != friends.end() )
				continue;

			const auto ptr = Interfaces::g_IEntity->get_entity_ptr_by_index( i );

			if( ent.m_iType == 13 )
				Globals::g_pProcess->write<
					Vector3 >( ptr + 0xEC, player_coords ); // 0xEC => m_vecWritablePosition (game_entity)
		}
	}
}
