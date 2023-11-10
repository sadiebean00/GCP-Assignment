#include "Sphere.h"
#include "Ray.h"

/*
*	Constructor class for the sphere
*/
Sphere::Sphere(glm::vec3 position, int radius, glm::vec3 colour)
{
	this->_position = position;
	this->_radius = radius;
	this->_colour = colour;
}

/*
*	Gets the position of the sphere
*/
glm::vec3 Sphere::currentPosition()
{
	return _position;
}

/*
*	Gets the radius of the sphere
*/
float Sphere::currentRadius()
{
	return _radius;
}

/*
*	This creates the shadows
*/
glm::vec3 Sphere::shadow(Ray _ray, glm::vec3 intersect)
{
	glm::vec3 _surfaceColour = _colour;

	/*
	*	Creates the Ambient Light
	*/
	float _ambientStrength = 0.l;
	glm::vec3 _ambient = _ambientStrength * _colour;

	/*
	*	Creates the Diffuse Light
	*/
	glm::vec3 _lightPosition = glm::vec3(100, 100, 250);
	glm::vec3 _lightDir = glm::normalize(_lightPosition - intersect);
	glm::vec3 _surfaceNorm = glm::normalize((intersect - _position) / _radius);
	float _diffuse = glm::max(glm::dot(_surfaceNorm, _lightDir), 0.0f);

	/*
	*	Creates the Specular Light
	*/
	float _specularStrength = 0.5f;
	glm::vec3 _viewDirection = -_ray.currentDirection();
	glm::vec3 _reflectDirection = glm::normalize(glm::reflect(-_lightDir, _surfaceNorm));
	float _spec = glm::pow(glm::max(glm::dot(_viewDirection, _reflectDirection), 0.0f), 32);
	float _specular = _specularStrength * _spec;

	_surfaceColour = (_ambient + _diffuse + _specular) * _colour;

	return glm::clamp(_surfaceColour, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
}