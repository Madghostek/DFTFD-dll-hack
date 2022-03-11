#pragma warning (disable : 4514)
#include "Object.h"
#include "reclass.h"
#include <stdio.h>
#include <exception>

//static addresses
//0x00605FBC enable debug
//0x004D69F0 debug write func
OBJECT* Player = *(OBJECT**)(0x008DA1A0);
size_t* entityListLen_special = (size_t*)(0x01200DA4);
size_t* entityListLen_special2 = (size_t*)0x01191980;
OBJECT** EntityList = (OBJECT**)(0x01200DA8);
static_data** StaticEntData = (static_data**)(0x0103B620);
weapon_hud_entry* HudList = (weapon_hud_entry*)(0x00629BA4);
//at *Entitylist + 256 objects there is special entlist
//at *ENtitylist + 900 objects there is something
//0x01200DA4 special ent list len?

//00F17DA0 4 have some kind of counter that goes to around 0x75 or more?
//0x00F17DC0 whackton of pointers :D, A4 is used to index?

typedef void(*CALLBACK_GENERIC)(void*);
//walk through entitylist array and pass each to callback
//there is additional 3 dwords of info after each pointer, dont know whats that yet
//this function ends if first obj is null, game not started
//entitylist seems to be max 256 size (game even caps at 40 somewhere)
void EnumObjects(void* base, void(*callback)(void* obj),size_t objsize)
{
	void* obj = base;
	if (obj == nullptr) return;
	//int count = 0; //entity list length is at 0x011726E0, count<len <!
	while (*(int*)obj) //if obj(0x18) is not null, object is active? (game does that), or if obj[0] != 0 like now
	{
		callback(obj);
		obj = (void*)(((int)obj) + objsize); 
	}
}

void EnumEnt(void(*callback)(OBJECT* obj))
{
	EnumObjects(*EntityList, (CALLBACK_GENERIC)callback, 0x2E8);
}

void EnumSpecial(void(*callback)(OBJECT* obj))
{
	OBJECT* obj = *EntityList + 0x100; //in objects, 0x2E800 off
	if (obj == nullptr) return;
	//int count = 0; //entity list length is at 0x011726E0, count<len <!
	for (size_t i = 0; i < (*entityListLen_special); ++i) //if obj(0x18) is not null, object is active? (game does that), or if obj[0] != 0 like now
	{
		callback(obj);
		obj++;
	}
}

void EnumSpecial2(void(*callback)(OBJECT* obj))
{
	OBJECT* obj = *EntityList + 0x900; //in objects, 0x1A2800 off
	if (obj == nullptr) return;
	//int count = 0; //entity list length is at 0x011726E0, count<len <!
	for (size_t i = 0; i < (*entityListLen_special2); ++i) //if obj(0x18) is not null, object is active? (game does that), or if obj[0] != 0 like now
	{
		callback(obj);
		obj++;
	}
}

void EnumStatic(void(*callback)(static_data* obj))
{
	EnumObjects(*StaticEntData, (CALLBACK_GENERIC)callback, 0x21C);
}

void EnumWeapons(void(*callback)(weapon_hud_entry*))
{
	weapon_hud_entry* obj = HudList;
	if (obj == nullptr) return;
	while (obj->text[0] || obj->hud_index)
	{
		callback(obj);
		obj = (weapon_hud_entry*)(((int)obj) + 0x70);
	}
}