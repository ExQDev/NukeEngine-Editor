#pragma once
#ifndef NUKEE_MESH_H
#define NUKEE_MESH_H
#include "Transform.h"
#include "Material.h"
#include <assimp/mesh.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <boost/container/list.hpp>

namespace bc = boost::container;

class Mesh 
{
    float *vertexArray;
    float *normalArray;
    float *uvArray;

    int numVerts;

    bc::list<Mesh*> children;

public:
    const char *name;

    Mesh(){
        children.clear();
    }

    void ImportAIMesh(aiMesh* mesh){
        numVerts = mesh->mNumFaces*3;

        vertexArray = new float[mesh->mNumFaces*3*3];
        normalArray = new float[mesh->mNumFaces*3*3];
        uvArray     = new float[mesh->mNumFaces*3*2];

        for(unsigned int i=0;i<mesh->mNumFaces;i++)
        {
            const aiFace& face = mesh->mFaces[i];

            for(int j=0;j<3;j++)
            {
                aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[j]];
                memcpy(uvArray,&uv,sizeof(float)*2);
                uvArray+=2;

                aiVector3D normal = mesh->mNormals[face.mIndices[j]];
                memcpy(normalArray,&normal,sizeof(float)*3);
                normalArray+=3;

                aiVector3D pos = mesh->mVertices[face.mIndices[j]];
                memcpy(vertexArray,&pos,sizeof(float)*3);
                vertexArray+=3;
            }
        }

        uvArray-=mesh->mNumFaces*3*2;
        normalArray-=mesh->mNumFaces*3*3;
        vertexArray-=mesh->mNumFaces*3*3;
        const char* __name = mesh->mName.C_Str();
        //strcpy(name, __name);
        name = __name;
    }

    void Render(Material *mat, Transform* tr){
        //cout << "DIFF CNT: " << mat->aiMat->GetTextureCount(aiTextureType_DIFFUSE) << endl;;
        //aiString texPath;
        //mat->aiMat->GetTexture(aiTextureType_DIFFUSE, 0, &texPath);
        //cout << "DIFF P: " << texPath.C_Str() << endl;
        glEnable(GL_COLOR_MATERIAL);
        glEnable (GL_LIGHTING);
        glEnable (GL_LIGHT0);

        Vector3 pos = tr->globalPosition();
        Vector3 rot = tr->globalRotation();
        Vector3 scale = tr->globalScale();

        glTranslated(pos.x, pos.y, pos.z);
        glRotatef(rot.x, 1.0, 0.0, 0.0);
        glRotatef(rot.y, 0.0, 1.0, 0.0);
        glRotatef(rot.z, 0.0, 0.0, 1.0);
        glScaled(scale.x, scale.y, scale.z);


        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3,GL_FLOAT,0,vertexArray);
        glNormalPointer(GL_FLOAT,0,normalArray);

        glClientActiveTexture(GL_TEXTURE0_ARB);
        glTexCoordPointer(2,GL_FLOAT,0,uvArray);

        glDrawArrays(GL_TRIANGLES,0,numVerts);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        glTranslated(-pos.x, -pos.y, -pos.z);
        glRotated(-rot.x, 1.0, 0.0, 0.0);
        glRotated(-rot.y, 0.0, 1.0, 0.0);
        glRotated(-rot.z, 0.0, 0.0, 1.0);
        glScaled(1/scale.x, 1/scale.y, 1/scale.z);

    }
};
#endif // !NUKEE_MESH_H
