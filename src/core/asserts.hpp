#pragma once

#include "defines.hpp"

#define UASSERTIONS_ENABLED

#ifdef UASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
/** @brief Causes a debug breakpoint to be hit. */
#define debugBreak() __debugbreak()
#else
/** @brief Causes a debug breakpoint to be hit. */
#define debugBreak() __builtin_trap()
#endif

/*
 * @brief Reports an assertion failure. Note that this is not the assertion itself,
 * just a reporting of an assertion failure that has already occurred.
 * @param expression The expression to be reported.
 * @param message A custom message to be reported, if provided.
 * @param file The path and name of the file containing the expression.
 * @param line The line number in the file where the assertion failure occurred.
 */
UAPI void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line);

/*
 * @brief Asserts the provided expression to be true, and logs a failure if not.
 * Also triggers a breakpoint if debugging.
 * @param expr The expression to be evaluated.
 */
#define UASSERT(expr)                                                \
    {                                                                \
        if (expr) {                                                  \
        } else {                                                     \
            report_assertion_failure(#expr, "", __FILE__, __LINE__); \
            debugBreak();                                            \
        }                                                            \
    }

/*
 * @brief Asserts the provided expression to be true, and logs a failure if not.
 * Allows the user to specify a message to accompany the failure.
 * Also triggers a breakpoint if debugging.
 * @param expr The expression to be evaluated.
 * @param message The message to be reported along with the assertion failure.
 */
#define UASSERT_MSG(expr, message)                                        \
    {                                                                     \
        if (expr) {                                                       \
        } else {                                                          \
            report_assertion_failure(#expr, message, __FILE__, __LINE__); \
            debugBreak();                                                 \
        }                                                                 \
    }

#ifdef _DEBUG
/*
 * @brief Asserts the provided expression to be true, and logs a failure if not.
 * Also triggers a breakpoint if debugging.
 * NOTE: Only included in debug builds; otherwise this is preprocessed out.
 * @param expr The expression to be evaluated.
 */
#define UASSERT_DEBUG(expr)                                          \
    {                                                                \
        if (expr) {                                                  \
        } else {                                                     \
            report_assertion_failure(#expr, "", __FILE__, __LINE__); \
            debugBreak();                                            \
        }                                                            \
    }
#else
#define UASSERT_DEBUG(expr)  // Does nothing at all
#endif

#else
#define UASSERT(expr)               // Does nothing at all
#define UASSERT_MSG(expr, message)  // Does nothing at all
#define UASSERT_DEBUG(expr)         // Does nothing at all
#endif