#include "Engine.h" 
#include <iostream> 

int main(int argc, char** argv)
{
	Bear::InitializeMemory();

	Bear::Engine::Instance().Initialize();
	Bear::Engine::Instance().Register();

	Bear::g_renderer.CreateWindow("Neumont", 800, 600, false);

	bool quit = false;
	while (!quit)
	{
		Bear::Engine::Instance().Update();

		if (Bear::g_inputSystem.GetKeyState(Bear::key_escape) == Bear::InputSystem::KeyState::Pressed) quit = true;

		Bear::g_renderer.BeginFrame();

		glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.5f, -0.5f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0.0f, 0.5f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(0.5f, -0.5f);

		glEnd();

		Bear::g_renderer.EndFrame();
	}

	Bear::Engine::Instance().Shutdown();
	return 0;
}