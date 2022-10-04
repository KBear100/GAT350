#include "Engine.h" 
#include <iostream> 

int main()
{
	Bear::InitializeMemory();

	Bear::Engine::Instance().Initialize();
	Bear::Engine::Instance().Register();

	Bear::g_renderer.CreateWindow("Neumont", 800, 600);

	bool quit = false;
	while (!quit)
	{
		Bear::Engine::Instance().Update();

		if (Bear::g_inputSystem.GetKeyState(Bear::key_escape) == Bear::InputSystem::KeyState::Pressed) quit = true;

		Bear::g_renderer.BeginFrame();
		Bear::g_renderer.EndFrame();
	}

	Bear::Engine::Instance().Shutdown();
}