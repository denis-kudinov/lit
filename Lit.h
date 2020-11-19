#include "Command.h"
#include "Commit.h"
#include "Exception.h"
#include "Graph.h"
#include <experimental/filesystem>
#include <iostream>
#include <limits.h>
#include <map>
#include <memory>
#include <unistd.h>
#include <vector>

namespace fs = std::experimental::filesystem;

class Lit {
public:
  Lit(const std::vector<std::string> &argv)
      : currentCommitId(-1), commitHistory(nullptr) {
    std::cout << "кек1"
              << "\n";
    if (!CheckRepo()) {
      std::cout << fs::current_path().string() << std::endl;
      if (argv[1] == "init") {
        if (!init()) {
          std::cout << "Couldn't init the repository "
                    << fs::current_path().string() << std::endl;
          return;
        }
      } else {
        std::cout << "Not a lit repository. Use 'lit init' to initialize the "
                     "repository."
                  << std::endl;
        return;
      }
    }

    std::cout << "кек2"
              << "\n";

    ReadData();

    std::cout << "кек3"
              << "\n";

    if (argv[1] == "help") {
      std::cout << "Implemented commands:"
                << "\n";
      std::cout
          << "lit init - initialize a repository"
          << "\n"
          << "lit commit - create a new commit containing all changes"
          << "\n"
          << "lit show - this sub-command is used to inspect the given commit"
          << "\n"
          << "lit checkout - this resets the state of all files to the given "
             "commit's state"
          << "\n";
    } else if (argv[1] == "show") {
      if (argv.size() > 3) {
        std::cout << "Wrong usage. Should be 'lit show [rN].'\n";
        return;
      } else if (argv.size() == 2)
        show();
      else
        show(argv[2]);
    } else if (argv[1] == "commit") {
      if (argv.size() == 2)
        commit();
      else {
        std::string message = "";
        for (int i = 2; i < argv.size(); i++)
          message += argv[i];
        commit(message);
      }

    } else if (argv[1] == "checkout") {
      std::cout << "кек4"
                << "\n";

      if (argv.size() > 3) {
        std::cout << "Wrong usage. Should be 'lit checkout [rN].'\n";
        return;
      } else if (argv.size() == 2)
        checkout();
      else
        checkout(argv[2]);
    }
  }

private:
  std::shared_ptr<Graph> commitHistory; //удалить нах

  int currentCommitId;

  std::map<int, int> parents;

  bool CheckRepo() {
    const fs::path workdir = fs::current_path();
    const fs::path litPath = workdir / ".lit";
    if (!fs::exists(litPath))
      return false;
    return true;
  }

  void ReadData() {
    std::cout << "кринж1"
              << "\n";

    if (fs::exists(".lit/commits/current.txt")) {
      std::ifstream in(".lit/commits/current.txt");
      in >> currentCommitId;
      in.close();
    }

    std::cout << "кринж2"
              << "\n";

    if (fs::exists(".lit/commits/parents.txt")) {
      std::ifstream in(".lit/commits/parents.txt");
      std::string str;
      int row = 0;
      while (std::getline(in, str)) {
        std::istringstream ss(str);
        int commit, parent;
        ss >> commit >> parent;
        parents[commit] = parent;
      }
      in.close();
    }

    std::cout << "кринж3"
              << "\n";

    if (fs::exists(".lit/graph.txt")) {
      commitHistory = std::make_shared<Graph>();
      commitHistory->ReadGraph();
    }
    std::cout << "кринж4"
              << "\n";
  }

  bool init() {
    if (!fs::create_directories(".lit")) {
      std::cout << ".lit directory cannot be created" << std::endl;
      return false;
    }

    fs::create_directories(".lit/initial_copy");

    const fs::path workdir = fs::current_path();

    Command cmd;
    cmd.Command = "rsync -a --exclude '.lit' " + workdir.string() +
                  "/* .lit/initial_copy/";
    cmd.execute();

    fs::create_directories(".lit/commits");
    return true;
  }

  void commit(std::string message = "") {
    int numberOfCommits;
    if (!fs::exists(".lit/commits/number.txt"))
      numberOfCommits = 0;
    else {
      std::ifstream in(".lit/commits/number.txt");
      in >> numberOfCommits;
      in.close();
    }

    auto commit =
        std::make_shared<Commit>(message, numberOfCommits, currentCommitId);

    parents[commit->id_int] = currentCommitId;
    int currentCommitId_old = currentCommitId;
    currentCommitId = commit->id_int;

    if (!PutDiff())
      return;

    if (!commitHistory)
      commitHistory = std::make_shared<Graph>();
    if (currentCommitId_old != -1)
      commitHistory->AddNode(currentCommitId_old, currentCommitId);

    std::ofstream out(".lit/commits/number.txt");
    out << ++numberOfCommits;
    out.close();

    std::ofstream out1(".lit/commits/parents.txt");
    for (auto &&i : parents) {
      out1 << i.first << " " << i.second << "\n";
    }
    out1.close();

    std::ofstream out2(".lit/commits/current.txt");
    out2 << currentCommitId;
    out2.close();
  }

