#include "crate_factory.hpp"
#include "pretty_print/pretty_print.hpp"
#include "hbr_crate.hpp"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>

crate_id_t * create_crate(Create_Mode * cm_spec) {

    // check that the target dock exists (or create it)
    if (!validate_dock(cm_spec->get_dock())) {

        // create a new dock
        create_dock(cm_spec->get_dock());
    } else {
        PrettyPrint::log("using existing dock");
    }

    // change directory to the dock
    std::string rpath = expand_dock_to_realpath(cm_spec->get_dock());
    
    if (chdir(rpath.c_str()) == -1) {
        // error switching directories to dock
        PrettyPrint::log_error("chdir: %s", true, strerror(errno));
        exit(HBRC_EXIT_CODE_UNKNOWN);
    }

    // assign a unique crate id
    std::string * crate_id = generate_crate_id();

    if (mkdir(crate_id->c_str(), 220) == -1) {
        PrettyPrint::log_error("creating crate directory: %s", true, strerror(errno));
        exit(HBRC_EXIT_CODE_UNKNOWN);
    }
    
    PrettyPrint::log("successfully built %s", crate_id->c_str());
}

void create_dock(std::string * path) {

    // absolute path to the directory to create a dock in
    std::string init_dock_path = expand_dock_to_realpath(path);

    // print dock creation location
    PrettyPrint::log("creating dock: %s%s", init_dock_path.c_str());

    // call mkdir to create the directory
    if (mkdir(init_dock_path.c_str(), 220) == -1) {
        
        PrettyPrint::log_error("when creating dock: %s", true, strerror(errno));
        
        exit(HBRC_EXIT_CODE_EACCES);
    }


}

bool validate_dock(std::string * path) {

    // expand to a realpath
    std::string rpath = expand_dock_to_realpath(path);

    // ensure the path exists and is accessable
    if (access(rpath.c_str(), F_OK) == -1) {
        return false;
    }

    return true;
}

std::string expand_dock_to_realpath(std::string * path) {

    std::string rpath;
    
    // if path is null, use $USER_HOME/
    if (path == NULL) {

        // get the user passwd entry, containing their home dir
        struct passwd * upw_entry = getpwuid(getuid());
        // convert to std::string
        std::string user_home_path (upw_entry->pw_dir);
        
        rpath = user_home_path.append("/.harbor/");

    } else {

        // expand path using realpath

    }

    return rpath;

}

std::string * generate_crate_id() {

    // create char array for holding random values
    char id[10] = {0};
    // set the randomness seed to time. security is not an issue here becuase we really just need a mostly unique value
    srand (time(NULL));
    // insert the random hex values in to the char array
    for (int i = 0; i < 9; i++) {
        sprintf(&id[i], "%x", rand() % 16);
    }

    return new std::string(id);
}