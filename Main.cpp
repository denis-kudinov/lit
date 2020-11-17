#include <iostream>
#include <experimental/filesystem>
//#include "FileWatcher.h"
#include "Lit.h"
#include <limits.h>
#include <unistd.h>
#include <vector>

namespace fs = std::experimental::filesystem;

using namespace std; //TODO

int main(int argc, char* argv[])
{
    vector<string> argv_s;
    
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
    catch(const string& e)
    {
        std::cout << e << '\n';
    }
    
    

    const fs::path workdir = fs::current_path();
    cout << workdir << endl;
    return 0;
}