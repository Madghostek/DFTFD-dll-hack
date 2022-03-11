#include "silence.h"
#include <windows.h>
#include <stdio.h>

#include "ProcessHelp.h"

//stolen from github
inline bool InjectDLL(DWORD pid, const char* DLL_Path)
{
	size_t dll_size = strlen(DLL_Path) + 1;
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (hProc == NULL)
	{
		printf("[!]Failed to open target process!\n");
		return false;
	}
	printf("[+]Opening Target Process...\n");

	LPVOID MyAlloc = VirtualAllocEx(hProc, NULL, dll_size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (MyAlloc == NULL)
	{
		printf("[!]Failed to allocate memory in Target Process.\n");
		return false;
	}

	printf("[+]Allocating memory in Target Process.\n");
	int IsWriteOK = WriteProcessMemory(hProc, MyAlloc, DLL_Path, dll_size, 0);
	if (IsWriteOK == 0)
	{
		printf("[!]Failed to write in Target Process memory.\n");
		return false;
	}
	printf("[+]Creating Remote Thread in Target Process\n");

	HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
	if (!kernel32)
	{
		printf("You're on linux somehow\n");
		return false;
	}
	LPTHREAD_START_ROUTINE addrLoadLibrary = reinterpret_cast<LPTHREAD_START_ROUTINE>(reinterpret_cast<void*>(GetProcAddress(kernel32, "LoadLibraryA")));
	if (!addrLoadLibrary) 
	{
		printf("LoadLibrary not found\n");
		return false;
	}
	DWORD dWord;
	HANDLE ThreadReturn = CreateRemoteThread(hProc, NULL, 0, addrLoadLibrary, MyAlloc, 0, &dWord);
	if (ThreadReturn == NULL)
	{
		printf("[!]Failed to create Remote Thread\n");
		return false;
	}

	if ((hProc != NULL) && (MyAlloc != NULL) && (IsWriteOK != ERROR_INVALID_HANDLE) && (ThreadReturn != NULL))
	{
		printf("[+]DLL Successfully Injected\n");
		return true;
	}

	return false;
}

int main(int argc, char* argv[])
{
	if (argc == 0)
	{
		printf("Pass dll path with -dll");
		return -1;
	}
	char* dllpath = nullptr;
	for (int i = 0;i < argc;++i)
	{
		if (strstr(argv[i], "-dll"))
		{
			dllpath = &argv[i][5];
		}

	}
	DWORD pid = FindProcessId("DFTFD.exe");
	if (!pid)
	{
		printf("No DFTFD.exe\n");
		return -1;
	}
	InjectDLL(pid,dllpath);
	return 0;
}
