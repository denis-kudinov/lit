#include <iostream>
#include <vector>
#include <experimental/filesystem>
#include <memory>

namespace fs = std::experimental::filesystem;
class Commit
{
private:
    static int id;
    //fs::path pathToDedicatedFolder;
    
public:

    const std::string currentId;
    const int currentId_int;
    const std::string message;
    const std::shared_ptr<Commit> parent;
    // TODO timestamp

    Commit(std::string message, std::shared_ptr<Commit> parent)
    : message(message)
    , currentId("r" + std::to_string(id++))
    , currentId_int(id)
    , parent(parent)
    {
        //if(!parent)
        //TODO создать папку
        //if message empty
            
        
    }
};
int Commit::id = 0;