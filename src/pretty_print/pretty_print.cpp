#include "pretty_print.hpp"
#include <stdio.h>
#include <string>

#define PRETTY_PRINT_PREFIX "harbor: "
#define PRETTY_PRINT_SUFFIX "\n"

#define ERROR_PREFIX "\033[31merror:\033[0m "
#define FATAL_ERROR_PREFIX "\033[31mfatal error:\033[0m "

#define WARNING_PREFIX "\033[33mwarning:\033[0m "


void PrettyPrint::log(const char* message) {

    printf("%s%s%s", PRETTY_PRINT_PREFIX, message, PRETTY_PRINT_SUFFIX);

}

void PrettyPrint::log_error(const char* message, bool fatal) {

    if (fatal) {

        printf("%s%s%s%s", PRETTY_PRINT_PREFIX, FATAL_ERROR_PREFIX, message, PRETTY_PRINT_SUFFIX);

    } else {

        printf("%s%s%s%s", PRETTY_PRINT_PREFIX, ERROR_PREFIX, message, PRETTY_PRINT_SUFFIX);

    }

}

void PrettyPrint::log_warning(const char * message, const char * vars...) {

    printf(std::string("%s%s").append(message).append("%s").c_str(), PRETTY_PRINT_PREFIX, WARNING_PREFIX, vars, PRETTY_PRINT_SUFFIX);

}