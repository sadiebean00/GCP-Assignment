#pragma once

#include <GLM/glm.hpp>

/*
*	Ray class created to store the ray's data. It gets the 
*	origin and direction of the ray. The class also holds the
*	vec3 for the ray's current origin and direction.
* 
*	We also have two booleans within this class to set the primary ray
*	as well as figuring whether there are shadows within the ray especially
*	if we have more than one sphere in the scene.
*/

class Ray
{
public:
	Ray();

	void directionSet(glm::vec3 direction);
	void originSet(glm::vec3 origin);

	glm::vec3 currentOrigin();
	glm::vec3 currentDirection();

	bool isPrimary;
	bool isShadow;

private:
	glm::vec3 _direction;
	glm::vec3 _origin;
};