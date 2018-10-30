#include "../inc/utils.hpp"



bool IsValidCommand(std::string input)
{
    

    std::string add_pattern      = "(^Add [a-zA-Z]+ to [a-zA-Z]+$)|";
    std::string delete_pattern   = "(^Delete [a-zA-Z]+$)|";
    std::string update_pattern   = "(^Update [a-zA-Z]+ to [a-zA-Z]+$)|";
    std::string gameover_pattern = "(^Game Over$)|";
    

    std::string all_patterns = add_pattern + delete_pattern + update_pattern + gameover_pattern ;
    std::regex pattern(all_patterns);

    if(std::regex_match(input, pattern))
    {
        return true;
    }


    return false;


}

bool IsValidUserInput(std::string input)
{
   
    std::string dir_inv_pattern = "(^[nswei]$)|";
    std::string attack_pattern  = "(^attack [a-zA-Z]+ with [a-zA-Z]+$)|";
    std::string take_pattern    = "(^take [a-zA-Z]+$)|";
    std::string read_pattern    = "(^read [a-zA-Z]+$)|";
    std::string drop_pattern    = "(^drop [a-zA-Z]+$)|";
    std::string put_pattern     = "(^put [a-zA-Z]+ in [a-zA-Z]+$)|";
    std::string open_pattern    = "(^open [a-zA-Z]+$)|";
    std::string turnon_pattern  = "(^turn on [a-zA-Z]+$)|";
    std::string quit_pattern    = "(^quit$)";

    std::string all_patterns = attack_pattern + take_pattern + read_pattern + 
                               drop_pattern   + put_pattern  + open_pattern + 
                               turnon_pattern + dir_inv_pattern + quit_pattern ;
                               
    std::regex pattern(all_patterns);

    if(std::regex_match(input, pattern))
    {
        return true;
    }


    return false;


}