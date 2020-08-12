// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"

nc::Engine engine;
nc::GameObject player;

namespace nc
{
	using clock = std::chrono::high_resolution_clock;
	using clock_duration = std::chrono::duration<clock::rep, std::nano>;
}

int main(int, char**)
{
	engine.Startup();

	player.Create(&engine);
	player.m_transform.position = { 400, 300 };
	player.m_transform.angle = 45;

	nc::Component* component;
	component = new nc::PhysicComponent;
	player.AddComponent(component);
	component->Create();

	component = new nc::SpriteComponent;
	player.AddComponent(component);
	component->Create();

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	IMG_Quit();

	nc::Texture* background = engine.GetSystem<nc::ResourceManager>()->Get<nc::Texture>("background.png", engine.GetSystem<nc::Renderer>());

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
		engine.Update();
		player.Update();

		//quit = (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESC) == nc::InputSystem::eButtonState::HELD)

		//player controller

		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystem::eButtonState::HELD)
		{
			player.m_transform.angle = player.m_transform.angle - 200.0f * engine.GetTimer().DeltaTime();
		}
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystem::eButtonState::HELD)
		{
			player.m_transform.angle = player.m_transform.angle + 200.0f * engine.GetTimer().DeltaTime();
		}

		nc::Vector2 force{ 0,0 };
		if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_UP) == nc::InputSystem::eButtonState::HELD)
		{
			force = nc::Vector2::forward * 1000.0f;
		}
		force = nc::Vector2::Rotate(force, nc::DegreesToRadians(player.m_transform.angle));

		//draw
		engine.GetSystem<nc::Renderer>()->BeginFrame();
		background->Draw({0, 0});

		player.Draw();

		engine.GetSystem<nc::Renderer>()->EndFrame();
	}

	engine.Shutdown();

	return 0;
}
