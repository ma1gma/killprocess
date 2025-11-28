// ConsoleApplication5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <Windows.h>
#include <iostream>
#include <locale> 
#include <codecvt>
#include <string>
#include <Psapi.h>
#include <TlHelp32.h>

int main()
{
    
    DWORD dwPriorityClass = 0;
    std::string fas;
    DWORD pid = 0;
    std::cout << "input process name" << std::endl;
    std::getline(std::cin, fas);

    std::wstring wideString;
    try {

        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
        wideString = converter.from_bytes(fas);
    }
    catch (const std::range_error& e) {



        return 1;
    }
    LPCWSTR lpWindowName = wideString.c_str();
    HWND hwnd = FindWindowW(NULL, lpWindowName);
    if (!hwnd) {
        HWND error = NULL;
        LPCWSTR erors = L"Программа не запущена перезапустите с запуском программы";
        LPCWSTR errors_table = L"Ошибка 01";
        UINT Type = MB_OKCANCEL || MB_ICONWARNING;

        MessageBox(error, erors, errors_table, Type);
    }

    else {

        std::cout << "Addres: " << lpWindowName << std::endl;
        DWORD pids = GetWindowThreadProcessId(hwnd, &pid);
        
        if (!pid) {
            MessageBox(NULL, L"ошибка в нахождений pid", L"ошибка 0x2", MB_OK || MB_ICONWARNING);
        }
        else {
            /*std::cout << "sa" << std::endl;*/
            std::cout << "pid: " << pid << std::endl;
            HANDLE fas =  GetCurrentProcess();
            DWORD Access = PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE |PROCESS_VM_WRITE;
            BOOL bHandle = FALSE;
            HANDLE hprocces = OpenProcess(Access, bHandle, pid);
            if (!hprocces) {
                MessageBox(NULL, L"ошибка в нахождений hprocces", L"ошибка 0x3", MB_OK || MB_ICONWARNING);
            }
            else {
                std::cout << "HANDLE: " << hprocces << std::endl;
            /*    HANDLE fasf =*/
                DWORD threadid = GetThreadId(hprocces);
                std::cout <<"Thread id: " << threadid << std::endl;
              
                DWORD DwGetProcessId= GetProcessId(hprocces);
                if (!DwGetProcessId) {
                    MessageBox(NULL, L"ошибка в нахождени DwGetProcessID", L"ошибка 0x4", MB_OK || MB_ICONWARNING);
             }
                else {
                    std::cout <<"DwGetProcessID: "<< DwGetProcessId << std::endl;
                   
                    TCHAR szBuff[1024];
                    DWORD dwTemp;
                    MODULEENTRY32 meModuleEntry;
                   HANDLE CONST hSnapshot= CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
                   meModuleEntry.dwSize = sizeof(MODULEENTRY32);
                    Module32First(hSnapshot, &meModuleEntry);
                    CloseHandle(hSnapshot);
                    if (!hSnapshot) {
                        MessageBox(NULL, L"Error", L"Error 0x5", MB_OK || MB_ICONWARNING);
                   }
                
                    else {
                       
                        std::cout << "hSnapshot: " << hSnapshot << std::endl;
                        dwPriorityClass= GetPriorityClass(hprocces);
                        std::cout << "PriorityClass: " <<dwPriorityClass<< std::endl;
                        
                    }
                }
            }
        }
    }
   
    /*  GetWindowThreadProcessId()
    if (!hwnd || !)
        LPCWSTR lpText = L"Привет, мир! Это ваше информационное сообщение.";
LPCWSTR lpCaption = L"Пример MessageBox";
UINT uType = MB_OK | MB_ICONINFORMATION;*/
//MessageBoxW(hWnd, lpText, lpCaption, uType);*/ //MB_OKCANCEL

}





// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
