// Include standard headers
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

#include <stdlib.h>
#include <string.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

#define GLM_FORCE_RADIANS

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
using namespace glm;


#include <unistd.h>


static const GLfloat vertices[] = {
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f, 1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,

    //Floor
   -10.0f,-1.0f,-10.0f,
    10.0f,-1.0f, 10.0f,
    10.0f,-1.0f,-10.0f,
   -10.0f,-1.0f, 10.0f,
    10.0f,-1.0f, 10.0f,
   -10.0f,-1.0f,-10.0f,
};


static const GLfloat colors[] = {
    //cube
    1.0f,  0.0f,  1.0f,//magenta
    1.0f,  0.0f,  1.0f,//magenta
    1.0f,  0.0f,  1.0f,//magenta
    1.0f,  1.0f,  0.0f,//yellow
    1.0f,  1.0f,  0.0f,//yellow
    1.0f,  1.0f,  0.0f,//yellow
    1.0f,  1.0f,  1.0f,//white
    1.0f,  1.0f,  1.0f,//white
    1.0f,  1.0f,  1.0f,//white
    1.0f,  1.0f,  0.0f,//yellow
    1.0f,  1.0f,  0.0f,//yellow
    1.0f,  1.0f,  0.0f,//yellow
    1.0f,  0.0f,  1.0f,//magenta
    1.0f,  0.0f,  1.0f,//magenta
    1.0f,  0.0f,  1.0f,//magenta
    1.0f,  1.0f,  1.0f,//white
    1.0f,  1.0f,  1.0f,//white
    1.0f,  1.0f,  1.0f,//white
    0.0f,  1.0f,  1.0f,//cyan
    0.0f,  1.0f,  1.0f,//cyan
    0.0f,  1.0f,  1.0f,//cyan
    1.0f,  0.0f,  0.0f,//red
    1.0f,  0.0f,  0.0f,//red
    1.0f,  0.0f,  0.0f,//red
    1.0f,  0.0f,  0.0f,//red
    1.0f,  0.0f,  0.0f,//red
    1.0f,  0.0f,  0.0f,//red
    0.0f,  1.0f,  0.0f,//green
    0.0f,  1.0f,  0.0f,//green
    0.0f,  1.0f,  0.0f,//green
    0.0f,  1.0f,  0.0f,//green
    0.0f,  1.0f,  0.0f,//green
    0.0f,  1.0f,  0.0f,//green
    0.0f,  1.0f,  1.0f,//cyan
    0.0f,  1.0f,  1.0f,//cyan
    0.0f,  1.0f,  1.0f,//cyan

    //Floor
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f
};

//normals
static const GLfloat normals[] = {
    //Cube
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    //Floor
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
};

// light position
GLfloat light[3] = {-3, 1.5, 2};

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

