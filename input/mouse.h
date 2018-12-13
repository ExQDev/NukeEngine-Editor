#ifndef MOUSE_H
#define MOUSE_H
#include <boost/container/list.hpp>
#include <boost/function.hpp>

namespace b = boost;
namespace bc = b::container;

class Mouse
{
    friend class NukeOGL;

private:
    Mouse() {}
    ~Mouse(){}

    bc::list<b::function<void(int button, int state, int x, int y)>> _onKey;
    bc::list<b::function<void(int button, int state, int x, int y)>> _onWheel;
    bc::list<b::function<void(int x, int y)>> _onMove;
    bc::list<b::function<void(int x, int y)>> _onPMove;

    void key(int button, int state, int x, int y)
    {
        for(auto f : _onKey)
        {
            f(button, state, x, y);
        }
    }

    void wheel(int button, int dir, int x, int y)
    {
        for(auto f : _onWheel)
        {
            f(button, dir, x, y);
        }
    }

    void move(int x, int y)
    {
        for(auto f : _onMove)
        {
            f(x, y);
        }
    }

    void pmove(int x, int y)
    {
        for(auto f : _onPMove)
        {
            f(x, y);
        }
    }

public:
    static Mouse *getSingleton()
    {
        static Mouse instance;
        return &instance;
    }

    Mouse* operator+=(b::function<void(int button, int state, int x, int y)> onKey)
    {
        _onKey.push_back(onKey);
    }

    Mouse* operator*=(b::function<void(int button, int dir, int x, int y)> onWheel)
    {
        _onWheel.push_back(onWheel);
    }

    Mouse* operator&=(b::function<void(int x, int y)> onMov)
    {
        _onMove.push_back(onMov);
    }

    Mouse* operator|=(b::function<void(int x, int y)> onPMov)
    {
        _onPMove.push_back(onPMov);
    }
};
#endif // MOUSE_H
