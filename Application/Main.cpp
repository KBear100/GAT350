#include "Engine.h" 
#include <iostream> 

#define POST_PROCESS

int main(int argc, char** argv)
{
	LOG("Application Started...");

	Bear::InitializeMemory();
	Bear::SetFilePath("../Assets");

	Bear::Engine::Instance().Initialize();
	Bear::Engine::Instance().Register();
	LOG("Engine Initialized...");

	Bear::g_renderer.CreateWindow("Neumont", 800, 600, false);
	LOG("Window Initialized...");
	Bear::g_gui.Initialize(Bear::g_renderer);

	// create framebuffer texture
	auto texture = std::make_shared<Bear::Texture>();
	texture->CreateTexture(1024, 1024);
	Bear::g_resources.Add<Bear::Texture>("fb_texture", texture);

	// create framebuffer
	auto framebuffer = Bear::g_resources.Get<Bear::Framebuffer>("framebuffer", "fb_texture");
	framebuffer->Unbind();

	// load scene
	auto scene = Bear::g_resources.Get<Bear::Scene>("Scenes/rtt.scn");

	float x = 0;

	glm::vec3 rot = { 0, 0, 0 };
	float ri = 1;
	float interpolation = 0.5f;
	bool quit = false;
	while (!quit)
	{
		Bear::Engine::Instance().Update();

		Bear::g_gui.BeginFrame(Bear::g_renderer);

		if (Bear::g_inputSystem.GetKeyState(Bear::key_escape) == Bear::InputSystem::KeyState::Pressed) quit = true;

		auto actor = scene->GetActorFromName("Tiger");
		if (actor)
		{
			actor->m_transform.rotation = Math::EulerToQuaternion(rot);
		}

		actor = scene->GetActorFromName("Light");
		if (actor)
		{
			// move light using sin wave 
			//actor->m_transform.position.x = x;
		}

		//auto material = Bear::g_resources.Get<Bear::Material>("Materials/multi.mtrl");
		//if (material)
		{
			//material->uv_offset.x += Bear::g_time.deltaTime;
			//material->uv_offset.y += Bear::g_time.deltaTime;
		}

		/*auto program = Bear::g_resources.Get<Bear::Program>("Shaders/FX/reflection_refraction.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("ri", ri);
			program->SetUniform("interpolation", interpolation);
		}*/

		auto program = Bear::g_resources.Get<Bear::Program>("shaders/postprocess/postprocess.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("offset", Bear::g_time.time);
		}

		ImGui::Begin("Transform");
		ImGui::DragFloat3("Rotation", &rot[0]);
		ImGui::DragFloat("Refraction", &ri, 0.01f, 1, 3);
		ImGui::DragFloat("Interpolation", &interpolation, 0.01f, 0, 1);
		ImGui::End();

		scene->Update();

#ifdef POST_PROCESS 
		// don't draw post process actor when rendering to the framebuffer 
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(false);
			}
		}
		// render pass 1 (render scene to framebuffer) 
		Bear::g_renderer.SetViewport(0, 0, framebuffer -> GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();
		Bear::g_renderer.BeginFrame();
		scene->PreRender(Bear::g_renderer);
		scene->Render(Bear::g_renderer);
		framebuffer->Unbind();

		// render pass 2 (render to screen) 
		Bear::g_renderer.RestoreViewport();
		Bear::g_renderer.BeginFrame();
		scene->PreRender(Bear::g_renderer);

		// draw only the post process actor to the screen 
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(true);
				actor->Draw(Bear::g_renderer);
			}
		}
#else 
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
#endif // POST_PROCESS 

		//Bear::g_gui.Draw();

		Bear::g_renderer.EndFrame();
		Bear::g_gui.EndFrame();
	}

	scene->RemoveAll();
	Bear::Engine::Instance().Shutdown();
	return 0;
}