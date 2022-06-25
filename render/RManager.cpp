#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <debug.h>
#include "stb_image.h"

#include "RManager.h"

#include "RCamera.h"
#include "render/RInstance.h"

RManager* RManager::m_rManager = nullptr;
GLFWwindow* RManager::m_window = nullptr;
vec2 RManager::m_windowSize{ 1600, 900 };

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    RManager::setWindowSize(vec2{ (float)width, (float)height });
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
    ASSERT(!m_rManager, "RManager reinitialization")
    initGLFW();

    m_rManager = new RManager();
    m_rManager->createWindow();

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ERROR("Failed to initialize GLAD")
    }

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

bool RManager::drawFrame() const
{
    glClearColor(224.0f/256.0f, 255.0f/256.0f, 255.0f/256.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    LincedListItem<const RInstance>* item = m_instanceList.getFirst();
    while (item)
    {
        item->getContent()->draw(m_activeCamera);
        item = item->getNext();
    }



    glfwSwapBuffers(m_window);
    glfwPollEvents();
    return !glfwWindowShouldClose(m_window);
}

RInstance* RManager::addRInstance(LevelInstance* ownLInstance)
{
    RInstance* instance = new RInstance(ownLInstance);
    m_instanceList.pushFront(instance);
    instance->m_selfRef = m_instanceList.getFirst();
    return instance;
}

RManager::RManager()
{
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