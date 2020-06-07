#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Headers/Vectors.h"
#include"Headers/Shader.h"
#include "Headers/Renderer.h"
#include "Headers/Demo.h"

// Our state
bool show_demo_window = true;
float x, y, z;
bool sliderInput = true;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
Renderer* r;
float camX, camY, camZ = -50;
float camRotA = 40, camRotX = -27, camRotY = 1, camRotZ;
Vector3 test;
bool horizontalRot;

void Update();
void KeyboardInput(unsigned char k, int x, int y);

int main(int a, char** arg) {
    r = new Renderer (a, arg, 720, 480, Update, KeyboardInput);
}

void KeyboardInput(unsigned char k, int x, int y) {
    r->ClearScreen();
    glLoadIdentity();
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
    glutPostRedisplay();
}

void display() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    {
        ImGui::Begin("Window manager");
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
    {
        static int counter = 0;

        ImGui::Begin("Vector properties");                          // Create a window called "Hello, world!" and append into it.
        ImGui::Checkbox("Slider input", &sliderInput);      // Edit bools storing our window open/close state
        if (ImGui::Button("Manual setup")) {
            std::cout << "Set X: ";
            std::cin >> x;
            std::cout << "Set Y: ";
            std::cin >> y;
            std::cout << "Set Z: ";
            std::cin >> z;
        }
        if (sliderInput) {
            ImGui::SliderFloat("X", &x, -50.0f, 50.0f);
            ImGui::SliderFloat("Y", &y, -50.0f, 50.0f);
            ImGui::SliderFloat("Z", &z, -50.0f, 50.0f);
        }
        else {
            ImGui::DragFloat("X", &x);
            ImGui::DragFloat("Y", &y);
            ImGui::DragFloat("Z", &z);
        }
        ImGui::Text("Magnitude: %f", test.GetMagnitude());
        if (test != Vector3Math::Zero()) {
            ImGui::Text("Normalized vector: ");
            ImGui::Text(test.Normalize().ToString().c_str());
            ImGui::Text("Theta angle = %f", test.GetAngle());
        }
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

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
    test.SetValues(x, y, z);
    //Translate and rotate just to get a better view
    glTranslatef(camX, camY, camZ);
    glRotatef(camRotA, camRotX, camRotY, camRotZ);
    r->DrawVector(test, 15);
    Renderer::DrawCartesianPlane(200);
    glutSwapBuffers();
}