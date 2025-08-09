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

            // we are finding the distance between the mouse pos and the circle pos
            // glm::vec2 localVector = { mMousePos.x - mCircle.getPos().x, mMousePos.y - mCircle.getPos().y };
            // after that we normalize that distance and multiplying this by a radius of the circle
            // which therefore will give us "scale" factor
            //localVector = glm::normalize(localVector) * float(mCircle.getBigRadius());
            // we are using the "scale" factor and getting the proper position.
           // const glm::vec2 globalVector = { localVector.x + mCircle.getPos().x, localVector.y + mCircle.getPos().y };

           // mFactoryRays.update(mCircle.getPos(), { globalVector.x, globalVector.y }, true);
//bool Setup::pointInCircle()
//{
    // we find the distance between the mouse and the circle again
    // but we also need to multiply it by itself (cuz of the equation structure)
//    const float xPart = (mMousePos.x - mCircle.getPos().x);
//    const float yPart = (mMousePos.y - mCircle.getPos().y);
//    const float distanceFromPointToCircle = (xPart * xPart) + (yPart * yPart);
//    const float squaredRadius = (mCircle.getBigRadius() * mCircle.getBigRadius());

    // a^2 * b^2 < r^2
//    return distanceFromPointToCircle < squaredRadius;
//}

	return 0;
}


