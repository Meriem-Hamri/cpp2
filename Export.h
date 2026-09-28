#ifndef EXPORT_H
#define EXPORT_H

#if defined(_WIN32) || defined(__CYGWIN__)
    #ifdef BIBLIOTHEQUE_EXPORTS
        #define BIBLIOTHEQUE_API __declspec(dllexport)
    #else
        #define BIBLIOTHEQUE_API __declspec(dllimport)
    #endif
#else
    #define BIBLIOTHEQUE_API
#endif

#endif
