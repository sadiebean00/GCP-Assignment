#include "Geometry.h"
#include "Sphere.h"
#include "Ray.h"

//Constructor class for Geometry, which will remain empty
Geometry::Geometry()
{

}

/*
*	The calculation uses to find the intersect point in order
*	for the ray tracer to work
*/

IntersectData Geometry::currentIntersectionPoint(Ray _ray, std::shared_ptr<Sphere> _sphere)
{
	IntersectData rtn;

	/*
	*	Calculates the distance to the centre by taking the ray's origin 
	*	by the sphere's position
	*/
	float DistanceToCentre = glm::length(_ray.currentOrigin() - _sphere->currentPosition());
	
	/*
	*	Tells the intersect data will be false if the distance to the 
	*	centre is less than or equal to the sphere's radius
	*/
	if (DistanceToCentre <= _sphere->currentRadius())
	{
		rtn._hit = false;
		return rtn;
	}

	/*
	*	Sets the vec a and p by either;
	*	a)
	*		the origin is minused by a vec 3 set at 0
	*	p)
	*		the position is minused by a vec set at 0
	*/
	glm::vec3 a = _ray.currentOrigin() - glm::vec3(0, 0, 0);
	glm::vec3 p = _sphere->currentPosition() - glm::vec3(0, 0, 0);

	/*
	*	The ray direction is set as the normalised direction of
	*	the ray
	*/
	glm::vec3 rayDir = glm::normalize(_ray.currentDirection());

	/*
	*	Works out the closest points on the line by using a dot product
	*	method
	*/
	glm::vec3 closestPointOnLine = a + (glm::dot((p - a), rayDir) * rayDir);

	float pointToLine = glm::length(p - closestPointOnLine);

	/*
	*	This if statement looks for the point to line and sees whether
	*	it is greater than the sphere's radius. If it is, the rtn hit
	*	is false.
	*/
	if (pointToLine > _sphere->currentRadius())
	{
		rtn._hit = false;
		return rtn;
	}

	rtn._hit = true;

	/*
	*	Works out the intersect distance by squaring the calculation that 
	*	comes from the total product of the sphere's radius multiplied
	*	by the sphere's radius and the point to the line times by itself.
	*	The two are then taken away from each other to get the number 
	*	needed in order for the square route function to work
	*/
	float IntersectDistance = glm::sqrt((_sphere->currentRadius() * _sphere->currentRadius()) - (pointToLine * pointToLine));
	/*
	*	The temporary distance is worked out through the dot product of p
	*	minus a followed by the ray's distance. We then minus this result
	*	by the intersect's distance
	*/
	float temporaryDistance = (glm::dot((p - a), rayDir) - IntersectDistance);
	/*
	*	The if statement tells us that if the temporary distance is less
	*	than 0, then the ray hasn't hit the sphere.
	*/
	if (temporaryDistance < 0)
	{
		rtn._hit = false;
		return rtn;
	}

	/*
	*	The intersect point of the data is worked out through a being
	*	added with the temporary distance and then multiplied by the 
	*	ray's direction
	*/
	rtn._intersectPoint = a + temporaryDistance * rayDir;
	
	/*
	*	The distance is then worked out with the length of the ray's
	*	origin point being taken away by the intersect point
	*/
	rtn._distance = glm::length(_ray.currentOrigin() - rtn._intersectPoint);

	return rtn;
}

IntersectData Geometry::sphereIntersection(Ray _ray, std::shared_ptr<Sphere> _sphere)
{
	return currentIntersectionPoint(_ray, _sphere);
}