#pragma once
#include <glm/glm.hpp>
struct MassPoint{
    glm::vec3  position;
    glm::vec3 velocity;
    float mass;
};

struct Spring{
    float k;
    float L;
    int p0;
    int p1;
};