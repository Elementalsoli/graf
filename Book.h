#ifndef BOOK_H
#define BOOK_H

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"

class Book {
public:
    VAO vaoCover, vaoPages;
    VBO vboCover, vboPages;
    EBO eboCover, eboPages;

    Book();
    void Draw(Shader& shader);
    void Delete();
};

#endif
