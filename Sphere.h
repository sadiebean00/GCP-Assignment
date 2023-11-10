#pragma once

#include <GLM/glm.hpp>

class Ray;

/*
*	Sphere class that relies on the RayTracer class and stores
*	the data that is needed to handle the sphere element.
*/

class Sphere
{
public:
	Sphere(glm::vec3 position, int radius, glm::vec3 colour);

	glm::vec3 shadow(Ray _ray, glm::vec3 intersect);

	glm::vec3 currentPosition();
	float currentRadius();

private:
	glm::vec3 _position;
	float _radius;
	glm::vec3 _colour;
};