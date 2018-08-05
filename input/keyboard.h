#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <boost/container/list.hpp>
#include <boost/function.hpp>

using namespace boost::container;
namespace b = boost;

class KeyBoard
{
    friend class NukeOGL;
private:
    KeyBoard() {}
    ~KeyBoard(){}

    list<b::function<void(unsigned char c, int x, int y)>> _onKey;
    list<b::function<void(int key, int x, int y)>> _onSpecialKey;
    list<b::function<void(unsigned char c, int x, int y)>> _onKeyUp;
    list<b::function<void(int key, int x, int y)>> _onSpecialKeyUp;
    bool* keyStates = new bool[256];

    void key(unsigned char c, int x, int y)
    {
        keyStates[c] = true;
        for(auto f : _onKey)
        {
            f(c, x, y);
        }
    }

    void special(int key, int x, int y)
    {
        for(auto f : _onSpecialKey)
        {
            f(key, x, y);
        }
    }

    void keyup(unsigned char c, int x, int y)
    {
        keyStates[c] = false;
        for(auto f : _onKeyUp)
        {
            f(c, x, y);
        }
    }

    void specialup(int key, int x, int y)
    {
        for(auto f : _onSpecialKeyUp)
        {
            f(key, x, y);
        }
    }
public:

    static KeyBoard* getSingleton()
    {
        static KeyBoard instance;
        return &instance;
    }

    bool getKeyPressed(unsigned char c){
        return keyStates[c];
    }

    KeyBoard* operator+=(b::function<void(unsigned char c, int x, int y)> onKey)
    {
        _onKey.push_back(onKey);
        return this;
    }

    KeyBoard* operator*=(b::function<void(int key, int x, int y)> onSpecialKey)
    {
        _onSpecialKey.push_back(onSpecialKey);
        return this;
    }

    KeyBoard* operator&=(b::function<void(unsigned char c, int x, int y)> onKeyUp)
    {
        _onKeyUp.push_back(onKeyUp);
        return this;
    }

    KeyBoard* operator|=(b::function<void(int key, int x, int y)> onSpecialKeyUp)
    {
        _onSpecialKeyUp.push_back(onSpecialKeyUp);
        return this;
    }
};
#endif // KEYBOARD_H
