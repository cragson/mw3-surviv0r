#pragma once

#include <memory>

#include "osmium/Memory/Process/process.hpp"

#include "mw3_cheat.hpp"
#include "mw3_overlay.hpp"


namespace Globals
{
	inline std::unique_ptr< process > g_pProcess = std::make_unique< process >();

	inline std::unique_ptr< mw3_cheat > g_pCheat = std::make_unique< mw3_cheat >();

	inline std::unique_ptr< mw3_overlay > g_pOverlay = std::make_unique< mw3_overlay >();
}
