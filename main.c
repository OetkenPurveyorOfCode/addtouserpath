#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#pragma comment(lib, "Advapi32.lib")
#if LOG
#define add_tp_path_log(...) wprintf(__VA_ARGS__)
#else
#define add_to_path_log(...) 
#endif

typedef enum {
    ATP_FailedToSetRegistryKey,
    ATP_FailedToOpenRegistryKey,
    ATP_PathKeyNotExisting,
    ATP_Ok,
} AddToPathErr;

AddToPathErr add_to_path(const wchar_t* input_path) {
    wchar_t path[32*1024] = {'%', 'P', 'A', 'T', 'H', '%', ';'};
    wcscat(path, input_path);
    HKEY key_handle = 0;
    DWORD disposition = 0;
    LSTATUS status = RegCreateKeyExW(
        HKEY_CURRENT_USER,
        L"Environment",
        0,
        NULL,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        NULL,
        &key_handle,
        &disposition
    );
    if (status != ERROR_SUCCESS) {
        return ATP_FailedToOpenRegistryKey;
    }
    if (disposition != REG_OPENED_EXISTING_KEY) {
        return ATP_PathKeyNotExisting;
    }
    add_to_path_log(L"path \"%s\"\n", path);
    wchar_t path_expanded[32 *1024] = {0};
    ExpandEnvironmentStringsW(
        path,
        path_expanded,
        32*1024
    );
    add_to_path_log(L"path expanded %s\n", path_expanded);
    LSTATUS status2 = RegSetValueExW(
        key_handle,
        L"Path", //Automatically null terminated
        0,
        REG_EXPAND_SZ,
        (BYTE*) path_expanded,
        2 *wcslen(path_expanded) + 1
    );
    if (status2 == ERROR_SUCCESS) {
        return ATP_Ok;
    } else {
        return ATP_FailedToSetRegistryKey;
    }
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
int wmain(int argc, wchar_t** argv) {
    if (argc == 2) {
        wchar_t path[MAX_PATH];
        if(GetFullPathNameW(argv[1], MAX_PATH, path, NULL) == 0) {
            printf("Failed to obtain full path");
            exit(-1);
        }
        AddToPathErr err = add_to_path(path);
        if (err == ATP_Ok) {
            printf("Added Directory to path\n");
        }
        else if(err == ATP_FailedToOpenRegistryKey) {
            printf("Failed to open registry key\n");
        }
        else if(err == ATP_FailedToSetRegistryKey) {
            printf("Failed to set registry key\n");
        }
        else if (err == ATP_PathKeyNotExisting) {
            printf("Path Key does not exist\n");
        }
        else {
            printf("Unknown error");
            assert(0);
        }
    } else {
        printf("Usage: addtopath <dirname>");
    }
    return 0;
}
