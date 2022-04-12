#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <debug.h>
#include "RManager.h"
#include "RCamera.h"
#include "renderable_object/Mesh.h"
#include "stb_image.h"

RManager* RManager::m_rManager = nullptr;
GLFWwindow* RManager::m_window = nullptr;
vec2 RManager::m_windowSize{ 800, 600 };

static Mesh* mesh;
static Mesh* mesh2;

void processInput(GLFWwindow* window)
{
    RCamera* camera = RManager::getRManager()->getActiveCamera();
    vec3 trans = vec3{};

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        trans += vec3{ 0.0f,0.0f,0.01f };
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        trans += vec3{ 0.0f,0.0f,-0.01f };
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        trans += vec3{ 0.01f,0.0f,0.0f };
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        trans += vec3{ -0.01f,0.0f,0.0f };
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        trans += vec3{ 0.0f,0.01f,0.0f };
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        trans += vec3{ 0.0f,-0.01f,0.0f };

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        mesh->setRotation(mesh->getRotation() + vec3{ 0.0f, 0.0f,0.01f });
    else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        mesh->setRotation(mesh->getRotation() + vec3{ 0.0f, 0.0f,-0.01f });

    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        mesh->setLocation(mesh->getLocation() + vec3{ 0.0f, 0.0f,0.01f });
    else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        mesh->setLocation(mesh->getLocation() + vec3{ 0.0f, 0.0f,-0.01f });

    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        mesh->setScale(mesh->getScale() + vec3{ 0.0f, 0.0f,0.01f });
    else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        mesh->setScale(mesh->getScale() + vec3{ 0.0f, 0.0f,-0.01f });

    mat3 rotat;
    initRotateTransform(rotat, camera->getRotation());
    trans = rotat * trans;
    camera->setLocation(camera->getLocation() + trans);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

    static float lastX = xpos;
    static float lastY = ypos;

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // �����������, ��� ��� Y-���������� ���� ����� �����

    lastX = xpos;
    lastY = ypos;

    RCamera* camera = RManager::getRManager()->getActiveCamera();
    camera->setRotation(camera->getRotation() + vec3{ -yoffset * 0.01f, xoffset * 0.01f, 0.0f });
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void initGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void RManager::init()
{
    if (m_rManager)
        ERROR("RenderManager reinitialization")
    initGLFW();

    m_rManager = new RManager();
    m_rManager->createWindow();

    glfwSetCursorPosCallback(m_window, mouse_callback);

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ERROR("Failed to initialize GLAD")
    }

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    ////////
    mesh = new Mesh{ Transform{vec3{},vec3{}, vec3{1.0f,1.0f,1.0f}} , 0, 0 };
    mesh2 = new Mesh{ Transform{vec3{},vec3{}, vec3{1.0f,1.0f,1.0f}} , 0, 0 };
    ////////
}

bool RManager::drawFrame()
{
    processInput(m_window);

    glClearColor(0.05f, 0.50f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    mat4 proj, view, cam;
    initPersProjTransform(proj, 3.14f * 0.5f, m_windowSize[0], m_windowSize[1], 0.01f, 100.0f);
    getRManager()->m_activeCamera->initViewMatrix(view);
    mesh->Draw(view, proj);
    mesh2->Draw(view, proj);



    glfwSwapBuffers(m_window);
    glfwPollEvents();
    return !glfwWindowShouldClose(m_window);
}

RManager::RManager()
{
    m_activeCamera = new RCamera(Transform{});
}

RManager::~RManager()
{
    if (this == m_rManager)
        glfwTerminate();
}

void RManager::createWindow()
{
    m_window = glfwCreateWindow(m_rManager->getWindowSize()[0], m_rManager->getWindowSize()[1], "Window", NULL, NULL);
    if (m_window == nullptr)
    {
        glfwTerminate();
        ERROR("Failed to create GLFW window")
    }
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
}