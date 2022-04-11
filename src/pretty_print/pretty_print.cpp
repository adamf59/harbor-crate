#include "pretty_print.hpp"
#include <stdio.h>
#include <string>
#include <stdarg.h>

#define PRETTY_PRINT_PREFIX "harbor: "
#define PRETTY_PRINT_SUFFIX "\n"

#define ERROR_PREFIX "\033[31merror:\033[0m "
#define FATAL_ERROR_PREFIX "\033[31mfatal error:\033[0m "

#define WARNING_PREFIX "\033[33mwarning:\033[0m "

void PrettyPrint::log_error(const char* message, bool fatal, ...) {

    // prepare va_list for holding va args
    va_list va_args_list;

    // print prefix
    printf(PRETTY_PRINT_PREFIX);

    if (fatal) {
        printf(FATAL_ERROR_PREFIX);
    } else {
        printf(ERROR_PREFIX);
    }

    // initialize the variadic args list
    va_start(va_args_list, message);

    // print args using vprintf
    vprintf(message, va_args_list);

    // close the variadic list
    va_end(va_args_list);

    // print suffix
    printf(PRETTY_PRINT_SUFFIX);

}

void PrettyPrint::log_warning(const char * message, const char * vars...) {

    printf(std::string("%s%s").append(message).append("%s").c_str(), PRETTY_PRINT_PREFIX, WARNING_PREFIX, vars, PRETTY_PRINT_SUFFIX);

}

void PrettyPrint::log(const char * message, ...) {

    // prepare va_list for holding va args
    va_list va_args_list;

    // print prefix
    printf(PRETTY_PRINT_PREFIX);

    // initialize the variadic args list
    va_start(va_args_list, message);

    // print args using vprintf
    vprintf(message, va_args_list);

    // close the variadic list
    va_end(va_args_list);

    // print suffix
    printf(PRETTY_PRINT_SUFFIX);

}