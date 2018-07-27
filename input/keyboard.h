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

    void key(unsigned char c, int x, int y)
    {
        for(auto f : _onKey)
        {
            f(c, x, y);
        }
    }
public:

    static KeyBoard* getSigleton()
    {
        static KeyBoard instance;
        return &instance;
    }



    KeyBoard operator+=(b::function<void(unsigned char c, int x, int y)> onKey)
    {
        _onKey.push_back(onKey);
    }
};
#endif // KEYBOARD_H
