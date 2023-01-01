#ifndef _DUSK_PLATFORM_DETECTION_HPP_
#define _DUSK_PLATFORM_DETECTION_HPP_

// One macro for Windows
#if !defined(_WIN32) && (defined(__WIN32__) || defined(WIN32) || defined(__MINGW32__))
    #define _WIN32
#endif

// Platform detection using predefined macros
#ifdef _WIN32
    /* Windows x64/x86 */
    #ifdef _WIN64
        #define DUSK_PLATFORM_WINDOWS
        /* Windows x64  */
    #else
        /* Windows x86 */
        #error "x86 Builds are not supported!"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #include <TargetConditionals.h>
    /* TARGET_OS_MAC exists on all the platforms
     * so we must check all of them (in this order)
     * to ensure that we're running on MAC
     * and not some other Apple platform
     */
    #if TARGET_IPHONE_SIMULATOR == 1
        #error "IOS simulator is not supported!"
    #elif TARGET_OS_IPHONE == 1
        #error "IOS is not supported!"
    #elif TARGET_OS_MAC == 1
        #error "MacOS is not supported!"
    #else
        #error "Unknown Apple platform!"
    #endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
    #error "Android is not supported!"
#elif defined(__linux__)
    #define DUSK_PLATFORM_LINUX
#else
    /* Unknown compiler/platform */
    #error "Unknown platform!"
#endif // End of platform detection

#endif // !_DUSK_PLATFORM_DETECTION_HPP_
