#include "Engine.h" 
#include <iostream> 

float points[] = {
	-0.5f, -0.5f,  0.0f,
	-0.5f, 0.5f,  0.0f,
	0.5f,  0.5f,  0.0f,
	-0.5f, -0.5f,  0.0f,
	0.5f,  0.5f,  0.0f,
	0.5f, -0.5f,  0.0f
};

glm::vec3 colors[] = {
	{0, 0, 1},
	{1, 0, 1},
	{0, 1, 0},
	{0, 0, 1},
	{0, 1, 1},
	{1, 1, 1},
};

glm::vec2 texcoords[]{
	{ 0, 0 },
	{ 0, 1 },
	{ 1, 1 },
	{ 0, 0 },
	{ 1, 1 },
	{ 1, 0 },
};

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

	// create vertex buffer
	GLuint pvbo = 0;
	glGenBuffers(1, &pvbo);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);

	GLuint cvbo = 0;
	glGenBuffers(1, &cvbo);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), colors, GL_STATIC_DRAW);

	GLuint tvbo = 0;
	glGenBuffers(1, &tvbo);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), texcoords, GL_STATIC_DRAW);

	// create vertex array
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	// create shader
	std::shared_ptr<Bear::Shader> vs = Bear::g_resources.Get<Bear::Shader>("Shaders/basic.vert", GL_VERTEX_SHADER);
	std::shared_ptr<Bear::Shader> fs = Bear::g_resources.Get<Bear::Shader>("Shaders/basic.frag", GL_FRAGMENT_SHADER);
	 
	//GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vs, 1, &vertex_shader, NULL);
	//glCompileShader(vs);
	//GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fs, 1, &fragment_shader, NULL);
	//glCompileShader(fs);

	// create program
	//std::shared_ptr<Bear::Program> program = Bear::g_resources.Get<Bear::Program>("Shaders/basic.prog", GL_PROGRAM);
	//program->Link();
	//program->Use();

	// create texture
	//std::shared_ptr<Bear::Texture> texture = Bear::g_resources.Get<Bear::Texture>("Sprites/llama.jpg");
	//std::shared_ptr<Bear::Texture> texture2 = Bear::g_resources.Get<Bear::Texture>("Sprites/wood.png");
	//texture->Bind();

	//create material
	std::shared_ptr<Bear::Material> material = Bear::g_resources.Get<Bear::Material>("Materials/box.mtrl");
	material->Bind();
	
	glm::mat4 mx{ 1 };
	//mx = glm::scale(glm::vec3(0.5, 0.5, 0.5));

	bool quit = false;
	while (!quit)
	{
		Bear::Engine::Instance().Update();

		if (Bear::g_inputSystem.GetKeyState(Bear::key_escape) == Bear::InputSystem::KeyState::Pressed) quit = true;

		material->GetProgram()->SetUniform("scale", std::sin(Bear::g_time.time * 3));
		material->GetProgram()->SetUniform("transform", mx);

		Bear::g_renderer.BeginFrame();
	
		glDrawArrays(GL_TRIANGLES, 0, 6);

		Bear::g_renderer.EndFrame();
	}

	Bear::Engine::Instance().Shutdown();
	return 0;
}