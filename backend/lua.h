#ifndef LUA_H
#define LUA_H
#include <lua.hpp>
#include <boost/filesystem.hpp>
#include <deps/LuaBridge/Source/LuaBridge/LuaBridge.h>
#include <iostream>

namespace b = boost;
namespace bfs = boost::filesystem;
namespace lb = luabridge;
using namespace std;

class Lua
{
private:
    Lua() {
        l = luaL_newstate();
        bfs::path plugdir("plugins");
        bfs::path plugins("plugins/lua");
        bfs::path main("plugins/lua/main.lua");
        if(!bfs::exists(plugdir))
            bfs::create_directory(plugdir);
        if(!bfs::exists(plugins))
            bfs::create_directory(plugins);
        if(!bfs::exists(main))
        {
            cout << "Main lua plugin is not detected. Skipping lua initialization." << endl;
        }
        else
        {
            cout << "Main lua plugin detected. Loading..." << endl;
            doFile(main.c_str());
        }
    }
    ~Lua() {}

public:
    lua_State* l;

    static Lua* getSingleton(){
        static Lua instance;
        return &instance;
    }

    lua_State* getState(){
        return l;
    }

    void doFile(const char* path){
        luaL_dofile(l, path);
    }

    void doStr(const char* str){
        luaL_dostring(l, str);
    }

    lb::LuaRef getGlobal(const char * var){
        lb::getGlobal(l, var);
    }
};
#endif // LUA_H
