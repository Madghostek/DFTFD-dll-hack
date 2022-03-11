// Created with ReClass.NET 1.2 by KN4CK3R
#pragma once
#include <stdint.h>

class Int3
{
public:
	uint32_t X; //0x0000
	uint32_t Y; //0x0004
	uint32_t Z; //0x0008
}; //Size: 0x000C

class OBJECT
{
public:
	uint32_t index; //0x0000
	class static_data* obj_static; //0x0004
	char pad_0008[4]; //0x0008
	class Info* Info; //0x000C
	void* model_ptr; //0x0010
	char pad_0014[4]; //0x0014
	class pointer_x18* Info3; //0x0018
	char pad_001C[8]; //0x001C
	class Int3 pos; //0x0024
	int32_t referenced_later_weird; //0x0030
	char pad_0034[2]; //0x0034
	uint16_t N0000006E; //0x0036
	uint32_t N000001E4; //0x0038
	class Int3 pos_mirror; //0x003C
	char pad_0048[12]; //0x0048
	class Int3 vel; //0x0054
	char pad_0060[16]; //0x0060
	char plrname[16]; //0x0070
	char pad_0080[4]; //0x0080
	uint32_t bitfield; //0x0084
	char pad_0088[20]; //0x0088
	uint32_t used; //0x009C
	char pad_00A0[4]; //0x00A0
	int32_t used_and_shifted; //0x00A4
	uint32_t inited_to_4096; //0x00A8
	char pad_00AC[64]; //0x00AC
	class static_data* copiedfrom0C_7C_Weapon; //0x00EC
	char pad_00F0[4]; //0x00F0
	uint32_t weapon_hudindex; //0x00F4
	char pad_00F8[12]; //0x00F8
	void* Weapon; //0x0104
	char pad_0108[60]; //0x0108
	class OBJECT* Parent; //0x0144
	uint32_t timer; //0x0148
	void* cleared_if_20000_bitfld_set; //0x014C
	class OBJECT** pointer_to_object_in_list; //0x0150
	uint32_t something_about_pointer_150; //0x0154
	void* sub1; //0x0158
	void* sub2_timer0; //0x015C
	char pad_0160[392]; //0x0160
}; //Size: 0x02E8

class static_data
{
public:
	char obj_name[32]; //0x0000
	uint32_t ID; //0x0020
	uint32_t probably_bits; //0x0024
	uint32_t type; //0x0028
	char pad_002C[224]; //0x002C
	void* ptr_copied_to_0x10; //0x010C
	char pad_0110[48]; //0x0110
	uint32_t this_fucker_so_far; //0x0140
	char pad_0144[24]; //0x0144
}; //Size: 0x015C

class pointer_x18
{
public:
	class unk* N00000227; //0x0000
	uint32_t val; //0x0004
	class subclass* unkptr; //0x0008
	uint32_t value_cmp; //0x000C
	char pad_0010[52]; //0x0010
}; //Size: 0x0044

class subclass
{
public:
	char pad_0000[76]; //0x0000
}; //Size: 0x004C

class Info
{
public:
	class OBJECT* owner; //0x0000
	char pad_0004[120]; //0x0004
	uint32_t linkedwith; //0x007C
	char pad_0080[64]; //0x0080
	uint32_t value; //0x00C0
	char pad_00C4[124]; //0x00C4
	uint32_t iszero; //0x0140
	char pad_0144[128]; //0x0144
}; //Size: 0x01C4

class unk
{
public:
	char pad_0000[48]; //0x0000
	uint32_t N00000A1D; //0x0030
	char pad_0034[80]; //0x0034
}; //Size: 0x0084

class weapon_hud_entry
{
public:
	char text[32]; //0x0000
	uint32_t zero[8]; //0x0020
	char text2[32]; //0x0040
	uint32_t idx_subtype1; //0x0060
	uint32_t idx_subtype2; //0x0064
	uint32_t idx_subtype3; //0x0068
	uint32_t hud_index; //0x006C
}; //Size: 0x0070