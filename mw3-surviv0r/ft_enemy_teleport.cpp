#include "ft_enemy_teleport.hpp"

#include "offsets.hpp"
#include "globals.hpp"

void ft_enemy_teleport::tick()
{
	if (!Globals::g_pMenu->get_value_of_setting< bool >("Other", "Teleport Enemies to Player"))
		return;

	auto player_coords = Globals::g_pProcess->read< Vector3 >(Offsets::refdef + 0x18);

	// add offset
	player_coords.x += 300.f;

	for (const auto& pub : Interfaces::g_IEntity->m_entities)
	{
		if (pub->m_game_entity.m_iType != 13 || pub->m_game_entity.m_iHealth <= 0)
			continue;

		const auto ptr = Interfaces::g_IEntity->get_entity_ptr_by_index(pub->m_game_entity.m_iClientNum & 0xFFF);

		Globals::g_pProcess->write< Vector3 >(ptr + 0xEC, player_coords);
	}
}
