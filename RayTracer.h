#pragma once

#include <GLM/glm.hpp>
#include <list>
#include <memory>

class Sphere;
class Ray;
class Geometry;

/*
*	This class handles the drawing of the ray tracer. We also have the drawSphere
*	function which references the sphere class's pointer that we utilise.
* 
*	Our private functions get a list and use the memory to create sphereres 
*	from the list we created from our Sphere function. We also create a 
*	geometry shared pointer to reference in this class.
*/

class RayTracer
{
public:
	RayTracer();

	void trace(Ray _ray, glm::vec3& colour);
	void addSphere(std::shared_ptr<Sphere> _sphere);

private:
	std::list<std::shared_ptr<Sphere>> _spheres;
	std::shared_ptr<Geometry> _geometry;
};