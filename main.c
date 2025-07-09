#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

#pragma comment(lib, "Advapi32.lib")
#if LOG
#define add_tp_path_log(...) wprintf(__VA_ARGS__)
#else
#define add_to_path_log(...) 
#endif

#ifdef __TINYC__
typedef long LSTATUS;
#define wcscat_s(a, b, c) wcscat(a, c)
#endif

#define MAX_ENV (16*1024)

typedef enum {
    ATP_FailedToSetRegistryKey,
    ATP_FailedToOpenRegistryKey,
    ATP_FailedToGetRegistryKey,
    ATP_PathKeyNotExisting,
    ATP_Ok,
} AddToPathErr;

void PrintLastErrorMessage(DWORD errorCode)
{
    if (errorCode == 0)
    {
        printf("No error.\n");
        return;
    }

    LPWSTR messageBuffer = NULL;

    // Format the error message from the system
    DWORD size = FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR)&messageBuffer,
        0,
        NULL);

    if (size == 0)
    {
        printf("Failed to format error message. Error code: %lu\n", errorCode);
        return;
    }

    wprintf(L"Error 0x%08X: %s\n", errorCode, messageBuffer);

    // Free the buffer allocated by FormatMessage
    LocalFree(messageBuffer);
}

AddToPathErr add_to_path(const wchar_t* input_path) {
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
    wchar_t path[MAX_ENV] = {0};
    DWORD old_path_size = MAX_ENV*2;
    status = RegGetValueW(
        key_handle,
        L"",
        L"Path",
        RRF_RT_ANY,
        NULL,
        path,
        &old_path_size
    );
    if (status == ERROR_MORE_DATA) {
        printf("more data");
    }
    if (status == ERROR_FILE_NOT_FOUND) {
        printf("key not found");
    }
    if (status != ERROR_SUCCESS) {
        PrintLastErrorMessage(status);
        return ATP_FailedToGetRegistryKey;
    }
    wprintf(L"%ls", path);
    wcscat_s(path, MAX_ENV, L";");
    wcscat_s(path, MAX_ENV, input_path);
    status = RegSetValueExW(
        key_handle,
        L"Path",
        0,
        REG_EXPAND_SZ,
        (BYTE*)path,
        (DWORD)(2*wcslen(path) + 1)
    );
    if (status != ERROR_SUCCESS) {
        return ATP_FailedToSetRegistryKey;
    }
    return ATP_Ok;
}

#ifdef __GNUC__
int main(int _argc, char** _argv) {
    (void) _argc; (void) _argv;
    int argc = 0;
    wchar_t ** argv = CommandLineToArgvW(GetCommandLineW(), &argc);
#else                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
int wmain(int argc, wchar_t** argv) {
#endif
    if (argc == 2) {
        wchar_t path[MAX_PATH];
        if(GetFullPathNameW(argv[1], MAX_PATH, path, NULL) == 0) {
            printf("Failed to obtain full path");
            exit(-1);
        }
        AddToPathErr err = add_to_path(path);
        switch (err) {
            break;case ATP_Ok: {
                printf("Added Directory to path\n");
            }
            break;case ATP_FailedToOpenRegistryKey: {
                printf("Failed to open registry key\n");
            }
            break;case ATP_FailedToSetRegistryKey: {
                printf("Failed to set registry key\n");
            }
            break;case ATP_FailedToGetRegistryKey: {
                printf("Failed to get registry key\n");
            }
            break;case ATP_PathKeyNotExisting: {
                printf("Path Key does not exist\n");
            }
            break;default: assert(0);
        }
    } else {
        printf("Usage: addtopath <dirname>");
    }
    return 0;
}
