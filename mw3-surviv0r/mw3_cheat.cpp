#include "mw3_cheat.hpp"

#include "ft_airstuck.hpp"
#include "ft_better_armor.hpp"
#include "ft_infinite_ammo.hpp"
#include "ft_more_money.hpp"
#include "ft_super_jump.hpp"
#include "ft_watermark.hpp"
#include "ft_xp_lover.hpp"
#include "globals.hpp"
#include "utils.hpp"


bool mw3_cheat::setup_features()
{
	auto mark = std::make_unique< ft_watermark >();
	mark->set_name( L"Watermark" );
	mark->set_print_status( false );
	mark->set_activation_delay( 1000 );
	mark->set_virtual_key_code( VK_RSHIFT );
	mark->enable_drawing();

	auto stuck = std::make_unique< ft_airstuck >();
	stuck->set_name( L"Airstuck" );
	stuck->set_print_status( true );
	stuck->set_activation_delay( 420 );
	stuck->set_virtual_key_code( VK_NUMPAD0 );
	stuck->disable_drawing();

	auto infammo = std::make_unique< ft_infinite_ammo >();
	infammo->set_name( L"Infinite Ammo" );
	infammo->set_print_status( true );
	infammo->set_activation_delay( 420 );
	infammo->set_virtual_key_code( VK_NUMPAD1 );
	infammo->disable_drawing();

	auto barmor = std::make_unique< ft_better_armor >();
	barmor->set_name( L"Better Armor" );
	barmor->set_print_status( true );
	barmor->set_activation_delay( 420 );
	barmor->set_virtual_key_code( VK_NUMPAD2 );
	barmor->disable_drawing();

	auto xp = std::make_unique< ft_xp_lover >();
	xp->set_name( L"XP Lover (Arrow-UP increases XP by 10000)" );
	xp->set_print_status( true );
	xp->set_activation_delay( 420 );
	xp->set_virtual_key_code( VK_NUMPAD3 );
	xp->disable_drawing();

	auto jump = std::make_unique< ft_super_jump >();
	jump->set_name( L"Super Jump" );
	jump->set_print_status( true );
	jump->set_activation_delay( 420 );
	jump->set_virtual_key_code( VK_NUMPAD2 );
	jump->disable_drawing();

	auto money = std::make_unique< ft_more_money >();
	money->set_name( L"Money Money Money" );
	money->set_print_status( false );
	money->set_activation_delay( 420 );
	money->set_virtual_key_code( VK_NUMPAD5 );
	money->disable_drawing();

	//this->m_features.push_back(std::move(mark));
	this->m_features.push_back( std::move( stuck ) );
	this->m_features.push_back( std::move( infammo ) );
	//this->m_features.push_back(std::move(barmor));
	//this->m_features.push_back(std::move(xp));
	this->m_features.push_back( std::move( jump ) );
	//this->m_features.push_back(std::move(money));

	return true;
}

bool mw3_cheat::setup_offsets()
{
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
