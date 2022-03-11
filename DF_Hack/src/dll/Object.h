#pragma once
#ifndef OBJECT_H
#define OBJECT_H
#include <cstdint>
#include "reclass.h"

//0x00481669 start of entity loop
//0x004840D0 another loop, it goes over entlist and special, calls same funciton

//constants

//pointer to player object in entity list
extern OBJECT* Player;
extern OBJECT** EntityList;


//constants end

//functions

void EnumEnt(void(*callback)(OBJECT* obj));
void EnumSpecial(void(*callback)(OBJECT* obj));
void EnumSpecial2(void(*callback)(OBJECT* obj));
void EnumStatic(void(*callback)(static_data* obj));
void EnumWeapons(void(*callback)(weapon_hud_entry* obj));
//functions end
#endif