#include <iostream>
#include <experimental/filesystem>
#include <limits.h>
#include <unistd.h>
#include <vector>
#include "Exception.h"

namespace fs = std::experimental::filesystem;

class Lit
{
public:
    Lit(const std::vector<std::string>& argv)
    {
        if(!CheckRepo())
        {
            if(argv[1] == "init")
            {
                init();
            }
            else 
            {
                std::cout << "Not a lit repository. Use 'lit init' to initialize the repository." << std::endl;
                //throw Exception("Not a lit repository. Use 'lit init' to initialize the repository.");
                return;
            }
        }
        if (argv[1] == "help")
        {
            
        } 
        else if(argv[1] == "status")
        {

        }
    }

private:
    bool CheckRepo()
    {
        const fs::path workdir = fs::current_path();
        const fs::path litPath = workdir / ".lit";
        if (!fs::exists(litPath))
            return false;
        return true;
    }

    bool init()
    {
        if(!fs::create_directories(".lit"))
        {
            throw Exception(".lit directory cannot be created");
            return false;
        }

        std::cout << "init lol" << std::endl;
        // TODO сделать первый коммит и где то их хранить 
    }
};