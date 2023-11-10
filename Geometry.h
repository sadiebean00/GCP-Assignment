#pragma once

#include <GLM/glm.hpp>
#include <memory>

/*
*	Created a struct to hold all of the intersection data
*	for the ray tracer.
*/

struct IntersectData
{
	bool _hit;
	float _distance;
	glm::vec3 _intersectPoint;
};

/*
*	References the Ray and Sphere classes
*/

class Ray;
class Sphere;

/*
*	Created a class to handle all of the geometry for the 
*	intersections of the ray tracer.
*/

class Geometry
{
public:
	Geometry();

	IntersectData sphereIntersection(Ray _ray, std::shared_ptr<Sphere> _sphere);
	IntersectData currentIntersectionPoint(Ray _ray, std::shared_ptr<Sphere> _sphere);
};