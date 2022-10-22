#include "ft_godmode.hpp"

#include "globals.hpp"

void ft_godmode::tick()
{
	if( !Globals::g_pMenu->get_value_of_setting< bool >( "Other", "Godmode" ) )
		return;

	const auto player_ptr = Interfaces::g_IEntity->get_entity_ptr_by_index( 0 );

	Globals::g_pProcess->write< int32_t >( player_ptr + 0x154, 1337 ); // 0x154 => m_iMaximumHealth (game_entity)
	Globals::g_pProcess->write< int32_t >( player_ptr + 0x150, 1337 ); // 0x150 => m_iHealth (game_entity)
}
