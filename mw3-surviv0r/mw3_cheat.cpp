#include "mw3_cheat.hpp"

#include "ft_aimbot.hpp"
#include "ft_enemy_teleport.hpp"
#include "ft_esp.hpp"
#include "ft_fovchanger.hpp"
#include "ft_funmode.hpp"
#include "ft_godmode.hpp"
#include "ft_infinite_ammo.hpp"
#include "ft_super_jump.hpp"
#include "ft_watermark.hpp"
#include "ft_weak_enemies.h"
#include "globals.hpp"
#include "utils.hpp"
#include "offsets.hpp"

bool mw3_cheat::setup_features()
{
	auto mark = std::make_unique< ft_watermark >();
	mark->set_name( L"Watermark" );
	mark->set_status( true );
	mark->enable_drawing();

	auto infammo = std::make_unique< ft_infinite_ammo >();
	infammo->set_name( L"Infinite Ammo" );
	infammo->disable_drawing();
	infammo->set_status( true );

	auto jump = std::make_unique< ft_super_jump >();
	jump->set_name( L"Super Jump" );
	jump->disable_drawing();
	jump->set_status( true );

	auto esp = std::make_unique< ft_esp >();
	esp->set_name( L"ESP" );
	esp->enable_drawing();
	esp->set_status( true );

	auto tele = std::make_unique< ft_enemy_teleport >();
	tele->set_name( L"Enemy Teleport" );
	tele->disable_drawing();
	tele->set_status( true );

	auto god = std::make_unique< ft_godmode >();
	god->set_name( L"Godmode" );
	god->disable_drawing();
	god->set_status( true );

	auto weak = std::make_unique< ft_weak_enemies >();
	weak->set_name( L"Weak Enemies" );
	weak->disable_drawing();
	weak->set_status( true );

	auto aim = std::make_unique< ft_aimbot >();
	aim->set_name( L"Aimbot" );
	aim->enable_drawing();
	aim->set_status( true );

	auto fov = std::make_unique< ft_fovchanger >();
	fov->set_name( L"Fov Changer" );
	fov->disable_drawing();
	fov->set_status( true );

	auto fun = std::make_unique< ft_funmode >();
	fun->set_name( L"Fun Mode" );
	fun->disable_drawing();
	fun->set_status( true );

	this->m_features.push_back( std::move( mark ) );
	this->m_features.push_back( std::move( infammo ) );
	this->m_features.push_back( std::move( jump ) );
	this->m_features.push_back( std::move( esp ) );
	this->m_features.push_back( std::move( tele ) );
	this->m_features.push_back( std::move( god ) );
	this->m_features.push_back( std::move( weak ) );
	this->m_features.push_back( std::move( aim ) );
	this->m_features.push_back( std::move( fov ) );
	this->m_features.push_back( std::move( fun ) );

	Globals::g_pMenu->set_virtual_key_code( VK_INSERT );
	Globals::g_pMenu->enable_drawing();

	return true;
}

bool mw3_cheat::setup_offsets()
{
	const auto game = Globals::g_pProcess->get_image_ptr_by_name( L"iw5sp.exe" );

	if( !game )
		return false;

	const auto rdef = game->find_pattern( L"BA ? ? ? ? C6 85", false );

	if( !rdef )
		return false;

	Offsets::refdef = game->deref_address< std::uintptr_t >( rdef + 1 );

	const auto state = game->find_pattern( L"8B 35 ? ? ? ? 83 FE 06", false );

	if( !state )
		return false;

	Offsets::connection_state = game->deref_address< std::uintptr_t >( state + 2 );

	const auto tonne = game->find_pattern( L" BF ? ? ? ? 7E 2A", false );

	if( !tonne )
		return false;

	Offsets::muelltonne = game->deref_address< std::uintptr_t >( tonne + 1 );

	const auto tonne_max = game->find_pattern( L"8B 0D ? ? ? ? 55 56", false );

	if( !tonne_max )
		return false;

	Offsets::muelltonne_max = game->deref_address< std::uintptr_t >( tonne_max + 2 );

	const auto fov = game->find_pattern( L"8B 0D ? ? ? ? A3 ? ? ? ? A1 ? ? ? ? C7 05", false );

	if( !fov )
		return false;

	Offsets::cgfov_ptr = game->deref_address< std::uintptr_t >( fov + 2 );

	const auto speed = game->find_pattern( L"8B 15 ? ? ? ? 8B 42 0C 8B 8B", false );

	if( !speed )
		return false;

	Offsets::speed_ptr = game->deref_address< std::uintptr_t >( speed + 2 );

	const auto gravity = game->find_pattern( L"A1 ? ? ? ? D9 40 0C 8D BE", false );

	if( !gravity )
		return false;

	Offsets::gravity_ptr = game->deref_address< std::uintptr_t >( gravity + 1 );

	const auto ents = game->find_pattern( L"BE ? ? ? ? EB 03 8D 49 00 85 F6", false );

	if( !ents )
		return false;

	Offsets::entity_list = game->deref_address< std::uintptr_t >( ents + 1 );

	const auto ui = game->find_pattern( L"A1 ? ? ? ? 81 EC ? ? ? ? 80 78 0C 00 74 29", false );

	if( !ui )
		return false;

	Offsets::DrawUIShowList = ui;

	const auto skinned = game->find_pattern( L"81 EC ? ? ? ? E8 ? ? ? ? D9 1C 24", false );

	if( !skinned )
		return false;

	Offsets::fn_R_DrawXModelSkinnedCached = skinned;

	// TODO: implement Cbuf_AddText

	return true;
}

void mw3_cheat::print_features()
{
	printf( "\n" );

	printf( "Feature-Name -> Feature-Hotkey\n" );

	for( const auto& feature : this->m_features )
		printf(
			"[>] %-25ws -> %s\n",
			feature->get_name().c_str(),
			utils::virtual_key_as_string( feature->get_virtual_key_code() ).c_str()
		);

	printf( "\n" );
}

void mw3_cheat::print_offsets()
{
	printf( "\n" );

	const auto msg = []( const std::string& name, const std::uintptr_t value )
	{
		printf( "[>] %-35s -> 0x%08X\n", name.c_str(), value );
	};

	msg( "Refdef", Offsets::refdef );
	msg( "Connection State", Offsets::connection_state );
	msg( "Muelltonne", Offsets::muelltonne );
	msg( "Muelltonne Max", Offsets::muelltonne_max );
	msg( "cg_fov", Offsets::cgfov_ptr );
	msg( "g_speed", Offsets::speed_ptr );
	msg( "g_gravity", Offsets::gravity_ptr );
	msg( "entitylist", Offsets::entity_list );
	msg( "DrawUIShowList", Offsets::DrawUIShowList );
	msg( "R_DrawXModelSkinnedCached", Offsets::fn_R_DrawXModelSkinnedCached );

	printf( "\n" );
}

void mw3_cheat::run()
{
	for( const auto& feature : this->m_features )
	{
		// before tick'ing the feature, check first if the state will eventually change
		if( GetAsyncKeyState( feature->get_virtual_key_code() ) & 0x8000 )
			feature->toggle();

		// let the feature tick() when active
		if( feature->is_active() )
			feature->tick();
	}
}

void mw3_cheat::shutdown()
{
	// disable every feature here
	for( const auto& feature : this->m_features )
		if( feature->is_active() )
			feature->disable();

	// clear image map here
	if( Globals::g_pProcess )
		Globals::g_pProcess->clear_image_map();
}
