#include "RayTracer.h"
#include "Sphere.h"
#include "Ray.h"
#include "Geometry.h"
/*
*	The constructor class for the ray tracer
*/
RayTracer::RayTracer()
{
	_geometry = std::make_shared<Geometry>();
}

/*
*	This calculates the colours of the ray when the sphere hits it.
*	It creates the reflections
*/
void RayTracer::trace(Ray _ray, glm::vec3& colour)
{
	float distance = 10000000;

	/*
	*	This is worked out in a for loop determining the spheres end 
	*	and start points
	*/
	for (std::list<std::shared_ptr<Sphere>>::iterator iter = _spheres.begin();
		iter != _spheres.end(); iter++)
	{
		/*
		*	This tells us that the response (which is where the ray 
		*	has been intersected) is equal to the sphere's intersect
		*	point.
		*/
		IntersectData response = _geometry->sphereIntersection(_ray, (*iter));
		/*
		*	Tells us if the response has been hit, what to do
		*/
		if (response._hit)
		{
			/*
			*	This sets the colour to be 0, 0, 0 is the ray is a 
			*	shadow and returns it.
			*/
			if (_ray.isShadow)
			{
				colour = glm::vec3(0, 0, 0);
				return;
			}
			/*
			*	This tells us if the responses' distance is less than the
			*	distance we gave earlier what to do.
			*/
			if (response._distance < distance)
			{
				/*
				*	The distance is set to be equal to the response's distance
				*/
				distance = response._distance;

				/*
				*	The ray's primary is worked out and if it is primary
				*	the colour is equal to the iter's point being the 
				*	shader.
				* 
				*	Else, the colour is added onto the same equation but
				*	times by 1.
				*/
				if (_ray.isPrimary)

					colour = (*iter)->shadow(_ray, response._intersectPoint);
				else
					colour += ((*iter)->shadow(_ray, response._intersectPoint) * 1.0f);

				if (_ray.isPrimary)
				{
					/*
					*	This works out the surface normal, the light direction and 
					*	the reflection direction of the ray
					*/
					glm::vec3 surfaceNorm = (response._intersectPoint - (*iter)->currentPosition()) / (*iter)->currentRadius();
					glm::vec3 lightDir = glm::normalize(glm::vec3(100, 100, 250) - response._intersectPoint);
					glm::vec3 reflectDir = glm::reflect(_ray.currentDirection(), surfaceNorm);
					
					/*
					*	This sets the reflection of the ray's direction, origin and 
					*	the primary is then set to 0.
					*/
					Ray _reflectRay;
					_reflectRay.directionSet(reflectDir);
					_reflectRay.originSet(response._intersectPoint + surfaceNorm * 0.01f);
					_reflectRay.isPrimary = false;

					/*
					*	This sets the trace ray's colour and reflect
					*/
					trace(_reflectRay, colour);

					/*
					*	This creates a shadow ray and sets the shadow to be true
					*/
					Ray _shadow;
					_shadow.directionSet(lightDir);
					_shadow.originSet(response._intersectPoint + surfaceNorm * 0.01f);
					_shadow.isPrimary = false;
					_shadow.isShadow = true;
					trace(_shadow, colour);
				}
				
			}
		}
	}
}

/*
*	Creates the sphere itself
*/
void RayTracer::addSphere(std::shared_ptr<Sphere> _sphere)
{
	_spheres.push_back(_sphere);
}