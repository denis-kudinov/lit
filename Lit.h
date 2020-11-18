#include <iostream>
#include <experimental/filesystem>
#include <limits.h>
#include <unistd.h>
#include <vector>
//#include <map>
#include "Exception.h"
#include "Graph.h"
#include "Command.h"
#include "Commit.h"
#include <memory>

namespace fs = std::experimental::filesystem;

class Lit
{
public:
    Lit(const std::vector<std::string>& argv)
    : commitHistory(nullptr)
    {
        if(!CheckRepo())
        {
            if(argv[1] == "init")
            {
                if (!init())
                {
                    std::cout << "Couldn't init the repo " << fs::current_path().string() << std::endl;
                    return;
                }
            }
            else 
            {
                std::cout << "Not a lit repository. Use 'lit init' to initialize the repository." << std::endl;
                //throw Exception("Not a lit repository. Use 'lit init' to initialize the repository.");
                return;
            }
        }

        //TODO прочитать граф из хранилища??
        //посмотреть current commit

        if (argv[1] == "help")
        {
            
        } 
        else if(argv[1] == "status")
        {

        }
        else if(argv[1] == "commit")
        {
            //commit(argv[]);
        }
    }

private:

    std::shared_ptr<Graph> commitHistory;

    //std::map<std::string, std::shared_ptr<Commit>> commits;

    std::shared_ptr<Commit> currentCommit;

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
            std::cout << ".lit directory cannot be created" << std::endl;
            return false;
        }

        //std::cout << "init lol" << std::endl; TODO

        fs::create_directories(".lit/initial_copy");



        const fs::path workdir = fs::current_path();
        
        Command cmd;
        cmd.Command = "rsync -a --exclude '.lit' " + workdir.string() + "/* .lit/initial_copy/";
        cmd.execute();

        fs::create_directories(".lit/commits");
        return true;
    }

    bool commit (std::string message = "")
    {
        std::shared_ptr<Commit> commit;
        if (fs::is_empty(".lit/commits"))
        {
            commit = std::make_shared<Commit>(message, nullptr);
            commitHistory = std::make_shared<Graph>();

        }
        else 
        {
            commit = std::make_shared<Commit>(message, currentCommit);
            commitHistory->AddNode(currentCommit->currentId_int, commit->currentId_int);
        }
             
        currentCommit = commit;

        //добавить граф в хранилище

        //создать дифф 
        //сохранить его в папку
    }
    
};