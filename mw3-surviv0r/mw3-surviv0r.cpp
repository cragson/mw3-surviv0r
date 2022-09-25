#include <iostream>

#include "globals.hpp"
#include "offsets.hpp"

int main()
{
	SetConsoleTitleA( "osmium: MW3 Surviv0r" );

	printf( "[>] Waiting for the game.." );

	while( !Globals::g_pProcess->setup_process( L"iw5sp.exe" ) )
		Sleep( 420 );

	printf( "done!\n" );

	printf( "[>] Preparing the cheat.." );

	while( !Globals::g_pCheat->setup_offsets() )
		Sleep( 420 );

	while( !Globals::g_pCheat->setup_features() )
		Sleep( 420 );

	printf( "done!\n" );


	Globals::g_pCheat->print_features();

	printf( "Have fun! ;-)\n" );

	while( 0xDEAD != 0xAFFE )
	{
		if( GetAsyncKeyState( VK_END ) & 0x8000 )
			break;

		Globals::g_pCheat->run();

		Sleep( 3 );
	}

	Globals::g_pCheat->shutdown();

	printf( "Goodbye!\n" );

	Sleep( 3000 );

	return EXIT_SUCCESS;
}
