#pragma once
#ifndef NUKEE_MESH_H
#define NUKEE_MESH_H
#include <assimp/mesh.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

class Mesh 
{
    float *vertexArray;
    float *normalArray;
    float *uvArray;

    int numVerts;

public:
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
    }

    void Render(){
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
    }
};
#endif // !NUKEE_MESH_H
