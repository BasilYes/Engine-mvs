#include "RCamera.h"

void RCamera::initViewMatrix(mat4& mat)
{
    mat3 rotate;
    initRotateTransform(rotate, getRotation());
    vec3 front = rotate * vec3{ 0.0f, 0.0f, 1.0f };
    vec3 right = rotate * vec3{ -1.0f, 0.0f, 0.0f };
    vec3 up = cross(right, front);
    mat4 lookAtDerection;
    initLookDirection(lookAtDerection, up, right, front);
    mat4 lookAtTranslation;
    initTranslationTransform(lookAtTranslation, -getLocation());
    mat = lookAtDerection* lookAtTranslation;
}