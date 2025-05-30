#ifndef MONITOR_H
#define MONITOR_H

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"

class Monitor {
public:
    VAO vaoScreen, vaoBase;
    VBO vboScreen, vboBase;
    EBO eboScreen, eboBase;

    Monitor();
    void Draw(Shader& shader);
    void Delete();
};

#endif
