#ifndef MODE_H
#define MODE_H

    #include <vector>
    #include <string>


    class Mode {

        public:
            /**
             * @brief process commands from an argument vector for this mode
             * 
             * @return int 
             */
            int process(std::vector<std::string> args);

    };

    
    

#endif