#include "pretty_print.hpp"
#include <stdio.h>

#define PRETTY_PRINT_PREFIX "harbor: "
#define PRETTY_PRINT_SUFFIX "\n"

#define ERROR_PREFIX "\033[31merror:\033[0m "
#define FATAL_ERROR_PREFIX "\033[31mfatal error:\033[0m "


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