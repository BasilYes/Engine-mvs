#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "IManager.h"
#include "render/RManager.h"
#include "render/RCamera.h"

EEventCaller<float> IManager::moveForward{};
EEventCaller<float> IManager::moveRight{};
EEventCaller<float> IManager::moveUp{};

IManager* IManager::m_iManager;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static float lastX = xpos;
    static float lastY = ypos;

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // перевернуто, так как Y-координаты идут снизу вверх

    lastX = xpos;
    lastY = ypos;

    RCamera* camera = RManager::getRManager()->getActiveCamera();
    camera->setRotation(camera->getRotation() + vec3{ yoffset * 0.01f, 0.0f, -xoffset * 0.01f });
}

IManager::IManager()
{
}

void IManager::init()
{
	ASSERT(!m_iManager, "IManager reinitialization")
	m_iManager = new IManager{};
    glfwSetCursorPosCallback(RManager::getWindow(), mouse_callback);
}

void IManager::processInput()
{
    GLFWwindow* window = RManager::getWindow();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        moveForward.call(1.0f);
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        moveForward.call(-1.0f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        moveRight.call(1.0f);
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        moveRight.call(-1.0f);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        moveUp.call(1.0f);
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        moveUp.call(-1.0f);


    //GLFWwindow* window = RManager::getWindow();
    //RCamera* camera = RManager::getRManager()->getActiveCamera();
    //vec3 trans = vec3{};

    //if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    //    glfwSetWindowShouldClose(window, true);
    //if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //    trans = vec3{ 0.0f,0.01f,0.0f };
    //else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //    trans = vec3{ 0.0f,-0.01f,0.0f };
    //if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //    trans = vec3{ -0.01f,0.0f,0.0f };
    //else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //    trans = vec3{ 0.01f,0.0f,0.0f };
    //if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    //    trans = vec3{ 0.0f,0.0f,0.01f };
    //else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    //    trans = vec3{ 0.0f,0.0f,-0.01f };

    //mat3 rotat;
    //initRotateTransform(rotat, camera->getRotation());
    //trans = rotat * trans;
    //camera->setLocation(camera->getLocation() + trans * 1.0f);

    //trans = vec3{};
    //if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    //    trans = vec3{ 0.0f,0.0f,0.01f };
    //if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    //    trans = vec3{ 0.01f,0.0f,0.0f };
    //if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    //    trans = vec3{ 0.0f,0.01f,0.0f };
    //if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
    //    trans = -trans;
    //TestUnit::u->setUnitLocation(TestUnit::u->getLocation() + trans);
}
