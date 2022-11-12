#include "entity_manager.hpp"

#include "offsets.hpp"

#include "globals.hpp"

bool entity_manager::get_entity_by_index( const uint32_t idx, game_entity* entity_ptr ) const
{
	if( idx < 0 || !entity_ptr )
		return false;

	const auto ptr = this->get_entity_ptr_by_index( idx );

	const auto entity = Globals::g_pProcess->read< game_entity >( ptr );

	*entity_ptr = entity;

	return true;
}

int32_t entity_manager::get_entities_count()
{
	return Globals::g_pProcess->read< int32_t >( Offsets::muelltonne_max );
}

bool entity_manager::dump_entities()
{
	// clear old entities
	if( !this->m_entities.empty() )
		this->m_entities.clear();


	const auto obj_count = this->get_entities_count();
	this->m_game_entities.resize( sizeof( game_entity ) * obj_count );


	if( !ReadProcessMemory(
		Globals::g_pProcess->get_process_handle(),
		reinterpret_cast< LPCVOID >( Offsets::muelltonne ),
		this->m_game_entities.data(),
		sizeof( game_entity ) * obj_count,
		nullptr
	) )
		return false;

	if( !ReadProcessMemory(
		Globals::g_pProcess->get_process_handle(),
		reinterpret_cast< LPCVOID >( Offsets::entity_list ),
		this->m_centities.data(),
		sizeof( centity ) * ENTITY_COUNT,
		nullptr
	) )
		return false;

	return true;
}

void entity_manager::apply_filter()
{
	this->m_entities.clear();
	for( const auto& obj : this->m_game_entities )
	{
		// only humans and weapons
		if( obj.m_iType != 13 && obj.m_iType != 2 )
			continue;

		/* TODO: Remove later
		for( const auto & ent : this->m_centities )
			if( ent.m_clientnum == obj.m_iClientNum )
				this->m_entities.push_back(std::make_unique< public_entity >(obj, ent));
		*/

		const auto is_same_ent = [&obj](const centity& ce)
		{
			return obj.m_iClientNum == ce.m_clientnum;
		};

		
		if( const auto obj_ce = std::ranges::find_if(
				this->m_centities.begin(),
				this->m_centities.end(),
				is_same_ent
			); obj_ce !=
			this->m_centities.end() )
			this->m_entities.push_back( std::make_unique< public_entity >( obj, *obj_ce ) );
		
	}
}
