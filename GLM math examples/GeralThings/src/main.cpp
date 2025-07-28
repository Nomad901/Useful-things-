#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SWIZZLE
#define SDL_MAIN_HANDLED
#include <iostream>
#include <format>

#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

int main(int argc, char* argv[])
{
	// this is in a local space now
	glm::vec4 vertex(1.0f, 5.0f, 1.0f, 1.0f);

	// local -> world
	glm::mat4 model(1.0f);
	model = glm::translate(model, { 50.0f,50.0f,0.0f });
	// world -> local
	glm::mat4 inverseModel = glm::inverse(model);

	// in order to translate the vector above in the world space 
	// we merely should multiply this on the model matrix;
	glm::vec4 vertexWorld = model * vertex;

	std::cout << std::format("The vertex: {}\n", glm::to_string(vertexWorld));

	SDL_Window* window = SDL_CreateWindow("MathExample", 1280, 720, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiBackendFlags_None;
	io.IniSavingRate = NULL;

	ImGui::StyleColorsDark();

	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);

	SDL_FRect tmpRect = { vertex.x, vertex.y, 100,100 };
	bool active = true;
	bool firstTime = true;
	bool showLogPos = false;

	int32_t colorWindow[3] = { 1,1,1 };
	int32_t colorQuad[3] = { 23,42,35 };

	while (active)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL3_ProcessEvent(&event);

			if (event.type == SDL_EVENT_QUIT)
			{
				active = false;
				break;
			}

			if (event.key.key == SDLK_D)
			{
				vertex.x += 5; 
				tmpRect.x = vertex.x;
			}
			else if (event.key.key == SDLK_A)
			{
				vertex.x -= 5;
				tmpRect.x = vertex.x;
			}
			else if (event.key.key == SDLK_W)
			{
				vertex.y -= 5;
				tmpRect.y = vertex.y;
			}
			else if (event.key.key == SDLK_S)
			{
				vertex.y += 5;
				tmpRect.y = vertex.y;
			}
		}
		SDL_SetRenderDrawColor(renderer, colorWindow[0], colorWindow[1], colorWindow[2], 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, colorQuad[0], colorQuad[1], colorQuad[2], 255);
		SDL_RenderRect(renderer, &tmpRect);

		ImGui_ImplSDL3_NewFrame();
		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui::NewFrame();

		if (firstTime)
		{
			ImGui::SetNextWindowPos({ 100,100 });
			ImGui::SetNextWindowSize({ 400, 300 });
			firstTime = false;
		}
		
		ImGui::Begin("I am math!", &active, ImGuiBackendFlags_None);
		
		if (ImGui::Button("WorldSpace"))
		{
			vertex = model * vertex;
			std::cout << std::format("WorldSpace pos: {}\n", glm::to_string(vertex));
		}
		else if (ImGui::Button("LocalSpace"))
		{
			vertex = inverseModel * vertex;
			std::cout << std::format("LocalSpace pos: {}\n", glm::to_string(vertex));
		}
		
		ImGui::Checkbox("Show position in the console", &showLogPos);
		if(showLogPos)
			std::cout << std::format("Position of the quad: {}\n", glm::to_string(vertex));

		ImGui::Spacing();
		ImGui::Separator();

		ImGui::SliderInt("Color background R", &colorWindow[0], 1, 255);
		ImGui::SliderInt("Color background G", &colorWindow[1], 1, 255);
		ImGui::SliderInt("Color background B", &colorWindow[2], 1, 255);

		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::SliderInt("Color Quad R", &colorQuad[0], 1, 255);
		ImGui::SliderInt("Color Quad G", &colorQuad[1], 1, 255);
		ImGui::SliderInt("Color Quad B", &colorQuad[2], 1, 255);

		ImGui::End();
		ImGui::EndFrame();

		ImGui::Render();
		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
		SDL_RenderPresent(renderer);
	}


	ImGui_ImplSDL3_Shutdown();
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
} 