  bool PutDiff() {
    const fs::path workdir = fs::current_path();
    if (currentCommitId == 0) {
      Command cmd;
      std::string c = "diff -ruN --exclude=.lit " + workdir.string() + " " +
                      workdir.string() + "/.lit/initial_copy/ > " +
                      workdir.string() + "/.lit/commits/0/0-1.patch";
      std::cout << c << std::endl;
      cmd.Command = c;
      cmd.execute();

      c = "diff -ruN --exclude=.lit " + workdir.string() +
          "/.lit/initial_copy/" + " " + workdir.string() + " > " +
          workdir.string() + "/.lit/commits/0/-10.patch";
      std::cout << c << std::endl;
      cmd.Command = c;
      cmd.execute();

      std::string patchfile = workdir.string() + "/.lit/commits/0/-10.patch";

      if (fs::is_empty(patchfile)) {
        std::cout << "Cannot commit: no changes were made.\n";
        RevertCommit();
        return false;
      }

      return true;
    }

    std::vector<int> path;
    int parent = parents[currentCommitId];

    while (parent != -1) {
      path.push_back(parent);
      parent = parents[parent];
    }
    path.push_back(-1);

    Command cmd;
    for (int i = path.size() - 2; i >= 0; --i) {
      std::string c =
          "patch -d " + workdir.string() + "/.lit/initial_copy -s < " +
          workdir.string() + "/.lit/commits/" + std::to_string(path[i]) + "/" +
          std::to_string(path[i + 1]) + std::to_string(path[i]) + ".patch";
      cmd.Command = c;
      std::cout << c << std::endl;
      cmd.execute();
    }

    std::string c =
        "diff -ruN --exclude=.lit " + workdir.string() + " " +
        workdir.string() + "/.lit/initial_copy/ > " + workdir.string() +
        "/.lit/commits/" + std::to_string(currentCommitId) + "/" +
        std::to_string(currentCommitId) + std::to_string(path[0]) + ".patch";
    cmd.Command = c;
    std::cout << c << std::endl;
    cmd.execute();
    c = "diff -ruN --exclude=.lit " + workdir.string() + "/.lit/initial_copy/" +
        " " + workdir.string() + " > " + workdir.string() + "/.lit/commits/" +
        std::to_string(currentCommitId) + "/" + std::to_string(path[0]) +
        std::to_string(currentCommitId) + ".patch"; // TODO
    cmd.Command = c;
    std::cout << c << std::endl;
    cmd.execute();

    for (int i = 0; i < path.size() - 1; ++i) {
      c = "patch -d " + workdir.string() + "/.lit/initial_copy -s < " +
          workdir.string() + "/.lit/commits/" + std::to_string(path[i]) + "/" +
          std::to_string(path[i]) + std::to_string(path[i + 1]) + ".patch";
      cmd.Command = c;
      std::cout << c << std::endl;
      cmd.execute();
    }

    std::string patchfile = workdir.string() + "/.lit/commits/" +
                            std::to_string(currentCommitId) + "/" +
                            std::to_string(path[0]) +
                            std::to_string(currentCommitId) + ".patch";

    if (fs::is_empty(patchfile)) {
      std::cout << "Cannot commit: no changes were made.\n";
      RevertCommit();
      return false;
    }
    return true;
  }

  void RevertCommit() {
    fs::remove_all(".lit/commits/" + std::to_string(currentCommitId) + "/");
    currentCommitId = parents[currentCommitId];
  }

  void show(std::string commitId = "") {
    if (commitId.empty())
      commitId = std::to_string(currentCommitId);
    else {
      commitId.erase(commitId.begin() + 0);
      auto it = parents.find(atoi(commitId.c_str()));
      if (it == parents.end()) {
        std::cout << "No such commit.\n";
        return;
      }
    }

    std::ifstream in(".lit/commits/" + commitId + "/info.txt");
    std::string s;
    while (getline(in, s)) {
      std::cout << s << std::endl;
    }
    in.close();

    int p = parents[atoi(commitId.c_str())];
    in.open(".lit/commits/" + commitId + "/" + std::to_string(p) + commitId +
            ".patch");
    while (getline(in, s)) {
      std::cout << s << std::endl;
    }
    in.close();
  }

  void checkout(std::string commitId = "") {
    std::cout << "лол1"
              << "\n";
    if (commitId.empty())
      commitId = std::to_string(currentCommitId);
    else {
      std::cout << "лол2"
                << "\n";
      commitId.erase(commitId.begin() + 0);
      auto it = parents.find(atoi(commitId.c_str()));
      if (it == parents.end()) {
        std::cout << "No such commit.\n";
        return;
      }
    }
    std::cout << "лол3"
              << "\n";

    currentCommitId = atoi(commitId.c_str());

    const fs::path workdir = fs::current_path();

    std::cout << "лол4"
              << "\n";

    std::vector<std::string> filesToRemove;
    for (auto &file : fs::directory_iterator(workdir)) {
      if (file.path().string() != workdir.string() + "/.lit") {
        filesToRemove.push_back(file.path().string());
      }
    }

    std::cout << "лол5"
              << "\n";

    for (auto i : filesToRemove) {
      fs::remove_all(i);
    }

    std::cout << "лол6"
              << "\n";

    fs::copy(workdir.string() + "/.lit/initial_copy", workdir.string(),
             fs::copy_options::recursive);

    std::vector<int> path;

    int parent = parents[currentCommitId];

    std::cout << "лол7"
              << "\n";

    path.push_back(currentCommitId);

    while (parent != -1) {
      path.push_back(parent);
      parent = parents[parent];
    }
    path.push_back(-1);

    std::cout << "лол8"
              << "\n";

    Command cmd;
    for (int i = path.size() - 2; i >= 0; --i) {
      cmd.Command =
          "patch -d " + workdir.string() + " -s < " + workdir.string() +
          "/.lit/commits/" + std::to_string(path[i]) + "/" +
          std::to_string(path[i + 1]) + std::to_string(path[i]) + ".patch";
      cmd.execute();
    }

    std::cout << "лол9"
              << "\n";

    std::ofstream out2(".lit/commits/current.txt");
    out2 << currentCommitId;
    out2.close();
    std::cout << "лол10"
              << "\n";
  }
};