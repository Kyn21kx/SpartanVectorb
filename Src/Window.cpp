#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Headers/Vectors.h"
#include"Headers/Shader.h"
#include "Headers/Renderer.h"
#include "Headers/Demo.h"

int window();

// Our state
static int g_Time = 0;
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
        camRotX++;
        break;
    case '6':
        camRotX--;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void display() {
    std::cout << "Testing" << std::endl;
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();

    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

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
    Vector3 test(10, 10, 50);
    //Translate and rotate just to get a better view
    glTranslatef(camX, camY, camZ);
    glRotatef(camRotA, camRotX, camRotY, camRotZ);
    r->DrawVector(test, 5);
    Renderer::DrawCartesianPlane(100);
    glutSwapBuffers();
}

int window() {

    Vector4 color;
    Vector3 line[2];
    //Get the file of the shader code
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL((r->GetWindow()), true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    bool sliderInput = true;
    while (!glfwWindowShouldClose(r->GetWindow())) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        r->ClearScreen();
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
        r->DrawVector(line[0], 5);
        // Swap front and back buffers
        glfwSwapBuffers(r->GetWindow());
        // Poll for and process events
        glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}