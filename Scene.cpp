#include "Scene.h"
#include <iostream>

#define SCREEN_W 600
#define SCREEN_H 480

/*
*	Constructor for Scene
*/
Scene::Scene()
{
	/*
	*	Creates the SDL window and checks for errors in getting it to load
	*/
	//mtx.lock();
	window = SDL_CreateWindow("Ray Tracer GFX", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_RESIZABLE);

	if (!window)
	{
		std::cout << "SDL Failed to create window" << std::endl;
	}

	/*
	*	Creates the SDL renderer and checks for errors in getting it to load
	*/
	renderer = SDL_CreateRenderer(window, -1, 0);
	

	if (!renderer)
	{
		std::cout << "SDL Failed to create renderer" << std::endl;
	}
	//mtx.unlock();
}

/*
*	Creates the deconstructor
*/
Scene::~Scene()
{

}

void Scene::DrawPixel(int x, int y, glm::vec3 col)
{
	/*
	*	Sets the draw colour for the pixel and proceeds to draw the point
	*/
	mtx.lock();
	SDL_SetRenderDrawColor(renderer, col.x, col.y, col.z, 255);
	SDL_RenderDrawPoint(renderer, x, y);
	mtx.unlock();
}

void Scene::Display()
{
	/*
	*	Shows the window with the completed render and spheres (added in the main.cpp)
	*/
	SDL_RenderPresent(renderer);
}

void Scene::Clean()
{
	/*
	*	Destroys the SDL window and cleans up any leftover functions
	*/
	SDL_DestroyWindow(window);
	SDL_Quit();
}