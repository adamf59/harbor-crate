#include "execute_mode.hpp"
#include "../crate_factory.hpp"
#include "../pretty_print/pretty_print.hpp"

int Execute_Mode::process(std::vector<std::string> args) {

    // harbor-crate execute <crate_id> <executable> [-detach]

    // check args length to ensure proper invokation
    if (args.size() < 4) {
        // not enough arguments, print usage
        printf("usage: %s execute crate_id executable_path [-d] [-v]\n", args.at(0).c_str());
        exit(HBRC_EXIT_CODE_BADARGS);
    }

    crate_id_t crate_id = args.at(2);
    std::string executable = args.at(3);

    this->_dock_path = NULL;
    this->_crate_id = new std::string(crate_id);
    this->_executable = executable;
    this->_detach = false;

    return crate_execute(this);
    
}