int main( void )
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);

    const GLFWvidmode* mode = glfwGetVideoMode(monitors[count-1]);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( mode->width, mode->height, "Basic Shadow Map", monitors[count-1], NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    // Capture the escape key
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.2f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);


    /// VBO: The attributes: vertex, color, normal

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint vbo[3];  
    glGenBuffers(3, vbo);

    // positions
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    //colors
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    //normals
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);


    /// Render to texture

    // The framebuffer - depth buffer.
    GLuint FramebufferName = 0;
    glGenFramebuffers(1, &FramebufferName);

    // Depth texture.
    GLuint depthTexture;
    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 mode->width, mode->height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);


    // Always check that our framebuffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        return false;

    ///
    /// the shadow map shader
    ///

    // Create and compile our GLSL program from the shaders
    GLuint depthProgramID = LoadShaders( "shadowmap.vert", "shadowmap.frag" );

    // Compute the MVP matrix from the light's point of view
    glm::mat4 depthProjectionMatrix = glm::ortho<float>(-15,15,-15,15,-15,20);
    glm::mat4 depthViewMatrix = glm::lookAt(glm::vec3(light[0], light[1], light[2]), glm::vec3(0,0,0), glm::vec3(0,1,0));
    glm::mat4 Model = glm::mat4(1.0f);

    GLuint depthProjectionMatrixID = glGetUniformLocation(depthProgramID, "Projection");
    GLuint depthViewMatrixID = glGetUniformLocation(depthProgramID, "View");
    GLuint depthModelMatrixID = glGetUniformLocation(depthProgramID, "Model");

    glUseProgram(depthProgramID);
    glUniformMatrix4fv(depthProjectionMatrixID, 1, GL_FALSE, &depthProjectionMatrix[0][0]);
    glUniformMatrix4fv(depthViewMatrixID, 1, GL_FALSE, &depthViewMatrix[0][0]);
    glUniformMatrix4fv(depthModelMatrixID, 1, GL_FALSE, &Model[0][0]);

    ///
    /// The main shader
    ///

    // Create and compile our GLSL program from the shaders
    GLuint program = LoadShaders( "SimpleVertexShader.vert", "SimpleFragmentShader.frag" );

    // Get a handles
    GLuint MatrixID_M = glGetUniformLocation(program, "M");
    GLuint MatrixID_V = glGetUniformLocation(program, "V");
    GLuint MatrixID_P = glGetUniformLocation(program, "P");
    GLuint lightID = glGetUniformLocation(program, "lightPos");    
    GLuint depthViewID = glGetUniformLocation(program, "depthView");
    GLuint depthProjectionID = glGetUniformLocation(program, "depthProjection");
    GLuint ShadowMapID = glGetUniformLocation(program, "shadowMap");

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) mode->width / (float)mode->height, 0.1f, 100.0f);
    glm::mat4 View = glm::lookAt(
        glm::vec3(0,4,15), // Camera is at (0,4,15), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)
        );

    glUseProgram(program);
    glUniformMatrix4fv(MatrixID_P, 1, GL_FALSE, &Projection[0][0]);
    glUniformMatrix4fv(MatrixID_M, 1, GL_FALSE, &Model[0][0]);
    glUniformMatrix4fv(MatrixID_V, 1, GL_FALSE, &View[0][0]);
    glUniform3fv(lightID, 1, &light[0]);

    glUniformMatrix4fv(depthViewID, 1, GL_FALSE, &depthViewMatrix[0][0]);
    glUniformMatrix4fv(depthProjectionID, 1, GL_FALSE, &depthProjectionMatrix[0][0]);


    float deg = 1;
    int i = 0;    
    double t0, t1;


    do{
        t0 = glfwGetTime();

        glm::mat4 rot = glm::rotate(i++ * glm::radians(deg), glm::vec3(0.0, 1.0, 0.0));
        glm::vec4 tmp(0.0f, 4.0f, 15.0f, 0.0f);
        glm::vec4 transformedVector = rot * tmp;

        View = glm::lookAt(
                glm::vec3(transformedVector), // Camera is in World Space
                glm::vec3(0,0,0), // and looks at the origin
                glm::vec3(0,1,0)
                );

        /// shadow map

        // Render to our framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
        glViewport(0,0,mode->width,mode->height); // Render on the whole framebuffer, complete from the lower left corner to the upper right
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT); // Cull back-facing triangles -> draw only front-facing triangles
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use shadowmap shader
        glUseProgram(depthProgramID);
        glDrawArrays(GL_TRIANGLES, 0, 14*3);

        /// main shader

        // Render to the framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0,0,mode->width,mode->height);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program);

        // Send the view matrix
        glUniformMatrix4fv(MatrixID_V, 1, GL_FALSE, &View[0][0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glUniform1i(ShadowMapID, 0);

        // Draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 14*3);

        t1 = glfwGetTime();
        printf("%lf\n", (t1-t0)*1000);
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();        



    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Cleanup vbo
    glDeleteBuffers(1, &vbo[0]);
    glDeleteBuffers(1, &vbo[1]);
    glDeleteBuffers(1, &vbo[2]);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(program);
    glDeleteProgram(depthProgramID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }else{
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;


    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}
