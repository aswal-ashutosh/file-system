#include <iostream>
#include <vector>
#include <set>
#include <map>

constexpr char branch = 192, dash = 196, endline = '\n';

class FileSystem {
    struct Directory {
        const std::string name;
        std::map<std::string, Directory*> content;
    };

    Directory* rootDirectory;

    static std::vector<std::string> parsePath(const std::string& path) {
        std::vector<std::string> parsedPath;
        std::string current;
        for (const char c : path) {
            if (c == '/') {
                parsedPath.push_back(current);
                current.clear();
            } else {
                current += c;
            }
        }
        if (!current.empty()) {
            parsedPath.push_back(current);
        }
        return parsedPath;
    }

    static void print(const Directory* directory, const int depth = 0) {
        std::cout << directory->name << endline;
        for (const auto& [_, directory] : directory->content) {
            std::cout << std::string(depth * 2, ' ') << branch << dash;
            FileSystem::print(directory, depth + 1);
        }
    }

    FileSystem() : rootDirectory(new Directory { "Root" })  {
    }


public:
    static FileSystem* instance;

    static FileSystem* getInstance() {
        if (FileSystem::instance == nullptr) {
            FileSystem::instance = new FileSystem();
        }
        return FileSystem::instance;
    }

    void add(const std::string& path) {
        const std::vector<std::string> parsedPath = FileSystem::parsePath(path.substr(1));
        Directory* curr = rootDirectory;
        for (const std::string directoryName : parsedPath) {
            auto it = curr->content.find(directoryName);
            if (it != curr->content.end()) {
                curr = it->second;
            } else {
                curr = curr->content[directoryName] = new Directory{ directoryName };
            }
        }
    }

    void print() {
        FileSystem::print(rootDirectory);
    }

};

FileSystem* FileSystem::instance = nullptr;

int main() {
    FileSystem* fileSystem = FileSystem::getInstance();
    fileSystem->add("/Desktop");
    fileSystem->add("/Desktop/My Games");
    fileSystem->add("/Desktop/My Games/game1.exe");
    fileSystem->add("/Desktop/My Games/game2.exe");
    fileSystem->add("/Desktop/My Games/Mini Games/game1.exe");
    fileSystem->add("/Desktop/My Games/Mini Games/Ultra Mini Games/game1.exe");
    fileSystem->add("/Desktop/My Games/Mini Games/Ultra Mini Games/game2.exe");
    fileSystem->add("/Desktop/Videos/video1.mp4");
    fileSystem->add("/Desktop/Videos/video2.mp4");
    fileSystem->print();
    return 0;
}