#include <iostream>
#include <vector>
#include <experimental/filesystem>
#include <memory>

namespace fs = std::experimental::filesystem;

int main()
{
    fs::create_directories(".lit/graph.txt");
    
}