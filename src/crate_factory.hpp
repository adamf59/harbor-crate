#ifndef CRATE_FACTORY_H
#define CRATE_FACTORY_H
    
    #include <string>
    #include "modes/create_mode.hpp"

    typedef std::string crate_id_t;

    /**
     * @brief create a new crate 
     * @return null pointer if failure, else pointer to string of crate's id.
     */
    crate_id_t * create_crate(Create_Mode * cm_spec);

    /**
     * @brief create a new dock at path. docks are directories which contain crate information and container file systems.
     * 
     */
    void create_dock(std::string * path);

    /**
     * @brief validates that a dock exists at a given path, and that it is a valid configuration
     * 
     * @param path 
     * @return true 
     * @return false 
     */
    bool validate_dock(std::string * path);

    std::string expand_dock_to_realpath(std::string * path);

    /**
     * @brief generates a random hex string (size = 10, len = 9)
     * 
     * @return std::string* 
     */
    std::string * generate_crate_id();

#endif