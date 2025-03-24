/* para linux, instalar os pacotes libglfw3-dev mesa-common-dev libglew-dev */
/* para compilar no linux: gcc main.c -lglfw -lGL -lGLEW -lm */

/* para windows, instalar bibliotecas compiladas do glfw3 e glew no ambiente mingw */
/* para compilar no windows: gcc main.c -lglfw3dll -lglew32 -lopengl32 */


#include <GL/glew.h>  

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> /* verifique no seu SO onde fica o glfw3.h */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

 
 
int main(void){
 
    // inicicializando o sistema de\ janelas
    glfwInit();

    // deixando a janela invisivel, por enquanto
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

 
    // criando uma janela
    GLFWwindow* window = glfwCreateWindow(800, 800, "Minha Janela", NULL, NULL);

    
    // tornando a janela como principal 
    glfwMakeContextCurrent(window);

    // inicializando Glew (para lidar com funcoes OpenGL)
    GLint GlewInitResult = glewInit();
    printf("GlewStatus: %s", glewGetErrorString(GlewInitResult));

    // Exibindo nossa janela
    glfwShowWindow(window);

    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);
 
        glfwSwapBuffers(window);
        
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
