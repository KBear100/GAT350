#include "Engine.h"

namespace Bear
{
	InputSystem g_inputSystem;
	Renderer g_renderer;
	Time g_time;
	AudioSystem g_audioSystem;
	ResourceManager g_resources;
	PhysicsSystem g_physicsSystem;
	EventManager g_eventManager;

	void Engine::Initialize()
	{
		g_renderer.Initialize();
		g_inputSystem.Initialize();
		g_audioSystem.Initialize();
		g_resources.Initialize();
		g_physicsSystem.Initialize();
		g_eventManager.Initialize();
	}

	void Engine::Update()
	{
		g_time.Tick();
		g_eventManager.Update();
		g_physicsSystem.Update();
		g_inputSystem.Update();
		g_audioSystem.Update();
	}

	void Engine::Shutdown()
	{
		Factory::Instance().Shutdown();

		g_eventManager.ShutDown();
		g_physicsSystem.Shutdown();
		g_resources.Shutdown();
		g_inputSystem.ShutDown();
		g_audioSystem.ShutDown();
		g_renderer.ShutDown();
	}

	void Engine::Register()
	{
		REGISTER_CLASS(Actor);
		REGISTER_CLASS(AudioComponent);
		REGISTER_CLASS(ModelComponent);
		REGISTER_CLASS(PhysicsComponent);
		REGISTER_CLASS(RBPhysicsComponent);
		REGISTER_CLASS(PlayerComponent);
		REGISTER_CLASS(SpriteComponent);
		REGISTER_CLASS(SpriteAnimComponent);
		REGISTER_CLASS(CollisionComponent);
		REGISTER_CLASS(TextComponent);
		REGISTER_CLASS(TilemapComponent);
		REGISTER_CLASS(CameraComponent);
		REGISTER_CLASS(CameraController);
		REGISTER_CLASS(LightComponent);
	}
}