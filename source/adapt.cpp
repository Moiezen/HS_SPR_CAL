#include "deck.h"

#include <windows.h>
#include <psapi.h>
#include <tchar.h>
#include <tlhelp32.h>

TCHAR filename[MAX_PATH];

void getroutefromid(int pid) {
    HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (processHandle != NULL) {
        GetModuleFileNameEx(processHandle, NULL, filename, MAX_PATH);
        CloseHandle(processHandle);
    }
}

char target_hs[] = "Hearthstone.exe";
char target_hs_[] = "\\Hearthstone.exe";

void getroute() {
    HANDLE processHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (processHandle == INVALID_HANDLE_VALUE) {
        return;
    }

    PROCESSENTRY32 processentry32;
    processentry32.dwSize = sizeof(processentry32);
    bool bProcess = Process32First(processHandle, &processentry32);
    while (bProcess) {
        if (strcmp(processentry32.szExeFile, target_hs) == 0) {
            getroutefromid(processentry32.th32ProcessID);
        }
        bProcess = Process32Next(processHandle, &processentry32);
    }
    CloseHandle(processHandle);
}

string adaptlk() {
    getroute();
    string temp = filename;
    auto p = temp.find(target_hs_);
    if (p != -1) temp = temp.substr(0, p);
    return temp;
}
