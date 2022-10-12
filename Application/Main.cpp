#include "Engine.h" 
#include <iostream> 

float points[] = {
  -0.5f, -0.5f,  0.0f,
   0.5f,  0.5f,  0.0f,
   -0.5f, 0.5f,  0.0f,
   -0.5f, -0.5f,  0.0f,
   0.5f,  0.5f,  0.0f,
   0.5f, -0.5f,  0.0f
};

Bear::Vector3 colors[] = {
	{0, 0, 1},
	{1, 0, 1},
	{0, 1, 0},
	{0, 0, 1},
	{0, 1, 1},
	{1, 1, 1},
};

int main(int argc, char** argv)
{
	Bear::InitializeMemory();
	Bear::SetFilePath("../Assets");

	Bear::Engine::Instance().Initialize();
	Bear::Engine::Instance().Register();

	Bear::g_renderer.CreateWindow("Neumont", 800, 600, false);

	// create vertex buffer
	GLuint pvbo = 0;
	glGenBuffers(1, &pvbo);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);

	GLuint cvbo = 0;
	glGenBuffers(1, &cvbo);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Bear::Vector3), colors, GL_STATIC_DRAW);

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
	GLuint program = glCreateProgram();
	glAttachShader(program, fs->m_shader);
	glAttachShader(program, vs->m_shader);
	glLinkProgram(program);
	glUseProgram(program);

	float angle = 0;
	Bear::Vector2 position;

	bool quit = false;
	while (!quit)
	{
		Bear::Engine::Instance().Update();

		if (Bear::g_inputSystem.GetKeyState(Bear::key_escape) == Bear::InputSystem::KeyState::Pressed) quit = true;

		Bear::g_renderer.BeginFrame();
	
		glDrawArrays(GL_TRIANGLES, 0, 6);

		Bear::g_renderer.EndFrame();
	}

	Bear::Engine::Instance().Shutdown();
	return 0;
}