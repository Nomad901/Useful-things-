#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SWIZZLE
#define SDL_MAIN_HANDLED
#include <iostream>
#include <format>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

int main(int argc, char* argv[])
{
	glm::vec3 A({ 1.0f, 3.0f, 4.0f });
	glm::vec3 B({ 4.0f, 0.5f, 6.0f });

	std::cout << std::format("A.x: {}  A.y: {}  A.z: {}\n", A.x, A.y, A.z);
	std::cout << std::format("B.x: {}  B.y: {}  B.z: {}\n", B.x, B.y, B.z);

	auto result = glm::dot(A, B); 
	// result = (A.x * B.x) + (A.y * B.y) + (A.z * B.z)
	std::cout << std::format("The result: {}\n", result);

	auto result2 = glm::normalize(A);
	// result2 = A / sqrt(A.x*A.x + A.y*A.y + A.z*A.z)
	std::cout << std::format("A.x: {}  A.y: {}  A.z: {}\n", result2.x, result2.y, result2.z);

	glm::mat4 mat(1.0f);
	std::cout << std::format("\nThe matrix: {}\n\n", glm::to_string(mat));

	// in order to print vectors onto the console 
	std::cout << std::format("Vector A: {}\n", glm::to_string(A));
	std::cout << glm::to_string(A.xyz()) << '\n' << glm::to_string(A.zx()) << '\n';

	// crossproduct
	auto result3 = glm::cross(A, B);
	// (y1*z2) - (z1*y2)
	// (z1*x2) - (x1*z2)
	// (x1*y2) - (y1*x2)

	// (3*6) - (4*0.5)
	// (4*4) - (1*6)
	// (1*0.5) - (3*4)

	std::cout << std::format("Crossproduct: {}\n", glm::to_string(result3));

	return 0;
}