#ifndef MODE_H
#define MODE_H

    #include <vector>
    #include <string>

    typedef std::pair<std::string, std::string> strstr_arg_pair;

    class Mode {

        public:
            /**
             * @brief process commands from an argument vector for this mode
             * 
             * @return int 
             */
            int process(std::vector<std::string> args);
        protected:
            /**
             * @brief parse a string with the format "X=Y" into a pair with first=X, second=Y
             * 
             * @param arg argument string to parse
             * @return std::pair<std::string, std::string> 
             */
            static strstr_arg_pair * parse_as_arg_pair(std::string arg);

    };

    
    

#endif