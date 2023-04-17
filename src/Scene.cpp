#include "Scene.hpp"
#include <p6/p6.h>
#include "Boid.hpp"
#include "imgui.h"


Scene::Scene(const p6::Context& ctx) {
    _borders = WindowLimits();
    updateBorders(ctx);

    _simulationParams = SimulationParams();
    _behaviors = Behaviors();

    _boids = createBoids(_simulationParams, _borders); 
}

void Scene::updateBorders(const p6::Context& ctx) {
    _borders = { 
        .top = 1 - 0.2f,
        .bottom = -1 + 0.2f,
        .left = -ctx.aspect_ratio() + 0.2f,
        .right = ctx.aspect_ratio() - 0.2f
    };
}

void Scene::createWindow() {
    ImGui::Begin("Simulation Parameters");
    ImGui::SliderFloat("Protected Area", &_simulationParams.protectedArea, 0.1f, 0.5f);
    ImGui::SliderFloat("Visual Area", &_simulationParams.visualArea, 0.5f, 1.f);
    ImGui::SliderFloat("Max Speed", &_simulationParams.maxSpeed, 0.1f, 0.9f);
    ImGui::Checkbox("Separation", &_behaviors.separation);
    ImGui::Checkbox("Allignment", &_behaviors.allignment);
    ImGui::Checkbox("Cohesion", &_behaviors.cohesion);    
    ImGui::End();
}

void Scene::runBoids(p6::Context& ctx) {
    for (Boid& boid : _boids) {
        boid.draw(ctx); 
        boid.move(_boids, _simulationParams, _borders, _behaviors);        
    }
}

void Scene::update(p6::Context& ctx) {
    updateBorders(ctx);
    createWindow();
    runBoids(ctx);
}