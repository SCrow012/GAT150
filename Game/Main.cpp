// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Graphics/Texture.h"
#include "Objects/GameObject.h"
#include "Components/PlayerComponents.h"
#include "Components/EnemyComponent.h"
#include "Core/JSON.h"
#include "Objects/ObjectFactory.h"
#include "Objects/Scene.h"
#include "TileMap.h"

nc::Engine engine;
nc::Scene scene;

int main(int, char**)
{
	scene.Create(&engine);
	engine.Startup();

	nc::ObjectFactory::Instance().Initialize();
	nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object>);
	nc::ObjectFactory::Instance().Register("EnemyComponent", new nc::Creator<nc::EnemyComponent, nc::Object>);

	rapidjson::Document document;
	nc::json::Load("scene.txt", document);
	scene.Read(document);

	nc::TileMap tileMap;
	nc::json::Load("tilemap.txt", document);
	scene.Create(&engine);
	tileMap.Read(document);
	tileMap.Create(&scene);

	//for (size_t i = 0; i < 10; i++)
	//{
	//	nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<nc::GameObject>("ProtoCoin");
	//	gameObject->m_transform.position = { nc::random(0, 800), nc::random(300, 450) };
	//	//gameObject->m_transform.angle = nc::random(0, 360);
	//	
	//	scene.AddGameObject(gameObject);
	//}

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
		scene.Update();

		//quit = (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESC) == nc::InputSystem::eButtonState::PRESSED)
		//	if (engine.GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_ESC) == nc::InputSystem::eButtonState::PRESSED)
		//	{
		//		quit = true;
		//	}

		
		//draw
		engine.GetSystem<nc::Renderer>()->BeginFrame();
		scene.Draw();

		engine.GetSystem<nc::Renderer>()->EndFrame();
	}

	scene.Destroy();
	engine.Shutdown();

	return 0;
}

//// json
	//rapidjson::Document document;
	//nc::json::Load("json.txt", document);
	//std::string str;
	//nc::json::Get(document, "string", str);
	//std::cout << str << std::endl;
	//bool b;
	//nc::json::Get(document, "bool", b);
	//std::cout << b << std::endl;
	//int i1;
	//nc::json::Get(document, "integer1", i1);
	//std::cout << i1 << std::endl;
	//int i2;
	//nc::json::Get(document, "integer2", i2);
	//std::cout << i2 << std::endl;
	//float f;
	//nc::json::Get(document, "float", f);
	//std::cout << f << std::endl;
	//nc::Vector2 v2;
	//nc::json::Get(document, "vector2", v2);
	//std::cout << v2 << std::endl;
	//nc::Color color;
	//nc::json::Get(document, "color", color);
	//std::cout << color << std::endl;