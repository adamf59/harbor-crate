#include <stdio.h>
#include <vector>
#include <iostream>
#include "hbr_crate.hpp"
#include "pretty_print/pretty_print.hpp"

// harbor crate entry point
int main(int argc, const char** argv) {

     // load arguments into a cpp vector of strings
     // define a std::string vector for our arguments
    std::vector<std::string> arguments_vector;

    // load argv arguments into the vector
    for (int argno = 0; argno < argc; argno++) {
        arguments_vector.push_back(std::string(argv[argno]));
    }

    // return the exit code from the argument command handler
    return handle_harbor_arguments(arguments_vector);

}

int handle_harbor_arguments(std::vector<std::string> args) {

    // determine the command mode, and pass execution to that mode handler

    // check argument vector size, must be at least 2
    if (args.size() < 2) {
        // insuffiencent number of arguments provided
        // give error and exit with BADARGS
        PrettyPrint::log_error("not enough arguments", true);
        return HBRC_EXIT_CODE_BADARGS;
    }
    
    // first argument is always the mode
    std::string command_mode = args.at(1);

    // pass argument to the correct mode handler
    if (command_mode == HBRC_MODE_CREATE) {
        // create command mode

    } else if (command_mode == HBRC_MODE_DELETE) {
        // delete command mode

    } else if (command_mode == HBRC_MODE_EXECUTE) {
        // execute command mode

    } else {
        // unrecognized command mode
        // throw an error to the user and exit with BADMODE.
        PrettyPrint::log_error("invalid mode specified", true);
        return HBRC_EXIT_CODE_BADMODE;
    }

}
