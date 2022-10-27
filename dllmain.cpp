// Hack NotePad.exe

/*
*  
*  By. Potato Pie (SK)
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
#include <cstring>
#include <string>
#include <stdlib.h>
#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
typedef unsigned long long uint64_t;
using namespace cv;

class TextData
{
public:
    wchar_t N0[38];
   
};

class PointerToText
{
public:
   
    PWCHAR Data;
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
    //TextN = (NotePadPP*)((DWORD64)GetModuleHandleW(NULL) + (DWORD64)0x44AB78);
    AllocConsole();
    freopen_s(&file, "CONOUT$", "w", stdout);


    std::string filename = "C:\\Users\\User\\source\\repos\\NotePadHack\\NotePadHack\\Psyc.mp4";
    VideoCapture capture(filename);
    Mat frame;
    Mat gray_image;
    if (capture.isOpened())
    {   
       
        for (;;)
        {
            capture >> frame;
            if (frame.empty())
                break;
            
            
            //std::cout << frame.cols << " " << frame.rows << std::endl;
            
            resize(frame, gray_image, cv::Size(1024,1024), 0, 0, INTER_LINEAR);
            cvtColor(gray_image, gray_image, COLOR_BGR2GRAY);
            imshow("gray",gray_image);
            const char* ASCII = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
            int shades = 255 / strlen(ASCII);
            auto charArray = new char[1024*1024];
            
            std::cout << gray_image.rows << gray_image.cols << std::endl;
            for (int i = 0; i < gray_image.rows; i++)
            {   
                int j = 0;
                for (j = 0; j < gray_image.cols; j++)
                {
              
                        int Scale = (int)gray_image.at<uchar>(i, j);
                        int charIndex = std::ceil(float(Scale) / float(shades));
                        const char c = ASCII[charIndex];



                       charArray[i*gray_image.rows+j] = c;
                    
                    
                    
                        //Text->Ptr->Data[i*gray_image.cols+j] = c;

                        //std::cout << "replacing" << std::endl;
                   

                }
                //charArray[i * gray_image.rows + j + 1] = (char)("\r");
                //charArray[i * gray_image.rows + j + 2] = (char)("\n");
               // Text->Ptr->Data[i] = *const_cast<wchar_t*>(L"\r\n");


            }
         
            
               //int nChars = MultiByteToWideChar(CP_ACP, 0, charArray, -1, NULL, 0);

               //const wchar_t* lpReplace = new WCHAR[nChars];
               // MultiByteToWideChar(CP_ACP, 0, charArray,-1, (LPWSTR)lpReplace, nChars);
             
                 
                //int i = 0;

                
                std::string Str(&charArray[0],&charArray[1024*1024-1]);
                std::wstring widestr =  std::wstring(Str.begin(), Str.end());
                const wchar_t* lpReplace = widestr.c_str();
                
               // const size_t size = strlen(charArray) + 1;
                //wchar_t* lpReplace = new wchar_t[size];
                //mbstowcs_s(&lpReplace[0], &charArray[0], size);
                //size_t SizeAfterConverted;
                //std::mbstowcs(&lpReplace[0], &charArray[0], size);
                
               
                //mbstowcs_s(&SizeAfterConverted,lpReplace, 0,charArray, size-1);
               
                
               
                //const char* ccp = reinterpret_cast<const char*>(charArray);
                //size_t len = std::mbstowcs(nullptr, &ccp[0], 0);
                //mbstowcs_s(&SizeAfterConverted, &lpReplace[0], size, &charArray[0], size);
                //std::cout << SizeAfterConverted << std::endl;
                std::cout << widestr.size()  << std::endl;
                memcpy(Text->Ptr->Data, lpReplace,widestr.size()*sizeof(wchar_t));
                //delete[] lpReplace;
                //strcpy(Text->Ptr->Data, lpReplace);
                /* while (*(lpReplace + i))
                {

                   // std::cout << "2222222222" << std::endl;
                    
                    Text->Ptr->Data[i] = *(lpReplace + i);

                   
                    i++;
                }*/
                //delete[] lpReplace;
                delete[] charArray;
                charArray = nullptr;
                waitKey(5);
        }
        
        /*for (int j = 0; j <= 100; j++)
        {
            std::string Str = RandomString(80);//RandomString(38);

            std::wstring widestr = L"OOOOOO\r\nIIIIII";std::wstring(Str.begin(), Str.end());//L"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
            const wchar_t* lpReplace = widestr.c_str();
            int i = 0;

            while (*(lpReplace + i))
            {


                Text->Ptr->Data[i] = *(lpReplace + i);
              

                i++;
            }
            Sleep(500);
            if (j == 1) break;
        }*/
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

