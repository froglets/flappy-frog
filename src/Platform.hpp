#pragma once

#if __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE
        #define IS_IOS
    #else
        #define IS_DESKTOP
    #endif
#else
    #define IS_DESKTOP
#endif
