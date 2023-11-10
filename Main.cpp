#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <mutex>
#include <list>

#include <SDL/SDL.h>
#include <GLM/glm.hpp>

#include "Scene.h"
#include "Ray.h"
#include "Sphere.h"
#include "RayTracer.h"
#include "Camera.h"

/*
*	NOTE FROM DEVELOPER:
*	
*	I had issues utilising SDL as the main function was not being recognised.
*	The way I came around this was by doing some research on StackOverflow, as 
*	other people had similar issues. They all suggested that I utilise the undef
*	function to undef the main function and this resulted in my program being able
*	to run SDL smoothly.
*/
#undef main

int noOfThreads = 1;
int input;
int win_x = 600;
int win_y = 480;

std::mutex mtx;

void runProgram()
{
	/*
	*	To begin with, we create shared pointers for our scene, ray tracer and camera classes. This makes
	*	it easier for us to access our various functions
	*/
	//mtx.lock();
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	std::shared_ptr<RayTracer> rayTracer = std::make_shared<RayTracer>();
	std::shared_ptr<Camera> camera = std::make_shared<Camera>();

	/*
	*	Creates the spheres to the scene by allocating their colours as well as their positions in a shared pointer
	*/
	std::shared_ptr<Sphere> s1 = std::make_shared<Sphere>(glm::vec3(0.0f, 4.0f, -20), 2, glm::vec3(0.75f, 1.0f, 0.75f));
	std::shared_ptr<Sphere> s2 = std::make_shared<Sphere>(glm::vec3(2.5f, 5.0f, -15), 1, glm::vec3(0.85f, 0, 0.25f));
	std::shared_ptr<Sphere> s3 = std::make_shared<Sphere>(glm::vec3(-0.9f, 1.04f, -15), 1.5, glm::vec3(0.25f, 0.4, 0.22f));
	std::shared_ptr<Sphere> s4 = std::make_shared<Sphere>(glm::vec3(-3.3f, 4.5f, -23), 2, glm::vec3(0.01f, 0.40f, 1.0f));
	/*
	*	Creates the sphere by referencing the addSphere function created in our RayTracer class
	*/
	rayTracer->addSphere(s1);
	rayTracer->addSphere(s2);
	rayTracer->addSphere(s3);
	rayTracer->addSphere(s4);
	//mtx.unlock();

	bool running = true;
	bool finished = false;

	if (!finished)
	{
		/*
		*	This starts the for loop to help the user start the ray tracing
		*	process and see how long it takes to run. Once the loop has started
		*	it calls the camera to create the ray. The colour is all set to 1.0f
		*	and the trace function uses our ray and colour to display our final
		*	product.
		*
		*	Once this has been completed the draw pixel is called, utilising glm::clamp
		*	to get the colour and position all together.
		*
		*	Our scene then displays the pixel onto the screen, ideally showcasing the finished
		*	ray trace. Our boolean for the finished is set to true as well, so our program knows
		*	that we do not have to render more than one item.
		*/

		for (int y = 0; y < 800; y++)
		{
			for (int x = 0; x < 600; x++)
			{
				Ray ray = camera->createRay(glm::vec3(x, y, 0));

				glm::vec3 colour = glm::vec3(1.0f, 1.0f, 1.0f);

				rayTracer->trace(ray, colour);

				colour.x *= 255;
				colour.y *= 255;
				colour.z *= 255;


				/*
				*	Here is the code to determine whether or not my raytracer is going to be multithreaded.
				*	I use a simple if statement that relies on the number input that the user uses when the 
				*	program is first opened.
				* 
				*	If the user selects 1, the program is run using a single thread. If the user selects the 
				*	second option, the user inputs the amount of threads that they want to use. The threads are
				*	then stored in a list, which uses a for loop to create an emplace, which inserts a new task.
				*	This will keep on occuring until the tasks reaches the same number of threads that the user 
				*	enters.
				* 
				*	When that has been completed the final product displays on the screen.
				*/
				if (noOfThreads == 1)
				{
					scene->DrawPixel(x, y, glm::clamp(colour, glm::vec3(0, 0, 0), glm::vec3(255, 255, 255)));
				}

				else if (noOfThreads <= std::thread::hardware_concurrency())
				{
				    std::list<std::thread> threads;
					std::thread thread;

					for (int i = 0; i < noOfThreads; i++)
					{
						 threads.emplace_back([=]
							{
									i, & Scene::DrawPixel;
									scene->DrawPixel(x, y, glm::clamp(colour, glm::vec3(0, 0, 0), glm::vec3(255, 255, 255)));
								
							}
						);
						
						//scene->DrawPixel(x, y, glm::clamp(colour, glm::vec3(0, 0, 0), glm::vec3(255, 255, 255)));
						
					}

					for (auto iter = threads.begin(); iter != threads.end(); iter++)
					{
						iter->join();
					}
					
				}
			}

			scene->Display();
			finished = true;
		}
	}

	/*
	*	This is our SDL_Event which records the key binds and allows the user to quit the application
	*	safely. This calls our cleanup function and changes running to false to stop it from working
	*/
	while (running)
	{
		SDL_Event e = { 0 };

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
				scene->Clean();
			}
		}
	}
}

void quit()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	scene->Clean();
}

int main(int argc, char** argv[])
{
	/*
	*	Here is our startup. When the program is first run, we are greeted by a set of options. Those options include:
	*	1) Running the normal single threaded program
	*	2) Editing the number of threads that we are using
	*	3) Exiting the program completely
	*/
	std::cout << "Press 1 to start the program" << std::endl;
	std::cout << "Press 2 to edit the number of threads" << std::endl;
	std::cout << "Press 3 to quit" << std::endl;
	std::cin >> input;
	
	if (input == 1)
	{
		runProgram();
	}

	else if (input == 2)
	{
		std::cout << "Enter new number of threads (" << std::thread::hardware_concurrency() << " logical processors available): ";
		std::cin >> noOfThreads;
		runProgram();
	}

	else if (input == 3)
	{
		quit();
	}

	return 0;
}
