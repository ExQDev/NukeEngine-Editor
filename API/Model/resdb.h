#ifndef RESDB_H
#define RESDB_H
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Shader.h"
#include <boost/container/list.hpp>

namespace bc = boost::container;

class ResDB
{
    ResDB() {}
    ~ResDB() {}
public:
    bc::list<Mesh*> meshes;
    bc::list<Texture*> textures;
    bc::list<Material*> materials;
    bc::list<Shader*> shaders;

    static ResDB* getSingleton(){
        static ResDB instance;
        return &instance;
    }
};
#endif // RESDB_H
