#include "Scene1.h"
#include <glm/gtx/quaternion.hpp>
#include <imgui.h>

bool useMidpoint = false;

void Scene1::init(){
    points = {
        {{0.f, 0.f, 0.f}, {-1.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, 1.f},
        {{0.f, 2.f, 0.f}, {1.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, 1.f}
    };
    springs = {{40.f, 1.f, points[0], points[1]}};
    std::cout << "Initialized Points and Spring" << std::endl;
}

void Scene1::onDraw(Renderer &renderer){
    /*for(auto& point : points){
        renderer.drawSphere(point.position, 0.1f);
    }

    for(auto& spring : springs){
        renderer.drawLine(spring.p0.position, spring.p1.position, glm::vec3(1));
    }*/
}

void Scene1::simulateStep(){
   
}

void Scene1::onGUI(){
    
}