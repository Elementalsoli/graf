#include "Monitor.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Prostok¹tny ekran (monitor)
GLfloat screenVertices[] = {
    -0.5f,  0.5f, 0.0f,  1,1,1,  0,0,
    -0.5f, -0.5f, 0.0f,  1,1,1,  0,1,
     0.5f, -0.5f, 0.0f,  1,1,1,  1,1,
     0.5f,  0.5f, 0.0f,  1,1,1,  1,0
};
GLuint screenIndices[] = { 0,1,2, 0,2,3 };

// Podstawa (nó¿ka) monitora
GLfloat baseVertices[] = {
    -0.05f, -0.5f,  0.0f,  0.5f,0.3f,0.1f, 0,0,
     0.05f, -0.5f,  0.0f,  0.5f,0.3f,0.1f, 0,1,
     0.05f, -1.0f,  0.0f,  0.5f,0.3f,0.1f, 1,1,
    -0.05f, -1.0f,  0.0f,  0.5f,0.3f,0.1f, 1,0
};
GLuint baseIndices[] = { 0,1,2, 0,2,3 };

Monitor::Monitor() {
    vaoScreen.Bind();
    vboScreen = VBO(screenVertices, sizeof(screenVertices));
    eboScreen = EBO(screenIndices, sizeof(screenIndices));
    vaoScreen.LinkAttrib(vboScreen, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vaoScreen.LinkAttrib(vboScreen, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoScreen.LinkAttrib(vboScreen, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vaoScreen.Unbind(); vboScreen.Unbind(); eboScreen.Unbind();

    vaoBase.Bind();
    vboBase = VBO(baseVertices, sizeof(baseVertices));
    eboBase = EBO(baseIndices, sizeof(baseIndices));
    vaoBase.LinkAttrib(vboBase, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vaoBase.LinkAttrib(vboBase, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoBase.LinkAttrib(vboBase, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vaoBase.Unbind(); vboBase.Unbind(); eboBase.Unbind();
}

void Monitor::Draw(Shader& shader) {
    // Ekran
    vaoScreen.Bind();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.5f));  // przesuniêcie na biurku
    shader.SetMat4("model", model);
    glDrawElements(GL_TRIANGLES, sizeof(screenIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

    // Nó¿ka
    vaoBase.Bind();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.5f));
    shader.SetMat4("model", model);
    glDrawElements(GL_TRIANGLES, sizeof(baseIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}

void Monitor::Delete() {
    vaoScreen.Delete(); vboScreen.Delete(); eboScreen.Delete();
    vaoBase.Delete(); vboBase.Delete(); eboBase.Delete();
}
