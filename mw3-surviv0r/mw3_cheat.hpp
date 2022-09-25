#pragma once

#include "osmium/Cheat/cheat.hpp"

class mw3_cheat : public cheat
{
public:
	bool setup_features() override;

	bool setup_offsets() override;

	void print_features() override;

	void print_offsets() override;

	void run() override;

	void shutdown() override;
};
