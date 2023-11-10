#pragma once

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

class Ray;

/*
*	Creates a camera class to handle the rays, as well as the view and projection matrices
*	
*	When we create the rays, we figure out the origin points for the coordinates as well as
*	the destination points. Finally, we will call the Ray class and initiate the ray tracer
*	as the Camera class will set the origin point for the ray tracer.
*/
class Camera
{
public:
	Camera();

	Ray createRay(glm::vec3 _position);
	unsigned int noOfThreads = 1;

private:
	glm::mat4 _projection;
	glm::mat4 _view;
};