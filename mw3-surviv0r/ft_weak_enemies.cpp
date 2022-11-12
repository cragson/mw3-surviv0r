#include "ft_weak_enemies.h"
#include "globals.hpp"

void ft_weak_enemies::tick()
{
	if( !Globals::g_pMenu->get_value_of_setting< bool >( "Other", "Weak Enemies" ) )
		return;

	for( const auto& pub : Interfaces::g_IEntity->m_entities )
	{
		if( pub->m_game_entity.m_iHealth > 1 )
		{
			const auto ptr = Interfaces::g_IEntity->get_entity_ptr_by_index( pub->m_game_entity.m_iClientNum & 0xFFF );

			Globals::g_pProcess->write< int32_t >( ptr + 0x150, 1 );
		}
	}
}
