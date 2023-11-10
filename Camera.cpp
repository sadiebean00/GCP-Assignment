#include "Ray.h"
#include "Camera.h"

/*
*	Constructor class for the camera
*/
Camera::Camera()
{
	_projection = glm::perspective(glm::radians(45.0f), 3.0f / 4.0f, 0.1f, 100.f);
	_view = glm::mat4(1);
}

/*
*	Creates the ray
*/
Ray Camera::createRay(glm::vec3 _position)
{
	/*
	*	Works out the origin point for each of the coordinates
	*/
	glm::vec4 _origin;
	_origin.x = (_position.x / (600.0f / 2.0f)) - 1;
	_origin.y = -((_position.y / (800.0f / 2.0f)) - 1);
	_origin.z = -1;
	_origin.w = 1;

	/*
	*	Works out the destination point for each of the coordinates
	*/
	glm::vec4 _destination;
	_destination.x = (_position.x / (600.0f / 2.0f)) - 1;
	_destination.y = -((_position.y / (800.0f / 2.0f)) - 1);
	_destination.z = 1;
	_destination.w = 1;

	/*
	*	The origin and destination are then inversed to get the new origin and destination points to work from
	*/
	_origin = glm::inverse(_projection) * _origin;
	_destination = glm::inverse(_projection) * _destination;

	/*
	*	We then set the origin and destination to be at the width of the original origin and destination
	*/
	_origin /= _origin.w;
	_destination /= _destination.w;

	/*
	*	We then inverse again to get a new origin and destination
	*/
	_origin = glm::inverse(_view) * _origin;
	_destination = glm::inverse(_view) * _destination;

	/*
	*	Uses a reference from the ray class, which we have adeptly named _ray
	*/
	Ray _ray;
	/*
	*	Sets the origin point of the ray
	*/
	_ray.originSet(glm::vec3(_origin));

	glm::vec3 _direction = glm::normalize(-glm::vec3(_origin) + glm::vec3(_destination));

	_ray.directionSet(_direction);

	return _ray;
}