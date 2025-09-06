// ------------------------------------------------------------
// Class: Physics
// Brief: Don't ask me how it works: it's copy and pasted from an example
// Author: Ben Harper
// Date: 2025-09-06
// ------------------------------------------------------------
#pragma once

#include "Jolt/Jolt.h"
#include <Jolt/Core/IssueReporting.h>

// STL includes
#include <iostream>
#include <cstdarg>
#include <thread>


    // Callback for traces, connect this to your own trace function if you have one
    static void TraceImpl(const char *inFMT, ...)
    {
        // Format the message
        va_list list;
        va_start(list, inFMT);
        char buffer[1024];
        vsnprintf(buffer, sizeof(buffer), inFMT, list);
        va_end(list);

        // Print to the TTY
        std::cout << buffer << std::endl;
    }

    #ifdef JPH_ENABLE_ASSERTS

    // Callback for asserts, connect this to your own assert handler if you have one
    static bool AssertFailedImpl(const char *inExpression, const char *inMessage, const char *inFile, uint32_t inLine)
    {
        // Print to the TTY
        std::cout << inFile << ":" << inLine << ": (" << inExpression << ") " << (inMessage != nullptr? inMessage : "") << std::endl;

        // Breakpoint
        return true;
    };

    #endif // JPH_ENABLE_ASSERTS