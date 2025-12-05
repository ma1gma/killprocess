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

    FILETIME lpCreationTime;
    FILETIME lpExitTime;
    FILETIME lpKernelTime;
    FILETIME lpUserTime;
    std::string fas;
    DWORD pids = 0;
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
    DWORD sizea;
    std::cout << "Do you want to get the process PID?" << std::endl;
    std::string ifs_yes_no;
    std::cin >> ifs_yes_no;
    
    if (ifs_yes_no == "yes") {
        /*DWORD dwPriorityClass = 0;*/
       
        
        LPCWSTR lpWindowName = wideString.c_str();
        HWND hwnd = FindWindowW(NULL, lpWindowName);
        if (!hwnd) {
            HWND error = NULL;
            LPCWSTR erors = L"Программа не запущена перезапустите с запуском программы";
            LPCWSTR errors_table = L"Ошибка";
            UINT Type = MB_OKCANCEL || MB_ICONWARNING;

            MessageBox(error, erors, errors_table, Type);
        }
        else {
            DWORD pids = GetWindowThreadProcessId(hwnd, &pids);
            /*std::cout << "PID your programm" << std::endl;*/
            if (!pids) {
                MessageBox(NULL, L"PID error", L"PID error programm exit", 0);

                return 0;
            }
            else {
                std::cout << "Your pid programm: " << pids << std::endl;
                std::cout << "functions open:" << std::endl;
                std::cout << "1.getting hprocess program" << std::endl;
                std::cout << "0.Exit" << std::endl;

                int sads;
                std::cin >> sads;
                if (sads == 1) {
                    GetWindowThreadProcessId(
                       hwnd,&pids);
                    //        DWORD Access = ;
                    //        BOOL bHandle = FALSE;
                    //        HANDLE hprocces = OpenProcess(Access, bHandle, pid);
                    //        if (!hprocces) {
                    //            MessageBox(NULL, L"ошибка в нахождений hprocces", L"ошибка 0x3", MB_OK || MB_ICONWARNING);
                    //        }
                    DWORD Acces = PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE |PROCESS_VM_WRITE;
                    HANDLE hprocess = OpenProcess(Acces, FALSE, pids);
                    std::cout << hprocess << std::endl;
                    if (!hprocess) {
                        DWORD errorCode = GetLastError(); 
                        std::string errorMessage = "hprocess error. Code: " + std::to_string(errorCode);
                        MessageBoxA(NULL, errorMessage.c_str(), "hprocess error exit", MB_OK | MB_ICONERROR);
                        
                    }
                    else {
                        std::cout << "Your hprocess" << hprocess << std::endl;
                        std::cout << "New functions :" << std::endl;
                        std::cout << "1.ReadProcessMemory: " << std::endl;
                        std::cout << "2.KillProcess" << std::endl;
                        std::cout << "3.getting PID via hprocess" << std::endl;
                        std::cout << "4.Determine whether a process is considered critical" << std::endl;
                        std::cout << "5.Retrieve timing information for the specified process.(working)" << std::endl;
                        std::cout << "6.Disables or enables the system's ability to temporarily raise the priority of the specified process's threads." << std::endl;
                        int number;
                        std::cin >> number;
                        if (number == 1) {
                            std::cout << "Give me addres(use own risk)" << std::endl;
                            DWORD addres_read=0;
                            std::cout << "Give me the type of data that is stored at this address(format 0x)" << std::endl;
                            std::string sasd;
                            std::cin >> sasd;
                            if (sasd == "int") {
                                DWORD read_process_memory = 0;
                                ReadProcessMemory(hprocess, (PBYTE*)addres_read, (LPVOID)read_process_memory, sizeof(read_process_memory), 0);
                            }
 /*                           else if (sasd == "BOOL") {
                                BOOL read_process_memory1;
                                ReadProcessMemory(hprocess, (PBYTE*)addres_read, (LPVOID)read_process_memory1, sizeof(read_process_memory1), 0);
                            }*/
                            //else if (sasd == "string") {
                            //    MessageBox(NULL, L"string non supported", L"string non suppored", 0);
                            //    return 0;
                            //}
                            //else if (sasd == "float") {
                            //    MessageBox(NULL, L"float non supported", L"float non suppored", 0);
                            //    return 0;
                            //}
                        }
                        else if (number == 2) {
                            TerminateProcess(hprocess, 0);
                           HWND hwnd1= FindWindow(NULL, lpWindowName);
                           if (!hwnd1) {
                               
                               MessageBox(NULL, L"the program was closed successfully", L"succes", MB_OK);
                           }
                        }
                        else if (number == 3) {
                            DWORD DwGetProcessId = GetProcessId(hprocess);
                            if (!DwGetProcessId) {
                                MessageBox(NULL, L"error", L"error", 0);
                                return 0;
                            }
                            else {
                                std::cout <<"DwGetProcessId: " << DwGetProcessId << std::endl;

                            }
                        }
                   
                        else if (number == 4) {
                            BOOL critical;
                            IsProcessCritical(
                                hprocess,&critical
                            );
                            std::cout <<"Critical: " << &critical << std::endl;
                        }
                        else if (number == 5) {
                            GetProcessTimes(
                                hprocess,
                                &lpCreationTime, &lpExitTime, &lpKernelTime,&lpUserTime
                            );
                            
                        } 
                        else {
                            std::cout << "TRUE/FALSE" << std::endl;
                            std::string true_false;
                            std::cin >> true_false;
                            if (true_false == "TRUE") {
                                SetProcessPriorityBoost(hprocess,TRUE);
                            }
                            else {
                                SetProcessPriorityBoost(hprocess, FALSE);
                            }
                        }
                    }

                }
                else {
                    MessageBox(NULL, L"Exit", L"Exit", MB_OK);
                }

            }

        }



        //            DWORD DwGetProcessId= GetProcessId(hprocces);
        //            if (!DwGetProcessId) {
        //                MessageBox(NULL, L"ошибка в нахождени DwGetProcessID", L"ошибка 0x4", MB_OK || MB_ICONWARNING);
        //         }
        //            else {
        //                std::cout <<"DwGetProcessID: "<< DwGetProcessId << std::endl;
        //               
        //                TCHAR szBuff[1024];
        //                DWORD dwTemp;
        //                MODULEENTRY32 meModuleEntry;
        //               HANDLE CONST hSnapshot= CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
        //               meModuleEntry.dwSize = sizeof(MODULEENTRY32);
        //                Module32First(hSnapshot, &meModuleEntry);
        //                CloseHandle(hSnapshot);
        //                if (!hSnapshot) {
        //                    MessageBox(NULL, L"Error", L"Error 0x5", MB_OK || MB_ICONWARNING);
        //               }
        //            
        //                else {
        //                   
        //                    std::cout << "hSnapshot: " << hSnapshot << std::endl;
        //                    dwPriorityClass= GetPriorityClass(hprocces);
        //                    std::cout << "PriorityClass: " <<dwPriorityClass<< std::endl;
        //                   /* ReadProcessMemory(hprocces,(PBYTE*)addres,&sizea,sizeof(sizea), 0);*/

        //                }     
        //        }
        //    }
        // 
        //}

        /*  GetWindowThreadProcessId()
        if (!hwnd || !)
            LPCWSTR lpText = L"Привет, мир! Это ваше информационное сообщение.";
    LPCWSTR lpCaption = L"Пример MessageBox";
    UINT uType = MB_OK | MB_ICONINFORMATION;*/
    //MessageBoxW(hWnd, lpText, lpCaption, uType);*/ //MB_OKCANCEL
    }
    else {
        std::cout << "exit good luck" << std::endl;
        MessageBox(NULL, L"Завершение", L"Программа завершена по желанию пользователя", MB_OK);
        return 0;
    }

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
