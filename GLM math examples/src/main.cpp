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

	// crossproduct - is helping to find a perpendicular vector of 2 other vectors. 
	// if we change A on B and B on A, results will be sheerly different
	auto result3 = glm::cross(A, B);
	// (y1*z2) - (z1*y2)
	// (z1*x2) - (x1*z2)
	// (x1*y2) - (y1*x2)

	// (3*6) - (4*0.5)
	// (4*4) - (1*6)
	// (1*0.5) - (3*4)
	
	std::cout << std::format("Crossproduct: {}\n", glm::to_string(result3));

	glm::vec3 T({ 3.0f, -2.0f, 0.0f });
	glm::vec3 R({ 0.0f, 7.0f, 0.0f });

	std::cout << std::format("A vector length: {}\n", glm::length(T));
	std::cout << std::format("B vector length: {}\n", glm::length(R));
	// sqrt(A.x*A.x + A.y*A.y)
	
	auto dotproduct = glm::dot(glm::normalize(T), glm::normalize(R));
	std::cout << std::format("Dot product: {}\n", dotproduct);
	// dot product is used to show how much 2 vectors are close. is 0 - this is orthoginal 
	std::cout << std::format("Angle: {}\n", std::acos(dotproduct) * 180.0f / glm::pi<float>());
	// is showing an angle between them. useful for bullets system

	auto crossProduct = glm::cross(T, R);
	std::cout << std::format("CrossProduct: {}\n", glm::to_string(crossProduct));
	//cross product is giving you a perpendicular vector to 2 other vectors


	return 0;
}
