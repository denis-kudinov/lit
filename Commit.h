#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include <chrono>
#include <ctime>

namespace fs = std::experimental::filesystem;
class Commit
{   
public:
    const std::string id_str;
    const int id_int;
    const std::string message;
    const int parentId_int;
    time_t currentTime;

    Commit(std::string message, int id, int parentId_int)
    : message(message)
    , id_str("r" + std::to_string(id))
    , id_int(id)
    , parentId_int(parentId_int)
    , currentTime(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))
    {
        PutInfo();

        Show();
    }

    void Show(bool display_diff=false)
    {
        std::cout << "Commit: " << id_str << "\n";
        if(parentId_int == -1)
            std::cout << "Root commit" << "\n";
        else
            std::cout << "Parent: r" << parentId_int << "\n";
        std::cout << "Date: " << ctime(&currentTime) << "\n";

        if (!display_diff)
            return;
        
        std::ifstream in(".lit/commits/" + id_int);
        std::string s;
        while(getline( in, s ))
        {
            std::cout << s << std::endl;
        }
        in.close();
    }

    void PutInfo()
    {
        fs::create_directories(".lit/commits/" + std::to_string(id_int) + "/");
        std::ofstream out(".lit/commits/" + std::to_string(id_int) + "/info.txt");
        out << "Commit: " << id_str << "\n";
        if(parentId_int == -1)
            out << "Root commit" << "\n";
        else
            out << "Parent: r" << parentId_int << "\n";
        out << "Date: " << ctime(&currentTime) << "\n";
        if(message.empty())
            out << "No message" << "\n";
        else
            out << "Message: " << message << "\n";
        out.close();  
    }
};