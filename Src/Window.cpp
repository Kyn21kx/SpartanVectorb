#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Headers/Vectors.h"
#include"Headers/Shader.h"
#include "Headers/Renderer.h"
#include "Headers/Demo.h"

//int window();

// Our state
bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
Renderer* r;
float camX, camY, camZ = -50;
float camRotA = 40, camRotX = 1, camRotY = 1, camRotZ;
void Update();
void KeyboardInput(unsigned char k, int x, int y);
int main(int a, char** arg) {
    r = new Renderer (a, arg, 720, 480, Update, KeyboardInput);

}

void KeyboardInput(unsigned char k, int x, int y) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    switch (k) {
    case 'a':
        std::cout << "TestKeyboard" << std::endl;
        camX++;
        break;
    case 'd':
        std::cout << "TestKeyboard" << std::endl;
        camX--;
        break;
    case 'w':
        std::cout << "TestKeyboard" << std::endl;
        camZ++;
        break;
    case 's':
        std::cout << "TestKeyboard" << std::endl;
        camZ--;
        break;
    case 'z':
        camY--;
        break;
    case 'x':
        camY++;
        break;
    case '8':
        camRotA++;
        break;
    case '2':
        camRotA--;
        break;
    case '4':
        camRotZ++;
        break;
    case '6':
        camRotZ--;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void display() {
    std::cout << "Testing" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}

void Update() {
    display();
    Vector3 test(10, 50, 20);
    //Translate and rotate just to get a better view
    glTranslatef(camX, camY, camZ);
    glRotatef(camRotA, camRotX, camRotY, camRotZ);
    r->DrawVector(test, 2);
    Renderer::DrawCartesianPlane(100);
    glutSwapBuffers();
}
/*
int window() {
    Renderer rend;
    Shader shaderManager;
    Vector4 color;
    Vector3 line[2];
    //Get the file of the shader code
    auto shaderCode = shaderManager.PassShader("Resources/Shaders/Basic.shader");
    std::cout << shaderCode.VertexSource << std::endl;
    unsigned int shader = shaderManager.CreateShader(shaderCode.VertexSource, shaderCode.FragmentSource);
    /* Loop until the user closes the window 
    float r = 0, g = 0, b = 0, a = 1;
    glUseProgram(shader);
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL((), true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    bool sliderInput = true;
    while (!glfwWindowShouldClose(rend.GetWindow())) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        color.SetValues(r, g, b, a);
        r = r < 1 ? r + 0.001 : 0;
        g = g < 1 ? g + 0.0001 : 0;
        b = b < 1 ? b + 0.00001 : 0;
        shaderManager.ChangeColor(shader, "u_Color", color);
        /* Render here 
        rend.ClearScreen();
        //IMGUI code
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        float mag = line[0].GetMagnitude();
        int counter = 0;

        {
            ImGui::Begin("Vector");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Checkbox("Slider Input:", &sliderInput);
            if (sliderInput) {
                ImGui::SliderFloat("X", &x, -100.0f, 100.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::SliderFloat("Y", &y, -100.0f, 100.0f);
            }
            else {
                ImGui::DragFloat("X", &x);
                ImGui::DragFloat("Y", &y);
            }

            ImGui::Text("Vector's magnitude: %f", mag);
            if (line[0] != Vector3Math::Zero()) {
                ImGui::Text("Angle: %f", line[0].GetAngle());
                ImGui::Text("Normalized vector ");
                ImGui::SameLine();
                ImGui::Text(line[0].Normalize().ToString().c_str());
            }
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
        {
            ImGui::Begin("Manager");
            if (ImGui::Button("Create vector")) {
                
            }
            ImGui::End();
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        line[0].SetValues(x, y, z);
        rend.DrawVector(line[0], 5);
        // Swap front and back buffers
        glfwSwapBuffers(rend.GetWindow());
        // Poll for and process events
        glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
*/