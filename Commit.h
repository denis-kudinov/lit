#include <iostream>
#include <vector>
#include <experimental/filesystem>
#include <memory>

namespace fs = std::experimental::filesystem;
class Commit
{
private:
    static int id;
    std::string message;
    const std::string currentId;
    fs::path pathToDedicatedFolder;
    std::shared_ptr<Commit> parent;

public:
    Commit(std::string message, std::shared_ptr<Commit> parent)
    : message(message)
    , currentId("r" + std::to_string(id++))
    , parent(parent)
    {}

    Commit(): currentId("r" + std::to_string(id++)) {}
    
};