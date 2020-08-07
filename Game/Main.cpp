// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Input/InputSystem.h"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

nc::Renderer renderer;
nc::ResourceManager resourceManager;
nc::InputSystem inputSystem;

int main(int, char**)
{
	renderer.Startup();
	resourceManager.Startup();
	inputSystem.Startup();

	renderer.Create("GAT150", 800, 600);

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	IMG_Quit();

	nc::Texture* texture1 = resourceManager.Get<nc::Texture>("sf2.png", &renderer);
	nc::Texture* texture2 = resourceManager.Get<nc::Texture>("sf2.png", &renderer);

	float angle{ 0 };
	nc::Vector2 position{ 400, 300 };

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

		resourceManager.Update();
		inputSystem.Update();

		// Begin Frame
		renderer.BeginFrame();
		//draw
		angle = angle + 1;
		texture1->Draw(position, { 1, 1 }, angle);

		if (inputSystem.GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystem::eButtonState::HELD)
		{
			position.x = position.x - 1.0f;
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystem::eButtonState::HELD)
		{
			position.x = position.x + 1.0f;
		}


		texture2->Draw({ 200, 400 }, { 2, 2 }, angle + 90);

		// End Frame
		renderer.EndFrame();
	}

	resourceManager.Shutdown();
	inputSystem.Shutdown();
	SDL_Quit();

	return 0;
}
