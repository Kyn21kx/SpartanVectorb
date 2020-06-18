#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Headers/Vectors.h"
#include"Headers/Shader.h"
#include "Headers/Renderer.h"
#include "Headers/Demo.h"

#define GET_NAME(variable) (#variable)

// Our state
bool keyInput = true;
float x, y, z;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
Renderer* r;
float camX, camY, camZ = -50;
float camRotA = 40, camRotX = -27, camRotY = 1, camRotZ;
std::vector<Vector3> testVectors;
bool horizontalRot;

void Update();
void VectorsUI();
void KeyboardInput(unsigned char k, int x, int y);

int main(int a, char** arg) { 
    r = new Renderer (a, arg, 720, 480, Update, KeyboardInput);
}

void KeyboardInput(unsigned char k, int x, int y) {
    r->ClearScreen();
    glLoadIdentity();
    if (keyInput) {
        switch (k) {
        case 'a':
            camX++;
            break;
        case 'd':
            camX--;
            break;
        case 'w':
            camZ++;
            break;
        case 's':
            camZ--;
            break;
        case 'z':
            camY++;
            break;
        case 'x':
            camY--;
            break;
        case '8':
            camRotA--;
            break;
        case '2':
            camRotA++;
            break;
        case '4':
            horizontalRot = true;
            camRotX = 0;
            break;
        case '6':
            horizontalRot = false;
            camRotX = -27;
            break;
        default:
            break;
        }
    }
    glutPostRedisplay();
}

void display() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    {
        ImGui::Begin("Window manager");
        ImGui::Checkbox("Enable / Disable Keyboard input", &keyInput);
        if (ImGui::Button("Create new vector")) {
            testVectors.push_back(Vector3());
        }
        ImGui::Text("Rotation mode: ");
        ImGui::SameLine();
        if (horizontalRot) {
            ImGui::Text("Horizontal");
        }
        else {
            ImGui::Text("Vertical");
        }
        ImGui::End();
    }

    VectorsUI();

    // Rendering
    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();
    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    r->ClearScreen();
    //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound, but prefer using the GL3+ code.
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    glutPostRedisplay();
    glLoadIdentity();
}

void Update() {
    display();
    //Translate and rotate just to get a better view
    glTranslatef(camX, camY, camZ);
    glRotatef(camRotA, camRotX, camRotY, camRotZ);
    r->DrawListOfVectors(testVectors, 5.0f);
    Renderer::DrawCartesianPlane(200);
    glutSwapBuffers();
}

void VectorsUI () {
    for (int i = 0; i < testVectors.size(); i++) {
        std::string name = "Test #";
        name.append(std::to_string(i));
        testVectors[i].DisplayPropertiesWindow(name.c_str());
    }
}
