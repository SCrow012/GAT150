// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Input/InputSystem.h"
#include "Core/Timer.h"
#include "Math/Math2.h"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <chrono>

nc::Renderer renderer;
nc::ResourceManager resourceManager;
nc::InputSystem inputSystem;
nc::FrameTimer timer;

namespace nc
{
	using clock = std::chrono::high_resolution_clock;
	using clock_duration = std::chrono::duration<clock::rep, std::nano>;
}


int main(int, char**)
{
	//nc::clock::time_point start = nc::clock::now();
	//for (size_t i = 0; i < 100; i++)
	//{
	//	std::sqrt(rand() % 100);
	//}
	//nc::clock_duration duration = nc::clock::now() - start;
	//std::cout << duration.count() << std::endl;
	//std::cout << timer.ElapsedSeconds();

	renderer.Startup();
	resourceManager.Startup();
	inputSystem.Startup();

	renderer.Create("GAT150", 800, 600);

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	IMG_Quit();

	nc::Texture* background = resourceManager.Get<nc::Texture>("background.png", &renderer);
	nc::Texture* car = resourceManager.Get<nc::Texture>("cars.png", &renderer);

	float angle{ 0 };
	nc::Vector2 position{ 400, 300 };
	nc::Vector2 velocity{ 0, 0 };

	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		// update
		timer.Tick();
		resourceManager.Update();
		inputSystem.Update();

		//player controller

		if (inputSystem.GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystem::eButtonState::HELD)
		{
			angle = angle - 200.0f * timer.DeltaTime();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystem::eButtonState::HELD)
		{
			angle = angle + 200.0f * timer.DeltaTime();
		}

		nc::Vector2 force{ 0,0 };
		if (inputSystem.GetButtonState(SDL_SCANCODE_UP) == nc::InputSystem::eButtonState::HELD)
		{
			force = nc::Vector2::forward * 1000.0f;
		}
		force = nc::Vector2::Rotate(force, nc::DegreesToRadians(angle));

		// physics
		velocity = velocity + force * timer.DeltaTime();
		velocity = velocity * 0.95f;
		position = position + velocity * timer.DeltaTime();

		//draw
		renderer.BeginFrame();
		background->Draw({0, 0});

		//player sprite draw
		car->Draw({ 0, 16, 64, 144 }, position, { 1, 1 }, angle);

		renderer.EndFrame();
	}

	resourceManager.Shutdown();
	inputSystem.Shutdown();
	SDL_Quit();

	return 0;
}
