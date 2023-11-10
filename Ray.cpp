#include "Ray.h"

//Constructor class for the Ray
Ray::Ray()
{
	//Sets the direction of the ray
	_direction = glm::vec3(0, 0, 1);
	//Sets the primary
	isPrimary = true;
	//Sets whether there are shadows
	isShadow = false;
}

//Sets the direction to match the direction we set in the constructor
void Ray::directionSet(glm::vec3 direction)
{
	_direction = direction;
}

//Sets the origin of the ray
void Ray::originSet(glm::vec3 origin)
{
	_origin = origin;
}

glm::vec3 Ray::currentDirection()
{
	return _direction;
}

glm::vec3 Ray::currentOrigin()
{
	return _origin;
}