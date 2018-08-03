#ifndef IRENDER_H
#define IRENDER_H
#include <boost/function.hpp>
#include <API/Model/Transform.h>

namespace b = boost;

class iRender
{
    friend class NukeOGL;
private:
    static iRender* _instance;
public:
    static iRender* getSingleton(){
        return _instance;
    }
    Transform* transform;
    int width, height;
    float fov, Far, Near;
    virtual int render() = 0;
    virtual int init(int w, int h) = 0;
    virtual void loop() = 0;
    virtual void deinit() = 0;
    virtual char* getEngine() = 0;
    virtual char* getVersion() = 0;
    virtual void setOnGUI(b::function<void(void)> cb) = 0;
    virtual void setOnRender(b::function<void(void)> cb) = 0;
//    virtual ~iRender() = 0;
};

iRender* iRender::_instance;

#endif // IRENDER_H
