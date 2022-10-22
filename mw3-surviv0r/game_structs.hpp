#pragma once
#include <cstdint>

class Vector2
{
public:
	float x, y;
};

class Vector3
{
public:
	float x, y, z;
};

class Matrix3x3
{
public:
	Vector3 a, b, c;
};

class centity
{
public:
	char pad_0000[2]; //0x0000
	int16_t m_valid1; //0x0002
	char pad_0004[12]; //0x0004
	Vector3 m_pos1; //0x0010
	char pad_001C[68]; //0x001C
	int32_t m_eFlags1; //0x0060
	int32_t m_eType1; //0x0064
	char pad_0068[32]; //0x0068
	int32_t m_eType2; //0x0088
	char pad_008C[8]; //0x008C
	Vector2 m_angles; //0x0094
	char pad_009C[60]; //0x009C
	int32_t m_eFlags2; //0x00D8
	int32_t m_eType3; //0x00DC
	char pad_00E0[92]; //0x00E0
	int8_t m_survival_team_ident1; //0x013C
	int8_t m_survival_team_ident2; //0x013D
	char pad_013E[10]; //0x013E
	int32_t m_weapon; //0x0148
	char pad_014C[4]; //0x014C
	int32_t m_clientnum; //0x0150
	char pad_0154[40]; //0x0154
	int32_t m_valid2; //0x017C
	char pad_0180[20]; //0x0180
}; //Size: 0x0194


class game_entity
{
public:
	int8_t m_iType; //0x0000
	char pad_0001[11]; //0x0001
	uint8_t m_iState; //0x000C
	char pad_000D[15]; //0x000D
	Vector3 m_vecPosition; //0x001C
	char pad_0028[72]; //0x0028
	bool m_bFriendly; //0x0070
	char pad_0071[19]; //0x0071
	int32_t m_iClientNum; //0x0084
	char pad_0088[76]; //0x0088
	Vector3 m_vecPositionUp; //0x00D4
	char pad_00E0[12]; //0x00E0
	Vector3 m_vecWritablePosition; //0x00EC
	char pad_00F8[88]; //0x00F8
	int32_t m_iHealth; //0x0150
	int32_t m_iMaximumHealth; //0x0154
	char pad_0158[280]; //0x0158
}; //Size: 0x0270



class RefDef // @ 0x98F948
{
public:
	int32_t m_iX; //0x0000
	int32_t m_iY; //0x0004
	int32_t m_iWidth; //0x0008
	int32_t m_iHeight; //0x000C
	Vector2 m_vecFov; //0x0010
	Vector3 m_vecPosition1; //0x0018
	Matrix3x3 m_mViewMatrix; //0x0024
	char pad_0048[4]; //0x0048
	Vector3 m_vecPosition2; //0x004C
	char pad_0058[964]; //0x0058
}; //Size: 0x041C