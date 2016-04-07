#pragma once

//#define STUBBED(txt) fprintf(stderr, "STUB: %s in %s, line %d.\n", txt, __FILE__, __LINE__)
#ifndef STUBBED
    #define STUBBED(txt) do { \
        static bool already_seen = false; \
        if (!already_seen) { \
            already_seen = true; \
            fprintf(stderr, "STUBBED: %s in %s, line %d.\n", txt, __FILE__, __LINE__); \
        } \
    } while (0)
#endif