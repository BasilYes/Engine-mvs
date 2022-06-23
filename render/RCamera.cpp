#include "RCamera.h"
#include "RManager.h"

void RCamera::updateViewMatrix(vec3 location, vec3 rotation)
{
    mat3 rotate;
    initRotateTransform(rotate, rotation);
    vec3 front = rotate * vec3{ 0.0f, 1.0f, 0.0f };
    vec3 right = rotate * vec3{ 1.0f, 0.0f, 0.0f };
    vec3 up = cross(right, front);
    mat4 lookAtDerection;
    initLookDirection(lookAtDerection, up, right, front);
    mat4 lookAtTranslation;
    initTranslationTransform(lookAtTranslation, -location);
    mat4 perspectiveProjection;
    initPersProjTransform(perspectiveProjection, 3.14f * 0.5f, RManager::getWindowSize()[0], RManager::getWindowSize()[1], 0.01f, 1000.0f);
    m_viewMatrix = perspectiveProjection * lookAtDerection * lookAtTranslation;
}