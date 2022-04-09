#include "mode.hpp"

strstr_arg_pair * Mode::parse_as_arg_pair(std::string arg) {
    
    // find the equals sign to split the argument at
    size_t split_at = arg.find('=');

    // ensure the equals sign is present, and is not at the end or beginning of the string
    if (split_at == std::string::npos || split_at == 0 || split_at == arg.size() - 1) {
        // invalid argument - return a null pointer
        return NULL;
    }
    // return the pair of strings on either side of the equals sign
    return new strstr_arg_pair (arg.substr(0, split_at), arg.substr(split_at + 1));
}