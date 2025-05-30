//#ifndef CAN_H
//#define CAN_H
//
//#include "VAO.h"
//#include "VBO.h"
//#include "EBO.h"
//#include "shaderClass.h"
//#include <vector>
//class Can {
//public:
//    VAO vao;
//    VBO vbo;
//    EBO ebo;
//    std::vector<float> vertices;
//    std::vector<unsigned int> indices;
//
//    Can(float radius, float height, unsigned int sectorCount);
//    void Draw(Shader& shader);
//    void Delete();
//};

//#endif

#ifndef CAN_H
#define CAN_H

#include <vector>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"

class Can {
public:
    VAO vaoSide, vaoTop;
    VBO vboSide, vboTop;
    EBO eboSide, eboTop;

    std::vector<float> sideVertices;
    std::vector<unsigned int> sideIndices;
    std::vector<float> topVertices;
    std::vector<unsigned int> topIndices;

    Can(float radius, float height, unsigned int sectorCount);
    void DrawSide(Shader& shader);
    void DrawTop(Shader& shader);
    void Delete();
};

#endif

