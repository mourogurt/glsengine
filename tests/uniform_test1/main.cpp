#include <iostream>
#include <fstream>
#include <engInit.hpp>
#include <engBuffer.hpp>
#include <engValue.hpp>
#include <engShader.hpp>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

using namespace std;

int main()
{
    EngInit init;
    unsigned win = init.createGLWindow("Example 5",800,600);
    EngGLPlatform* platform = init.getEngGLPlatform(win);
    EngShader shader;
    string src;
    ifstream in("vert.glsl");
    getline(in,src,'\0');
    in.close();
    shader.compileShaderStage(GL_VERTEX_SHADER,src);
    in.open("frag.glsl");
    getline(in,src,'\0');
    in.close();
    shader.compileShaderStage(GL_FRAGMENT_SHADER,src);
    shader.linkShader();
    auto log = shader.getErrLog();
    for (unsigned i = 0; i < log.size(); i++)
        cout << log[i]<<endl;
    if (log.size() > 0) return 1;
    GLuint VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    EngGLUniform uniform1;
    uniform1.setShader(&shader);
    uniform1.bind("MVP");
    //GLuint MatrixID = glGetUniformLocation(program, "MVP");
    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 View       = glm::lookAt(
                                    glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
                                    glm::vec3(0,0,0), // and looks at the origin
                                    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                               );
    glm::mat4 Model      = glm::mat4(1.0f);
    glm::mat4 MVP        = Projection * View * Model;
    uniform1.write(&MVP[0][0],4,4,1);
    EngGLAttribute attrib1;
    attrib1.setShader(&shader);
    attrib1.bind("vcolor");
    GLfloat color[4] = {0.5f,0.0f,0.0f,1.0f};
    attrib1.write(color,4);
    EngGLVBO buf1;
    GLfloat pos[] = {
            -1.0f, -1.0f, 0.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f,
             0.0f,  1.0f, 0.0f, 1.0f,
    };
    buf1.allocate(sizeof(pos),GL_STATIC_DRAW,pos);
    buf1.setShader(&shader);
    buf1.setLocation("pos");
    glClearColor(0.3f,0.3f,0.3f,1.0f);
    //glUseProgram(program);
    buf1.bind();
    buf1.enable();
    do
    {
        glClear(GL_COLOR_BUFFER_BIT);
        buf1.render(3);
        glfwSwapBuffers(platform->controll_window);
        glfwPollEvents();
    } while (glfwGetKey(platform->controll_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
             glfwWindowShouldClose(platform->controll_window) == 0);
    buf1.disable();
    buf1.clear();
    glDeleteVertexArrays(1,&VAO);
    return 0;
}

