#include "Desk.h"

// Blat sto�u
GLfloat deskVertices[] = {
    -2.0f, -0.6f,  2.0f,   0.8f, 0.5f, 0.3f,  0,0,
    -2.0f, -0.6f, -2.0f,   0.8f, 0.5f, 0.3f,  0,1,
     2.0f, -0.6f, -2.0f,   0.8f, 0.5f, 0.3f,  1,1,
     2.0f, -0.6f,  2.0f,   0.8f, 0.5f, 0.3f,  1,0,
    -2.0f, -0.7f,  2.0f,   0.8f, 0.5f, 0.3f,  0,0,
    -2.0f, -0.7f, -2.0f,   0.8f, 0.5f, 0.3f,  0,1,
     2.0f, -0.7f, -2.0f,   0.8f, 0.5f, 0.3f,  1,1,
     2.0f, -0.7f,  2.0f,   0.8f, 0.5f, 0.3f,  1,0
};
GLuint deskIndices[] = { 0,1,2, 0,2,3, 4,5,6, 4,6,7, 0,1,5, 0,5,4, 1,2,6, 1,6,5, 2,3,7, 2,7,6, 3,0,4, 3,4,7 };

// Nogi sto�u (4 s�upki w rogach)
GLfloat legVertices[] = {
    // Prawy prz�d � dwukrotnie szerszy i d�u�szy
    2.0f, -0.7f,  2.0f,   0.5f,0.3f,0.1f, 0,0,
    1.6f, -0.7f,  2.0f,   0.5f,0.3f,0.1f, 0,1,
    1.6f, -2.7f,  2.0f,   0.5f,0.3f,0.1f, 1,1,
    2.0f, -2.7f,  2.0f,   0.5f,0.3f,0.1f, 1,0,

    // Prawy ty�
    2.0f, -0.7f, -2.0f,   0.5f,0.3f,0.1f, 0,0,
    1.6f, -0.7f, -2.0f,   0.5f,0.3f,0.1f, 0,1,
    1.6f, -2.7f, -2.0f,   0.5f,0.3f,0.1f, 1,1,
    2.0f, -2.7f, -2.0f,   0.5f,0.3f,0.1f, 1,0,

    // Lewy prz�d
   -1.6f, -0.7f,  2.0f,   0.5f,0.3f,0.1f, 0,0,
   -2.0f, -0.7f,  2.0f,   0.5f,0.3f,0.1f, 0,1,
   -2.0f, -2.7f,  2.0f,   0.5f,0.3f,0.1f, 1,1,
   -1.6f, -2.7f,  2.0f,   0.5f,0.3f,0.1f, 1,0,

   // Lewy ty�
  -1.6f, -0.7f, -2.0f,   0.5f,0.3f,0.1f, 0,0,
  -2.0f, -0.7f, -2.0f,   0.5f,0.3f,0.1f, 0,1,
  -2.0f, -2.7f, -2.0f,   0.5f,0.3f,0.1f, 1,1,
  -1.6f, -2.7f, -2.0f,   0.5f,0.3f,0.1f, 1,0
};
GLuint legIndices[] = {
    0,1,2, 0,2,3, 4,5,6, 4,6,7, 8,9,10, 8,10,11, 12,13,14, 12,14,15
};

Desk::Desk() {
    vaoTop.Bind();
    vboTop = VBO(deskVertices, sizeof(deskVertices));
    eboTop = EBO(deskIndices, sizeof(deskIndices));
    vaoTop.LinkAttrib(vboTop, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vaoTop.LinkAttrib(vboTop, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoTop.LinkAttrib(vboTop, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vaoTop.Unbind(); vboTop.Unbind(); eboTop.Unbind();

    vaoLegs.Bind();
    vboLegs = VBO(legVertices, sizeof(legVertices));
    eboLegs = EBO(legIndices, sizeof(legIndices));
    vaoLegs.LinkAttrib(vboLegs, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vaoLegs.LinkAttrib(vboLegs, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vaoLegs.LinkAttrib(vboLegs, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vaoLegs.Unbind(); vboLegs.Unbind(); eboLegs.Unbind();
}

void Desk::Draw(Shader& shader) {
    vaoTop.Bind();
    shader.SetMat4("model", glm::mat4(1.0f));
    glDrawElements(GL_TRIANGLES, sizeof(deskIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

    vaoLegs.Bind();
    shader.SetMat4("model", glm::mat4(1.0f));
    glDrawElements(GL_TRIANGLES, sizeof(legIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}

void Desk::Delete() {
    vaoTop.Delete(); vboTop.Delete(); eboTop.Delete();
    vaoLegs.Delete(); vboLegs.Delete(); eboLegs.Delete();
}
