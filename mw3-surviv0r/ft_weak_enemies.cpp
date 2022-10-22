#include "ft_weak_enemies.h"
#include "offsets.hpp"
#include "globals.hpp"

void ft_weak_enemies::tick()
{
	if( !Globals::g_pMenu->get_value_of_setting< bool >( "Other", "Weak Enemies" ) )
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

	for( auto i = 1; i < MAX_ENT_COUNT; i++ )
	{
		if( Interfaces::g_IEntity->get_entity_by_index( i, &ent ) )
		{
			if( ent.m_iHealth <= 0 )
				continue;

			const auto ptr = Interfaces::g_IEntity->get_entity_ptr_by_index( i );

			if( std::ranges::find( friends.begin(), friends.end(), ent.m_iClientNum ) != friends.end() )
			{
				Globals::g_pProcess->write< int32_t >( ptr + 0x150, ent.m_iMaximumHealth );

				continue;
			}

			if( ent.m_iHealth > 1 )
				Globals::g_pProcess->write< int32_t >( ptr + 0x150, 1 );
		}
	}
}
