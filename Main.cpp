#include <filesystem>
namespace fs = std::filesystem;

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
#include "Sphere.h"
#include "Stand.h"
#include "Desk.h"
#include "can.h"
#include "Monitor.h"
#include "Book.h"

const unsigned int width = 800;
const unsigned int height = 800;

int main()
{
    // Inicjalizacja GLFW i ustawienia OpenGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Globe Scene", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    // Shader
    Shader shaderProgram("default.vert", "default.frag");
    Shader lightShader("light.vert", "light.frag");

    // Obiekty
    Sphere sphere(0.5f, 36, 18);
    Stand stand;
    Desk desk;
    Can can(0.15f, 0.7f, 144);
    Book book;
    //Monitor monitor;
    

    // Tekstury
    Texture sphereTex("ziemia.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture woodTex("wood.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture deskTex("desk.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture canTex("redbull.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    canTex.texUnit(shaderProgram, "tex0", 0);
    Texture upside("zawleczka.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
   /* Texture monitorTex("xp.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    monitorTex.texUnit(shaderProgram, "tex0", 0);*/
    Texture coverTex("ksiazka.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    coverTex.texUnit(shaderProgram, "tex0", 0);

    Texture pageTex("papier.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    pageTex.texUnit(shaderProgram, "tex0", 0);
    
    // Kamera
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 3.0f));
    // Light (œwiat³o)
    GLfloat lightVertices[] = {
        -0.1f,-0.1f,-0.1f,  0.1f,-0.1f,-0.1f,  0.1f, 0.1f,-0.1f, -0.1f, 0.1f,-0.1f,
        -0.1f,-0.1f, 0.1f,  0.1f,-0.1f, 0.1f,  0.1f, 0.1f, 0.1f, -0.1f, 0.1f, 0.1f
    };
    GLuint lightIndices[] = {
        0,1,2, 0,2,3, 4,5,6, 4,6,7, 0,1,5, 0,5,4, 1,2,6, 1,6,5, 2,3,7, 2,7,6, 3,0,4, 3,4,7
    };
    VAO lightVAO; lightVAO.Bind();
    VBO lightVBO(lightVertices, sizeof(lightVertices));
    EBO lightEBO(lightIndices, sizeof(lightIndices));
    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    lightVAO.Unbind(); lightVBO.Unbind(); lightEBO.Unbind();

    glm::vec4 lightColor = glm::vec4(1, 1, 1, 1);
    glm::vec3 lightPos = glm::vec3(1.5f, 1.5f, 1.5f);
    glm::mat4 lightModel = glm::translate(glm::mat4(1.0f), lightPos);
    // Pêtla renderowania
    while (!glfwWindowShouldClose(window))
    {
        // Czyszczenie ekranu
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Aktywacja shadera i ustawienia kamery
        shaderProgram.Activate();
        camera.Inputs(window);
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        // Ustawiamy œwiat³o w shaderze
        shaderProgram.Activate();
        glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);

        // Rysowanie biurka
        deskTex.Bind();
        desk.Draw(shaderProgram);

        // Rysowanie stojaka
        woodTex.Bind();
        stand.Draw(shaderProgram);

        // Rysowanie kuli globusa
        sphereTex.Bind();
        sphere.Draw(shaderProgram);

        // Puszka - bok
        canTex.Bind();
        can.DrawSide(shaderProgram);

        // Puszka - górna pokrywka
        upside.Bind();
        can.DrawTop(shaderProgram);
        
        coverTex.Bind();   // Jeœli chcesz teksturê ok³adki
        book.Draw(shaderProgram);  // Funkcja rysuje ok³adkê i papier raze

    /*    monitorTex.Bind();
        monitor.Draw(shaderProgram);
        */
        // Swap i poll
        lightShader.Activate();
        camera.Matrix(45.0f, 0.1f, 100.0f, lightShader, "camMatrix");
        glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
        glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(window);
        glfwPollEvents();


    }

    // Sprz¹tanie
    sphere.Delete();
    stand.Delete();
    desk.Delete();
    sphereTex.Delete(); woodTex.Delete(); deskTex.Delete();
    shaderProgram.Delete();
    book.Delete();
    coverTex.Delete();
    pageTex.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
