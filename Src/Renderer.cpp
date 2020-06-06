#include "Headers/Renderer.h"


Renderer::Renderer() {
    std::cout << "Error, no parameters have been set for the constructor of the renderer, please call the constructor from the main function and provide appropiate parameters!";
    windowHeight = 0;
    windowWidth = 0;
}

Renderer::Renderer(int n, char** arg, int winWidth, int winHeight, void MainLoopFunc(), void InputFunc(unsigned char k, int x, int y)) {
    windowWidth = winWidth;
    windowHeight = winHeight;
    GLUTWindow(n, arg, MainLoopFunc, InputFunc);
}

void Renderer::Init() {
    glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    gluPerspective(35, 1, 0.1f, 1000);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glViewport(0.0f, 0.0f, 720, 480); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels

}

int Renderer::WindowSetup(int width, int height) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Vector Test", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cout << "Error!" << std::endl;
    }

    
    
}

void Renderer::DrawCartesianPlane(int units) {
    for (int i = 0; i < units; i++) {
        glPushMatrix();
        if (i < units / 2) {
            glTranslatef(0, 0, i);
        }
        else if (i >= units / 2) {
            glTranslatef(i - units / 2, 0, 0);
            glRotatef(-90, 0, 1, 0);
        }
        glBegin(GL_LINES);
        glColor3f(1, 1, 1);
        glLineWidth(0.01f);
        glVertex3f(0, -0.1, 0);
        glVertex3f((units / 2) - 1, -0.1, 0);
        glEnd();
        glPopMatrix();
    }
}

void Renderer::DrawVector(Vector3 v, float lineWidth) {
    glPushMatrix();
    glBegin(GL_LINES);
    glLineWidth(lineWidth);
    glColor3f(1, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(v.GetX(), v.GetY(), v.GetZ());
    //(GL_LINES, [Desde qu� �ndice del arreglo empieza], [Cantidad de vectores deseados])
    glEnd();
    glPopMatrix();
}
/*
void Renderer::DrawVector(Vector2 v, float lineWidth) {
    glLineWidth(lineWidth);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, v.ToVertices<4>().data());
    //(GL_LINES, [Desde qu� �ndice del arreglo empieza], [Cantidad de vectores deseados])
    glDrawArrays(GL_LINES, 0, 2);
    glDisableClientState(GL_VERTEX_ARRAY);
}*/

void Renderer::DrawVector(Vector3 fromAltOrigin, Vector3 toPoint, float lineWidth) {
    glLineWidth(lineWidth);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, toPoint.ToVertices<6>(fromAltOrigin).data());
    //(GL_LINES, [Desde qu� �ndice del arreglo empieza], [Cantidad de vectores deseados])
    glDrawArrays(GL_LINES, 0, 2);
    glDisableClientState(GL_VERTEX_ARRAY);
}

/*void Renderer::DrawVector(Vector2 fromAltOrigin, Vector2 toPoint, float lineWidth) {
    glLineWidth(lineWidth);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, toPoint.ToVertices<4>(fromAltOrigin).data());
    //(GL_LINES, [Desde qu� �ndice del arreglo empieza], [Cantidad de vectores deseados])
    glDrawArrays(GL_LINES, 0, 2);
    glDisableClientState(GL_VERTEX_ARRAY);
}*/

void Renderer::ClearScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::CameraPerspective() {

}

void Renderer::GLUTWindow(int n, char** arg, void mainLoopFunc(), void inputFunc(unsigned char k, int x, int y)) {
    glutInit(&n, arg);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Testing glut");
    glutDisplayFunc(mainLoopFunc);
    glutKeyboardFunc(inputFunc);
    Init();
    glutMainLoop();
}
