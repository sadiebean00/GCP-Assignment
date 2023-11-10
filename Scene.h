/*
	This class draws the scene that we will use to draw the pixels
*/
#pragma once

#include <SDL/SDL.h>
#include "GLM/glm.hpp"
#include <iostream>
#include <string>
#include <mutex>
#include "gl.h"

struct Settings
{
	unsigned int noOfThreads = 1;
	int resolution = 1;
};

class Scene
{
public:
	Scene();
	~Scene();

	void DrawPixel(int x, int y, glm::vec3 col);
	void Display();
	void Clean();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Settings settings;
	std::mutex mtx;
};