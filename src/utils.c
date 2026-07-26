#include "../include/utils.h"

#ifdef _WIN32
#include <windows.h>
#endif

// Clear Screen
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pause Screen
void pauseScreen()
{
    printf("\nPress Enter to continue...");

    while (getchar() != '\n');

    getchar();
}