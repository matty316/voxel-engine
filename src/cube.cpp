#include "cube.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Cube::render() {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	shader.setMat4("model", model);
}