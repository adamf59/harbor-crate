#include "mode.hpp"
#include "create_mode.hpp"
#include "../pretty_print/pretty_print.hpp"
#include "../hbr_crate.hpp"

// define optional arguments for create mode
#define MOUNT_ARG "mount"
#define NETWORK_ARG "network"
#define CRATE_NAME_ARG "name"
#define HOSTNAME_ARG "hostname"


int Create_Mode::process(std::vector<std::string> args) {

    // parse create mode arguments to fill fields before spinning up the crate
    for (size_t argno = 2; argno < args.size(); argno++) {

        // check the type of the argument (variable or flag)
        if (args.at(argno).find("=") == std::string::npos) {
            // handle the argument as a flag
            // not currently handled as there aren't any flags in create
            PrettyPrint::log_warning("ignoring flag %s", args.at(argno).c_str());
        } else {

            // parse the arguments into a string,string pair
            strstr_arg_pair * arg_pair = Mode::parse_as_arg_pair(args.at(argno));

            // argument name is the first value in the pair
            std::string arg_name = arg_pair->first;
            std::string arg_val = arg_pair->second;
            printf("parse %s = %s\n", arg_name.c_str(), arg_pair->second.c_str());

            if (arg_name == CRATE_NAME_ARG) {

                // set the new crate's name
                this->_cratename = arg_val;

            } else if (arg_name == HOSTNAME_ARG) {

                // set the new crate's hostname
                this->_hostname = arg_val;

            } else if (arg_name == NETWORK_ARG) {

                // set the new crate's network
                this->_network_mode = arg_val;

            } else if (arg_name == MOUNT_ARG) {

                this->_fsmounts.push_back("");

            } else {
                // unknown argument
                // log error and quit with BADARGS
                PrettyPrint::log_error("create mode encountered unknown argument during parsing", true);
                return HBRC_EXIT_CODE_BADARGS;

            }

    }

    } 

    return HBRC_EXIT_CODE_UNKNOWN;
}