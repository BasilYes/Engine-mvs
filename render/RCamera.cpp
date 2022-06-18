#include "RCamera.h"
#include "RManager.h"

void RCamera::updateViewMatrix(const RManager* manager)
{
    mat3 rotate;
    initRotateTransform(rotate, getRotation());
    vec3 front = rotate * vec3{ 0.0f, 1.0f, 0.0f };
    vec3 right = rotate * vec3{ 1.0f, 0.0f, 0.0f };
    vec3 up = cross(right, front);
    mat4 lookAtDerection;
    initLookDirection(lookAtDerection, up, right, front);
    mat4 lookAtTranslation;
    initTranslationTransform(lookAtTranslation, -getLocation());
    mat4 perspectiveProjection;
    initPersProjTransform(perspectiveProjection, 3.14f * 0.5f, manager->getWindowSize()[0], manager->getWindowSize()[1], 0.01f, 100.0f);
    m_viewMatrix = perspectiveProjection * lookAtDerection * lookAtTranslation;
}