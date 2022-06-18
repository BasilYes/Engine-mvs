#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <debug.h>
#include "RManager.h"
#include "RCamera.h"
#include "renderable_object/RMesh.h"
#include "stb_image.h"

#include "game/units/TestUnit.h"

RManager* RManager::m_rManager = nullptr;
GLFWwindow* RManager::m_window = nullptr;
vec2 RManager::m_windowSize{ 800, 600 };

void processInput(GLFWwindow* window)
{
    RCamera* camera = RManager::getRManager()->getActiveCamera();
    vec3 trans = vec3{};

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        trans = vec3{ 0.0f,0.01f,0.0f };
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        trans = vec3{ 0.0f,-0.01f,0.0f };
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        trans = vec3{ -0.01f,0.0f,0.0f };
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        trans = vec3{ 0.01f,0.0f,0.0f };
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        trans = vec3{ 0.0f,0.0f,0.01f };
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        trans = vec3{ 0.0f,0.0f,-0.01f };

    mat3 rotat;
    initRotateTransform(rotat, camera->getRotation());
    trans = rotat * trans;
    camera->setLocation(camera->getLocation() + trans*1.0f);


    //trans = vec3{};
    //if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    //    trans = vec3{ 0.0f,0.0f,0.01f };
    //else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    //    trans = vec3{ 0.0f,0.0f,-0.01f };
    //if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    //    trans = vec3{ 0.01f,0.0f,0.0f };
    //else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    //    trans = vec3{ -0.01f,0.0f,0.0f };
    //if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    //    trans = vec3{ 0.0f,0.01f,0.0f };
    //else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    //    trans = vec3{ 0.0f,-0.01f,0.0f };    trans = vec3{};
    trans = vec3{};
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        trans = vec3{ 0.0f,0.0f,0.01f };
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        trans = vec3{ 0.01f,0.0f,0.0f };
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        trans = vec3{ 0.0f,0.01f,0.0f };
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        trans = -trans;
    TestUnit::u->setUnitLocation(TestUnit::u->getLocation() + trans);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

    static float lastX = xpos;
    static float lastY = ypos;

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // перевернуто, так как Y-координаты идут снизу вверх

    lastX = xpos;
    lastY = ypos;

    RCamera* camera = RManager::getRManager()->getActiveCamera();
    camera->setRotation(camera->getRotation() + vec3{ yoffset * 0.01f, 0.0f, -xoffset * 0.01f});
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

void RManager::addMesh(RMesh* mesh)
{
    m_rManager->m_drawList.pushFront(mesh);
    mesh->RObject::m_selfRef = m_drawList.getFirst();
}
void RManager::addRObject(RObject* mesh)
{
    m_rManager->m_drawList.pushFront(mesh);
    mesh->RObject::m_selfRef = m_drawList.getFirst();
}

void RManager::init()
{
    ASSERT(!m_rManager, "RenderManager reinitialization")
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
}

bool RManager::drawFrame() const
{
    processInput(m_window);

    glClearColor(0.05f, 0.50f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    m_activeCamera->updateViewMatrix(this);
    LincedListItem<const RObject>* item = m_drawList.getFirst();
    while (item)
    {
        item->getContent()->draw(m_activeCamera);
        item = item->getNext();
    }



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