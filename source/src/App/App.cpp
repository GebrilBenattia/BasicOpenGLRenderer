#include "App.hpp"
#include "Matrix3.hpp"
#include "Framebuffer.hpp"
#include "Utils.hpp"

std::vector<Scene> App::m_ScenesList;
Window App::window;
Camera App::cam = Camera(0, 0, 20, 0, 1, 0);

float App::deltaTime;

App::~App()
{
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void App::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.ProcessKeyboard(FORWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.ProcessKeyboard(BACKWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.ProcessKeyboard(LEFT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cam.ProcessKeyboard(DOWNWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cam.ProcessKeyboard(UPWARD, deltaTime);
}

void App::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (cam.firstMouse)
    {
        cam.lastX = xpos;
        cam.lastY = ypos;
        cam.firstMouse = false;
    }

    float xoffset = xpos - cam.lastX;
    float yoffset = cam.lastY - ypos; // reversed since y-coordinates go from bottom to top

    cam.lastX = xpos;
    cam.lastY = ypos;

    cam.ProcessMouseMovement(xoffset, yoffset, true);
}

void App::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    cam.ProcessMouseScroll(static_cast<float>(yoffset));
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------


int App::Update()
{
    window.SetupGLFW(SCR_WIDTH, SCR_HEIGHT, "Herethon");

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                       //CREATING SHADERS

    ResourceManager::Create<Shader>("ourshader");
    ResourceManager::Create<Shader>("lightshader");
    ResourceManager::Create<Shader>("shaderSingleColor");
    ResourceManager::Create<Shader>("blendingshader");
    ResourceManager::Create<Shader>("skyboxshader");
    ResourceManager::Create<Shader>("framebufferShader");

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                    //CREATING MODELS

    ResourceManager::Create<Model>("Batman.obj");
    ResourceManager::Create<Model>("cube.obj");
    ResourceManager::Create<Model>("plane.obj");
    ResourceManager::Create<Model>("sphere.obj");


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                    //CREATING TEXTURES

    ResourceManager::Create<Texture>("viking_room.jpg");
    ResourceManager::Create<Texture>("container.jpg");
    ResourceManager::Create<Texture>("wall.jpg");
    ResourceManager::Create<Texture>("container2.jpg");
    ResourceManager::Create<Texture>("window2.png");
    ResourceManager::Create<Texture>("grass.png");
    ResourceManager::Create<Texture>("dirt.jpg");
    ResourceManager::Create<Texture>("gold.jpg");
    ResourceManager::Create<Texture>("Logo.png");

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                    //LOADING MODELS

    ResourceManager::Get<Model>("Batman.obj")->Load3DModel("Batman.obj");
    ResourceManager::Get<Model>("cube.obj")->Load3DModel("cube.obj");
    ResourceManager::Get<Model>("plane.obj")->Load3DModel("plane.obj");
    ResourceManager::Get<Model>("sphere.obj")->Load3DModel("sphere.obj");

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                    //CREATING LIGHT 2 - 5

    //PointLight pointLight1(Vector3(0.f, 0.2f, 0.f), 1.0f, 0.09f, 0.032f, Vector3(0.05f, 0.05f, 0.05f), Vector3(0.8f, 0.8f, 0.8f), Vector3(1.0f, 1.0f, 1.0f));
    //PointLight pointLight2(Vector3(2.3f, -3.3f, -4.0f), 1.0f, 0.09f, 0.032f, Vector3(0.05f, 0.05f, 0.05f), Vector3(0.8f, 0.8f, 0.8f), Vector3(1.0f, 1.0f, 1.0f));
    PointLight pointLight3(Vector3(0.0f, 5.0f, 0.0f), 1.0f, 0.09f, 0.032f, Vector3(0.05f, 0.05f, 0.05f), Vector3(0.8f, 0.8f, 0.8f), Vector3(1.0f, 1.0f, 1.0f));
    //PointLight pointLight4(Vector3(0.0f, 0.0f, -3.0f), 1.0f, 0.09f, 0.032f, Vector3(0.05f, 0.05f, 0.05f), Vector3(0.8f, 0.8f, 0.8f), Vector3(1.0f, 1.0f, 1.0f));


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                   //CREATING LIGHT 6 & 7

    SpotLight spot1(cam.Position, cam.Front, std::cosf((12.5f * (M_PI / 180.f))), std::cosf((12.5f * (M_PI / 180.f))), 1.0f, 0.09f, 0.032f, Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 1.0f, 1.0f));

    SpotLight spot2(Vector3(10.5f, 20.f ,0.5f), Vector3(0.f, -1.f, 0.f), std::cosf((12.5f * ((float)M_PI / 180.f))), std::cosf((12.5f * ((float)M_PI / 180.f))), 1.0f, 0.09f, 0.032f, Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(1.f, 0.f, 1.f));
    //PointLight pointLight1(Vector3(10.f, 10.2f, 0.f), 1.0f, 0.09f, 0.032f, Vector3(0.05f, 0.05f, 0.05f), Vector3(0.8f, 0.8f, 0.8f), Vector3(1.0f, 1.0f, 1.0f));

    spot1.name = "CameraFlashLight";

    DirLight dir1(Vector3(-0.2f, -1.0f, -0.3f), Vector3(0.05f, 0.05f, 0.05f), Vector3(0.4f, 0.4f, 0.4f), Vector3(0.5f, 0.5f, 0.5f));

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Enables the Depth Buffer
    glEnable(GL_DEPTH_TEST);

    Scene scene("Main Scene");

    //scene.AddSpotLight(spot1);

    Skybox sky(cam);

    Cube cube(cam);
    cube.transform.pos = Vector3(0.f, -5.f, 0.f);
    cube.transform.scale = Vector3(10.f, 10.f, 10.f);

    Framebuffer fb(window.GetWidth(), window.GetHeight());

    Utils::SetupImGui(window.GetWindow());

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window.GetWindow()))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // input
        // -----
        std::string FPS = std::to_string(1 / deltaTime);
        std::string NewTitle = "Herethon - " + FPS + " FPS";
        glfwSetWindowTitle(window.GetWindow(), NewTitle.c_str());

        Utils::SetupDockSpace(window);

        // render
        // ------
        fb.Bind();
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // ... rendering our triangle as before
        spot1.m_Position = cam.Position;
        spot1.m_Direction = cam.Front;

        Vector3 lightcolor(1.0, 1.0, 1.0);

        ResourceManager::Get<Shader>("ourshader")->Use();
        ResourceManager::Get<Shader>("ourshader")->SetVec3("color", lightcolor);

        ResourceManager::Get<Shader>("ourshader")->SetVec3("viewPos", cam.Position);
        ResourceManager::Get<Shader>("ourshader")->SetFloat("material.shininess", 64.0f);

        scene.Update();

        DirLight::Update();
        SpotLight::Update(cam);
        PointLight::Update(cam);
        /*
        */

        //spot1.UpdateSelf(cam);

        ResourceManager::Get<Shader>("lightshader")->Use();

        sky.Update();

        cube.Update(*ResourceManager::Get<Shader>("ourshader"));

        //cube.transform.eulerRot += 0.1f;
        //cube2.Update(*ResourceManager::Get<Shader>("ourshader"));

        fb.Unbind();

        if (ImGui::BeginMainMenuBar()) {
            // Décalage pour le logo
            ImGui::Dummy(ImVec2(-13, 0)); // Remplace 50 par la largeur de ton logo
            // Affichage de la texture de la "viking_room" à la place du dummy
            float window_width = 25;
            float window_height = 25;
            GLuint vikingRoomTextureID = ResourceManager::Get<Texture>("Logo.png")->TextureID;

            ImVec2 pos = ImGui::GetCursorScreenPos();
            ImGui::Image((void*)(intptr_t)vikingRoomTextureID, ImVec2(window_width, window_height), ImVec2(0, 1), ImVec2(1, 0), ImVec4(1, 1, 1, 1)); // Remplace par les dimensions de ton logo

            float availableSpaceY = ImGui::GetContentRegionAvail().y - window_height;

            //ImGui::Dummy(ImVec2(0.0f, availableSpaceY)); // Utilise l'espace disponible en Y pour ajuster l'espacement

            int width, height;
            glfwGetWindowSize(window.GetWindow(), &width, &height);

            // Placement du logo
            ImGui::SameLine(window_width + 10); // Place les éléments à la même ligne
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New")) {
                    // Action à effectuer lorsqu'on clique sur "New"
                }
                if (ImGui::MenuItem("Open")) {
                    // Action à effectuer lorsqu'on clique sur "Open"
                }
                ImGui::EndMenu();
            }
            ImGui::SameLine(window_width + 45); // Place les éléments à la même ligne
            if (ImGui::BeginMenu("Edit")) {
                ImGui::EndMenu();
            }
            ImGui::SameLine(window_width + 80); // Place les éléments à la même ligne
            if (ImGui::BeginMenu("Help")) {
                ImGui::EndMenu();
            }
            ImGui::SameLine(width - 180);
            if (ImGui::MenuItem("Minimize")) {
                // Action à effectuer lorsqu'on clique sur "Minimize"
                glfwIconifyWindow(window.GetWindow()); // Réduit la fenêtre
            }
            ImGui::SameLine(width - 120);
            if (ImGui::MenuItem("Fullscreen")) {
                // Action à effectuer lorsqu'on clique sur "Windowed/Fullscreen"
                // Basculer entre mode plein écran et fenêtré
                if (window.IsFullScreen()) {
                    // Basculer en mode fenêtré
                    int windowedPosX, windowedPosY;
                    glfwGetWindowPos(window.GetWindow(), &windowedPosX, &windowedPosY);
                    glfwSetWindowMonitor(window.GetWindow(), NULL, windowedPosX, windowedPosY, window.GetWidth(), window.GetHeight(), GLFW_DONT_CARE);
                    window.SetFullScreen(false);
                }
                else {
                    // Basculer en mode plein écran
                    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
                    glfwSetWindowMonitor(window.GetWindow(), glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
                    window.SetFullScreen(true);
                }
            }
            ImGui::SameLine(width - 50);
            if (ImGui::MenuItem("Close")) {
                // Action à effectuer lorsqu'on clique sur "Close"
                glfwSetWindowShouldClose(window.GetWindow(), GLFW_TRUE); // Ferme la fenêtre GLFW
            }
            ImGui::EndMainMenuBar();
        }
       
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));
        if (ImGui::Begin("Scene", NULL)) {
            if (ImGui::IsWindowFocused()) {
                processInput(window.GetWindow());
                glfwSetCursorPosCallback(window.GetWindow(), App::mouse_callback);
                glfwSetScrollCallback(window.GetWindow(), App::scroll_callback);
                glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                cam.Update();
            }
            else {
                glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            float window_width = ImGui::GetContentRegionAvail().x;
            float window_height = ImGui::GetContentRegionAvail().y;

            fb.Rescale(window_width, window_height);
            glViewport(0, 0, (int)window_width, (int)window_height);

            ImVec2 pos = ImGui::GetCursorScreenPos();

            //and here we can add our created texture as image to ImGui
            //unfortunately we need to use the cast to void* or I didn't find another way tbh
            ImGui::GetWindowDrawList()->AddImage(
                (void*)(intptr_t)fb.GetTexture(),
                ImVec2(pos.x, pos.y),
                ImVec2(pos.x + window_width, pos.y + window_height),
                ImVec2(0, 1),
                ImVec2(1, 0)
            );
        }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        deltaTime = static_cast<float>(ImGui::GetIO().DeltaTime);

        //std::cout << glfwGetTime() - time << std::endl;

        glfwSwapBuffers(window.GetWindow());
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}