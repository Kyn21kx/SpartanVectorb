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
    glViewport(0.0f, 0.0f, windowWidth, windowHeight);
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
        glLineWidth(0.01f);
        glBegin(GL_LINES);
        glColor3f(1, 1, 1);
        glVertex3f(0, 0, 0);
        glVertex3f((units / 2), 0, 0);
        glEnd();
        glPopMatrix();
    }
}


void Renderer::DrawVector(Vector3 v, float lineWidth) {
    glPushMatrix();
    glLineWidth(lineWidth);
    glEnable(GL_SMOOTH);
    glBegin(GL_LINES);
    glColor3f(v.r, v.g, v.b);
    glVertex3f(0, 0, 0);
    glVertex3f(v.GetX(), v.GetY(), v.GetZ());
    //(GL_LINES, [Desde qué índice del arreglo empieza], [Cantidad de vectores deseados])
    glEnd();
    glPopMatrix();
}

void Renderer::DrawVector(Vector3 fromAltOrigin, Vector3 toPoint, float lineWidth) {
    glPushMatrix();
    glLineWidth(lineWidth);
    glEnable(GL_SMOOTH);
    glBegin(GL_LINES);
    glColor3f(toPoint.r, toPoint.g, toPoint.b);
    glVertex3f(fromAltOrigin.GetX(), fromAltOrigin.GetY(), fromAltOrigin.GetZ());
    glVertex3f(toPoint.GetX(), toPoint.GetY(), toPoint.GetZ());
    //(GL_LINES, [Desde qué índice del arreglo empieza], [Cantidad de vectores deseados])
    glEnd();
    glPopMatrix();
}

void Renderer::DrawListOfVectors(std::vector<Vector3> list, float lineWidth) {
    for (Vector3 el : list) {
        float nX = (el.GetMagnitude() / 8.0f) * cosf(150);
        float nY = (el.GetMagnitude() / 8.0f) * sinf(150);
        Vector3 upV(nX, nY, el.GetZ());
        Vector3 downV(nX, -nY, el.GetZ());
        DrawVector(el, lineWidth);
        /*DrawVector(el, upV, lineWidth);
        DrawVector(el, downV, lineWidth);
        */
    }
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::CameraPerspective() {

}

void Renderer::GLUTWindow(int n, char** arg, void mainLoopFunc(), void inputFunc(unsigned char k, int x, int y)) {
    glutInit(&n, arg);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Spartan Vector");
    glutDisplayFunc(mainLoopFunc);
    glutKeyboardFunc(inputFunc);
#pragma region ImGUI_Code
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    // Setup Platform/Renderer bindings
    ImGui_ImplGLUT_Init();
    ImGui_ImplGLUT_InstallFuncs();
    ImGui_ImplOpenGL2_Init();
#pragma endregion
    Init();
    glutMainLoop();
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();
}

