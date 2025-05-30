#include "Book.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Ok³adka – prostok¹t, grubszy, lekko rozchylony
GLfloat coverVertices[] = {
    -1.2f,  0.0f,  0.9f,  0.6f,0.2f,0.1f, 0,0,  // Górna
    -1.2f,  0.0f, -0.9f,  0.6f,0.2f,0.1f, 0,1,
     1.2f,  0.2f, -0.9f,  0.6f,0.2f,0.1f, 1,1,
     1.2f,  0.2f,  0.9f,  0.6f,0.2f,0.1f, 1,0,

    -1.2f, -0.1f,  0.9f,  0.6f,0.2f,0.1f, 0,0,  // Dolna
    -1.2f, -0.1f, -0.9f,  0.6f,0.2f,0.1f, 0,1,
     1.2f, -0.1f, -0.9f,  0.6f,0.2f,0.1f, 1,1,
     1.2f, -0.1f,  0.9f,  0.6f,0.2f,0.1f, 1,0
};
GLuint coverIndices[] = { 0,1,2, 0,2,3, 4,5,6, 4,6,7, 0,1,5, 0,5,4, 1,2,6, 1,6,5, 2,3,7, 2,7,6, 3,0,4, 3,4,7 };

// Œrodek ksi¹¿ki – cieñszy, delikatnie przesuniêty do œrodka
GLfloat pagesVertices[] = {
    -1.0f, -0.08f,  0.7f,  0.95f,0.9f,0.85f, 0,0,  // Górna
    -1.0f, -0.08f, -0.7f,  0.95f,0.9f,0.85f, 0,1,
     1.0f,  0.15f, -0.7f,  0.95f,0.9f,0.85f, 1,1,
     1.0f,  0.15f,  0.7f,  0.95f,0.9f,0.85f, 1,0,

    -1.0f, -0.1f,  0.7f,  0.95f,0.9f,0.85f, 0,0,  // Dolna
    -1.0f, -0.1f, -0.7f,  0.95f,0.9f,0.85f, 0,1,
     1.0f, -0.1f, -0.7f,  0.95f,0.9f,0.85f, 1,1,
     1.0f, -0.1f,  0.7f,  0.95f,0.9f,0.85f, 1,0
};
GLuint pagesIndices[] = { 0,1,2, 0,2,3, 4,5,6, 4,6,7, 0,1,5, 0,5,4, 1,2,6, 1,6,5, 2,3,7, 2,7,6, 3,0,4, 3,4,7 };



// Ok³adka – szersza, grubsza, zaokr¹glona

// Papier – wê¿szy, cieñszy, z wciêciem



Book::Book() {
    vaoCover.Bind();
    vboCover = VBO(coverVertices, sizeof(coverVertices));
    eboCover = EBO(coverIndices, sizeof(coverIndices));
    vaoCover.LinkAttrib(vboCover, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vaoCover.LinkAttrib(vboCover, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoCover.LinkAttrib(vboCover, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vaoCover.Unbind(); vboCover.Unbind(); eboCover.Unbind();

    vaoPages.Bind();
    vboPages = VBO(pagesVertices, sizeof(pagesVertices));
    eboPages = EBO(pagesIndices, sizeof(pagesIndices));
    vaoPages.LinkAttrib(vboPages, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vaoPages.LinkAttrib(vboPages, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoPages.LinkAttrib(vboPages, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vaoPages.Unbind(); vboPages.Unbind(); eboPages.Unbind();
}

void Book::Draw(Shader& shader) {
    vaoCover.Bind();
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, -1.0f));
    shader.SetMat4("model", model);
    glDrawElements(GL_TRIANGLES, sizeof(coverIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

    vaoPages.Bind();
    model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, -1.0f));
    shader.SetMat4("model", model);
    glDrawElements(GL_TRIANGLES, sizeof(pagesIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}

void Book::Delete() {
    vaoCover.Delete(); vboCover.Delete(); eboCover.Delete();
    vaoPages.Delete(); vboPages.Delete(); eboPages.Delete();
}
