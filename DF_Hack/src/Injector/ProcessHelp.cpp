#include <windows.h>
#include <tlhelp32.h>
#include <stdlib.h>
#include <stdio.h>

//bool CheckRunning(DWORD pid)
//{
//    HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
//    THREADENTRY32 te32;
//    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pid);
//    if (hThreadSnap == INVALID_HANDLE_VALUE)
//        return false;
//
//    // Fill in the size of the structure before using it. 
//    te32.dwSize = sizeof(THREADENTRY32);
//
//    // Retrieve information about the first thread,
//    // and exit if unsuccessful
//    if (!Thread32First(hThreadSnap, &te32))
//    {
//        CloseHandle(hThreadSnap);     // Must clean up the snapshot object!
//        return false;
//    }
//
//    // Now walk the thread list of the system,
//    // and display information about each thread
//    // associated with the specified process
//    do
//    {
//        if (te32.th32OwnerProcessID == pid)
//        {
//            printf("\n     THREAD ID      = 0x%08X", te32.th32ThreadID);
//            printf("\n     base priority  = %d", te32.tpBasePri);
//            printf("\n     delta priority = %d", te32.tpDeltaPri);
//        }
//    } while (Thread32Next(hThreadSnap, &te32));
//
//    printf(TEXT("\n"));
//
//    //  Don't forget to clean up the snapshot object.
//    CloseHandle(hThreadSnap);
//    return(TRUE);
//}

DWORD FindProcessId(const char* processName)
{
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    Process32First(processesSnapshot, &processInfo);
    do
    {
        if (!strcmp(processName, processInfo.szExeFile))
        {
            HANDLE test = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processInfo.th32ProcessID);
            if (test)
            {
                CloseHandle(test);
                CloseHandle(processesSnapshot);
                return processInfo.th32ProcessID;
            }
            else
            {
                printf("[-] skipping sus\n");
            }
        }
    } while (Process32Next(processesSnapshot, &processInfo));

    CloseHandle(processesSnapshot);
    return 0;
}
