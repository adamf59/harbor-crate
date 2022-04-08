#include "mode.hpp"

strstr_arg_pair Mode::parse_as_arg_pair(std::string arg) {
    
    // find the equals sign to split the argument at
    int split_at = arg.find('=');

    if (split_at == -1) {
        return strstr_arg_pair (NULL, NULL);
    }

}