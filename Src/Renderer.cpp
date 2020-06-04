#include "Headers/Renderer.h"

Renderer::Renderer() {
    WindowSetup(720, 480);
}
Renderer::Renderer(int winWidth, int winHeight) {
    WindowSetup(winWidth, winHeight);
}

int Renderer::WindowSetup(int width, int height) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Vector Test", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cout << "Error!" << std::endl;
    }

    //glm::mat4 proj = glm::perspective(35.0f, 1.0f, 0.1f, 100.0f);
    glOrtho(0, width, 0, height, 0, 1); // essentially set coordinate system
    glViewport(0.0f, 0.0f, width, height); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode(GL_MODELVIEW); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    
    m_window = window;
    
}

void Renderer::DrawCartesianPlane() const {
	Vector3 cartesianVectorPos((float)std::numeric_limits<float>::infinity(), (float)std::numeric_limits<float>::infinity(), 0);

}

void Renderer::DrawVector(Vector3 v, float lineWidth) {
    // Render OpenGL here
    glLineWidth(lineWidth);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, v.ToVertices<6>().data());
    //(GL_LINES, [Desde qué índice del arreglo empieza], [Cantidad de vectores deseados])
    glDrawArrays(GL_LINES, 0, 2);
    glDisableClientState(GL_VERTEX_ARRAY);
}
/*
void Renderer::DrawVector(Vector2 v, float lineWidth) {
    glLineWidth(lineWidth);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, v.ToVertices<4>().data());
    //(GL_LINES, [Desde qué índice del arreglo empieza], [Cantidad de vectores deseados])
    glDrawArrays(GL_LINES, 0, 2);
    glDisableClientState(GL_VERTEX_ARRAY);
}*/

void Renderer::DrawVector(Vector3 fromAltOrigin, Vector3 toPoint, float lineWidth) {
    glLineWidth(lineWidth);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, toPoint.ToVertices<6>(fromAltOrigin).data());
    //(GL_LINES, [Desde qué índice del arreglo empieza], [Cantidad de vectores deseados])
    glDrawArrays(GL_LINES, 0, 2);
    glDisableClientState(GL_VERTEX_ARRAY);
}

/*void Renderer::DrawVector(Vector2 fromAltOrigin, Vector2 toPoint, float lineWidth) {
    glLineWidth(lineWidth);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, toPoint.ToVertices<4>(fromAltOrigin).data());
    //(GL_LINES, [Desde qué índice del arreglo empieza], [Cantidad de vectores deseados])
    glDrawArrays(GL_LINES, 0, 2);
    glDisableClientState(GL_VERTEX_ARRAY);
}*/

void Renderer::ClearScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::CameraPerspective() {

}
