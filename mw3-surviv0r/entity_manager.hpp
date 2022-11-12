#pragma once
#include <cstdint>
#include <memory>
#include <vector>

#include "game_structs.hpp"
#include "offsets.hpp"

constexpr auto ENTITY_COUNT = 1000;

class public_entity
{
public:
	public_entity()
		: m_centity( {} )
	  , m_game_entity( {} ) {}

	public_entity( const game_entity& ge, const centity& ce )
		: m_centity( ce )
	  , m_game_entity( ge ) {}

	centity m_centity;
	game_entity m_game_entity;
};

class entity_manager
{
public:
	entity_manager()
		: m_game_entities( {} )
	  , m_centities( {} )
	{
		this->m_centities.resize( sizeof( centity ) * ENTITY_COUNT );
	}

	[[nodiscard]] static constexpr std::uintptr_t get_entity_ptr_by_index( uint16_t idx )
	{
		return Offsets::muelltonne + idx * 0x270;
	}

	[[nodiscard]] static constexpr std::uintptr_t get_centity_ptr_by_index(uint16_t idx)
	{
		return Offsets::entity_list + idx * 0x194;
	}

	[[nodiscard]] bool get_entity_by_index( uint32_t idx, game_entity* entity_ptr ) const;

	[[nodiscard]] static int32_t get_entities_count();

	bool dump_entities();

	void apply_filter();

	std::vector< std::unique_ptr< public_entity > > m_entities;

private:
	std::vector< game_entity > m_game_entities;
	std::vector< centity > m_centities;
};
