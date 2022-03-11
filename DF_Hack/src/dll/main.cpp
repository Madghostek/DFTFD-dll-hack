#pragma warning (disable : 4514)
#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00
#include <Windows.h>
#include <stdio.h>

#include "Object.h"

void EnumCallback(OBJECT* obj)
{
    printf("obj: %p %s\n",obj, obj->obj_static->obj_name);
    if (obj->sub1 != (void*)0x00403AE4)
        printf("!!!NOT NOP!!!\n");
}
int counter = 0;
void EnumCallback_static_data(static_data* obj)
{
    printf("%d. (%p): ID: %d, type: %d, %d %s\n", counter, obj, obj->ID, obj->type, obj->probably_bits, obj->obj_name);
    counter += 1;
}
void EnumCallback_weapons(weapon_hud_entry* obj)
{
    printf("%d. %s %d %d %d\n", counter, obj->text,obj->idx_subtype1, obj->idx_subtype2, obj->idx_subtype3);
    for (int i = 0; i < 8; ++i)
    {
        if (obj->zero[i])
            printf("!!!NONZERO!!!\n");
    }
    counter += 1;
}


bool GetConsole()
{
    FreeConsole();
    if (!AllocConsole())
    {
        
        return false;
    }
    FILE* old;
    if (!freopen_s(&old,"CONOUT$", "wb", stdout) &&
        !freopen_s(&old,"CONOUT$", "wb", stderr) &&
        !freopen_s(&old,"CONIN$", "rb", stdin))
    {
        SetConsoleTitle("DF Hack");
        return true;
    }
    return false;
}

void (*DF_printf)(int,const char*,int) =(void(*)(int,const char*,int))0x0050AA73;

#define KEY(a) (GetAsyncKeyState(a) & 0x8000)

DWORD WINAPI HackThread(PVOID param)
{
    if (!GetConsole())
        goto end;
    printf("\
  ____  _____   _                _    \n\
 |  _ \\|  ___| | |__   __ _  ___| | __\n\
 | | | | |_    | '_ \\ / _` |/ __| |/ /\n\
 | |_| |  _|   | | | | (_| | (__|   < \n\
 |____/|_|     |_| |_|\\__,_|\\___|_|\\_\\\n\n");
    printf("DLL loaded\n");
    //main code

    if (Player == nullptr)
    {
        printf("Player not found!\n");
        goto end;
    }
    printf("%s\n", Player->obj_static->obj_name);
    printf("%s\n", Player->plrname);
    //EnumObjects(EnumCallback);
    while (!KEY(VK_ESCAPE) && Player!=nullptr)
    {
        if (KEY(VK_SHIFT) && KEY(VK_F1))
        {
            EnumEnt(EnumCallback);
            printf("EntityList printed\n");
            Sleep(1000);
        }
        if (KEY(VK_SHIFT) && KEY(VK_F2))
        {
            EnumSpecial(EnumCallback);
            printf("Special list printed\n");
            Sleep(1000);
        }
        else if (KEY(VK_SHIFT) && KEY(VK_F3))
        {
            //Player->bitfield |= 0x20; //parachute
            //printf("parachute\n");
            //Sleep(1000);
            EnumSpecial2(EnumCallback);
            printf("Special2 list printed\n");
            Sleep(1000);
        }
        else if (KEY(VK_SHIFT) && KEY(VK_F4))
        {
            printf("Printing static objects:\n\n");
            counter = 0;
            EnumStatic(EnumCallback_static_data);
            Sleep(1000);
        }
        else if (KEY(VK_SHIFT) && KEY(VK_F5))
        {
            printf("Printing weapons:\n\n");
            counter = 0;
            EnumWeapons(EnumCallback_weapons);
            Sleep(1000);
        }
        else if (KEY(VK_SHIFT) && KEY(VK_OEM_2))
        {
            printf("command:");
            char command[128] = { 0 };
            OBJECT* addr;
            gets_s(command);
            if (!strncmp(command, "goto",4))
            {
                if (command[6]=='x')
                    addr = (OBJECT*)strtol(&command[6], 0, 16);
                else
                    addr = (OBJECT*)strtol(&command[4], 0, 16);
                if (addr == nullptr || addr->index == 0) continue;
                printf("tping to %p\n", addr);
                memcpy(&Player->pos, &addr->pos,3*sizeof(uint32_t));
            }
            Sleep(1000);
        }
        Sleep(200);
    }

    //code end

end:
    printf("\nDLL terminated\n");
    FreeConsole();
    FreeLibraryAndExitThread((HINSTANCE)param, 0);
}

extern "C" BOOL WINAPI DllMain(
    HINSTANCE const instance,  // handle to DLL module
    DWORD     const reason,    // reason for calling function
    LPVOID    const) // reserved
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(instance); //disable useless thread notifs
        HANDLE hThread = CreateThread(0, 0, HackThread, instance, 0, NULL);
        if (!hThread)
            return FALSE;
        CloseHandle(hThread);
    }
    return TRUE;
}