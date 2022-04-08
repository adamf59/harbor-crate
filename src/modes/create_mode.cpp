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
    for (int argno = 2; argno < args.size(); argno++) {

        // parse the arguments into a string,string pair
        strstr_arg_pair arg_pair = this->parse_as_arg_pair(args.at(argno));

        // argument name is the first value in the pair
        std::string arg_name = arg_pair.first;

        if (arg_name == CRATE_NAME_ARG) {

        } else if (arg_name == HOSTNAME_ARG) {

        } else if (arg_name == NETWORK_ARG) {

        } else if (arg_name == MOUNT_ARG) {

        } else {
            // unknown argument
            // log error and quit with BADARGS
            PrettyPrint::log_error("create mode encountered unknown argument during parsing", true);
            return HBRC_EXIT_CODE_BADARGS;

        }

    } 

    PrettyPrint::log_error("this is work in progress!", true);



    return HBRC_EXIT_CODE_UNKNOWN;
}