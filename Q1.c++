#include <iostream>
#include <windows.h>

int main()
{
    int sharedVariable = 0;

    // Create child process 1
    STARTUPINFO si1 = {sizeof(si1)};
    PROCESS_INFORMATION pi1;
    if (!CreateProcess(NULL, "child1.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si1, &pi1))
    {
        std::cerr << "Failed to create child process 1." << std::endl;
        return 1;
    }

    // Create child process 2
    STARTUPINFO si2 = {sizeof(si2)};
    PROCESS_INFORMATION pi2;
    if (!CreateProcess(NULL, "child2.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2))
    {
        std::cerr << "Failed to create child process 2." << std::endl;
        return 1;
    }

    // Wait for child processes to finish
    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);

    // Print final value of shared variable
    std::cout << "Final value of sharedVariable: " << sharedVariable << std::endl;

    return 0;
}
