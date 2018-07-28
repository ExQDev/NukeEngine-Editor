#ifndef MOUSE_H
#define MOUSE_H
#include <boost/container/list.hpp>
#include <boost/function.hpp>

using namespace boost::container;
namespace b = boost;

class Mouse
{
    friend class NukeOGL;

private:
    Mouse() {}
    ~Mouse(){}

    list<b::function<void(unsigned char c, int x, int y)>> _onKey;

    void key(unsigned char c, int x, int y)
    {
        for(auto f : _onKey)
        {
            f(c, x, y);
        }
    }

public:
    static Mouse *getSingleton()
    {
        static Mouse instance;
        return &instance;
    }

    Mouse* operator+=(b::function<void(unsigned char c, int x, int y)> onKey)
    {
        _onKey.push_back(onKey);
    }
};
#endif // MOUSE_H
