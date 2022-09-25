#pragma once

#include <cstddef>


namespace Offsets
{
	inline std::ptrdiff_t primary_ammo_clip = 0xF82118;

	inline std::ptrdiff_t secondary_ammo_clip = 0xF8213C;

	inline std::ptrdiff_t survival_money =
			0x164C8D0; // wHy OfFsEt ChAnGe AfTeR rOuNd pls not du verdammter tiefkuehlschubladenschubser

	inline std::ptrdiff_t survial_armor =
			0x171FBA0;// wHy OfFsEt ChAnGe AfTeR rOuNd pls not du verdammter tiefkuehlschubladenschubser

	inline std::ptrdiff_t survival_xp =
			0x17303C0; // wHy OfFsEt ChAnGe AfTeR rOuNd pls not du verdammter tiefkuehlschubladenschubser

	inline std::ptrdiff_t survival_y_coord = 0xF81D6C;

	inline std::ptrdiff_t primary_m320_clip = 0xF82148;

	inline std::ptrdiff_t secondary_m320_clip = 0xF82154;

	inline std::ptrdiff_t primary_grenade_ammo = 0xF82124;

	inline std::ptrdiff_t secondary_grenade_ammo = 0xF82130;

	inline std::ptrdiff_t primary_ammo_mag = 0xF820A0;

	inline std::ptrdiff_t secondary_ammo_mag = 0xF820B8;

	inline std::ptrdiff_t survival_x_coord = 0xF81D64;

	inline std::ptrdiff_t survival_z_coord = 0xF81D68;

	inline std::ptrdiff_t survival_super_jump = 0xF81D78;
}
