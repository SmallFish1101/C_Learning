#include <stdio.h>

#ifdef _WIN32
    #define PLATFORM "Windows"
    #define PATH_SEP '\\'
#elif defined(__linux__)
    #define PLATFORM "Linux"
    #define PATH_SEP '/'
#else
    #define PLATFORM "Unknown"
    #define PATH_SEP '/'
#endif

int main(void) {
    printf("Running on %s, path separator is '%c'\n", PLATFORM, PATH_SEP);
    return 0;
}