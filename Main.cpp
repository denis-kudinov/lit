#include <iostream>
//#include "FileWatcher.h"
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

    try
    {
        if(argc < 2)
        {
            throw Exception("Use 'lit help'");
            
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
    
    

    const fs::path workdir = fs::current_path();
    std::cout << workdir << std::endl;
    return 0;
}