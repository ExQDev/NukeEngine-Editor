#ifndef CONFIG_H
#define CONFIG_H
#include <backend/lua.h>

struct NukeWindow{
    int w, h;
} NukeWindow;

class Config
{
private:
    Config() {
        Lua* lua = Lua::getSingleton();
        bfs::path configDir("config");
        bfs::path config("./config/main.lua");
        if(!bfs::exists(configDir))
            bfs::create_directory(configDir);
        if(!bfs::exists(config))
        {
            cout << "Main config not found, create it please!" << endl;
            return;
        }
        boost::filesystem::recursive_directory_iterator iter(configDir), eod;
        for(auto & p : iter)
        {
            cout << "[config] " << p.path().generic_path().c_str() << endl;
//            ifstream infile { p.path().c_str() };
//            std::string file {  istreambuf_iterator<char>(infile), istreambuf_iterator<char>() };
//            cout << file << endl;
            lua->doFile(p.path().c_str());
        }
        auto w = lb::getGlobal(lua->l, "window");
        if(!w.isNil()){
            window.h = w["height"].cast<int>();
            window.w = w["width"].cast<int>();
        }
    }
    ~Config() {}
public:
    struct NukeWindow window {};
    static Config* getSingleton(){
        static Config instance;
        return &instance;
    }
};
#endif // CONFIG_H
