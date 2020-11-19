#include <iostream>
//#include "Graph.h"
#include "Lit.h"
#include <limits.h>
#include <unistd.h>
#include <vector>

int main(int argc, char* argv[])
{
    std::vector<std::string> argv_s;
    
    for (int i = 0; i < argc; i++)
    {
        argv_s.push_back(argv[i]);
    }

    //argv_s.push_back("commit");
    //argv_s.push_back("lol");

    try
    {
        if(argv_s.size() < 2) //TODO
        {
            std::cout << "Use 'lit help'.\n";
            
        }
        else
        {

            
            Lit* lit = new Lit(argv_s);
            
            
            
            delete lit;
        }
            
    }
    catch(const std::string& e)
    {
        std::cout << e << '\n';
    }
    
    

    //const fs::path workdir = fs::current_path();
    //std::cout << workdir << std::endl;
    return 0;
}