// Hack NotePad.exe

/*
*  For some reason i couldn't manage to make it write more than 39 letters per line
*  By. Potato Pie
* 
* 
* 
* 
* 
* 
* 
* 
* 
* */
#include "pch.h"
#include <iostream>
#include "stdio.h"
#include <Windows.h>
#include <cstdlib>

typedef unsigned long long uint64_t;


class TextData
{
public:
    wchar_t N0[38];
   
};
class PointerToText
{
public:
    TextData* Data;
    //char pad_[0x8];
};
class TextNotepad
{
public:
    PointerToText* Ptr;
};



TextNotepad* Text = nullptr;


const int ch_MAX = 45;
std::string RandomString(int ch)
{
    char alpha[ch_MAX] = { '!', '@', '#', '$', '%', '^', '&',
                          '2', '3', '4', '5', '6', '7', '8',
                          'a', '/', '*', '-', '+', '0', '1',
                          'b', 'c', 'd', 'e', 'f','g','h',
                          'i','j','k','l','m','n','o','p',
                          'q','r','s','t','u','v','x','y',
                          'z'};
    std::string result = "";
    for (int i = 0; i < ch; i++)
        result = result + alpha[rand() % ch_MAX];

    return result;
}


uint64_t __stdcall mainProg(HMODULE h_module) 
{   
    FILE* file=nullptr;
    Text = (TextNotepad*)((DWORD64)GetModuleHandleW(NULL) + (DWORD64)0x31690);

    AllocConsole();
    freopen_s(&file, "CONOUT$", "w", stdout);


   

    for (int j = 0; j <= 100; j++)
    {
        std::string Str = RandomString(38);

        std::wstring widestr = std::wstring(Str.begin(), Str.end());//L"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
        const wchar_t* lpReplace = widestr.c_str();
        int i = 0;
        if (j == 0)
        {
            lpReplace = L"NOTEPAD GOT HACKED                   ";
        }
        while (*(lpReplace + i))
        {

           
            Text->Ptr->Data->N0[i] = *(lpReplace + i);




            i++;
        }
        Sleep(500);
    }
    
   fclose(file);
   fclose(stdout);
   FreeConsole();
   Sleep(1000);
   FreeLibraryAndExitThread(h_module, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    
   
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

        _Post_ _Notnull_ CloseHandle(CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(mainProg), hModule, 0, nullptr));

        break;

    case DLL_THREAD_ATTACH:
        
        
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    default:
        break;
    }
    return TRUE;
}

