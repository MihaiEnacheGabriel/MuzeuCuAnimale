#include "Floor.h"


void Floor::renderFloor()
{
	//unsigned int floorVBO;
	if (floorVAO == 0) {
		// set up vertex data (and buffer(s)) and configure vertex attributes
		float planeVertices[] = {
			// positions            // normals         // texcoords
			10000.0f, -7.5f,  10000.0f,  0.0f, 1.0f, 0.0f,  250.0f,  0.0f,
			-10000.0f, -7.5f,  10000.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
			-1000.0f, -7.5f, -10000.0f,  0.0f, 1.0f, 0.0f,   0.0f, 250.0f,

			10000.0f, -7.5f,  10000.0f,  0.0f, 1.0f, 0.0f,  250.0f,  0.0f,
			-10000.0f, -7.5f, -10000.0f,  0.0f, 1.0f, 0.0f,   0.0f, 250.0f,
			10000.0f, -7.5f, -10000.0f,  0.0f, 1.0f, 0.0f,  250.0f, 250.0f
		};
		// plane VAO
		glGenVertexArrays(1, &floorVAO);
		glGenBuffers(1, &floorVBO);
		glBindVertexArray(floorVAO);
		glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glBindVertexArray(0);
	}

	glBindVertexArray(floorVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


void Floor::renderScene(const Shader& shader)
{
	// floor
	glm::mat4 model = glm::mat4(1.0f);

	shader.SetMat4("model", model);
	renderFloor();
}

void Floor::setUp(const Camera& camera,Shader& floorShader,unsigned int floorTexture)
{
	glm::mat4 projectionFloor = camera.GetProjectionMatrix();
	glm::mat4 viewFloor = camera.GetViewMatrix();
	floorShader.SetMat4("projection", projectionFloor);
	floorShader.SetMat4("view", viewFloor);
	floorShader.SetVec3("viewPos", camera.GetPosition());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, floorTexture);
	glDisable(GL_CULL_FACE);
}
