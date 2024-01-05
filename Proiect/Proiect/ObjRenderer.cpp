#include "ObjRenderer.h"

void ObjRenderer::Renderer(Shader& shader,Camera& camera,Model& m,glm::vec3 translate,glm::vec3 scale, glm::vec3 rotate,float angle)
{
	shader.Use();
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, translate);
	model = glm::scale(model,scale);
	model = glm::rotate(model, glm::radians(angle), rotate);
	shader.SetMat4("model", model);
	glm::mat4 projectionHorse = camera.GetProjectionMatrix();
	glm::mat4 viewHorse = camera.GetViewMatrix();
	shader.SetMat4("projection", projectionHorse);
	shader.SetMat4("view", viewHorse);
	shader.SetVec3("viewPos", camera.GetPosition());
	m.Draw(shader);
}

void ObjRenderer::Renderer1(Shader& shader, Camera& camera, Model& m, glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate, float angle, glm::vec3 rotate1, float angle1)
{
	shader.Use();
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, translate);
	model = glm::scale(model, scale);
	model = glm::rotate(model, glm::radians(angle), rotate);
	model = glm::rotate(model, glm::radians(angle1), rotate1);
	shader.SetMat4("model", model);
	glm::mat4 projectionHorse = camera.GetProjectionMatrix();
	glm::mat4 viewHorse = camera.GetViewMatrix();
	shader.SetMat4("projection", projectionHorse);
	shader.SetMat4("view", viewHorse);
	shader.SetVec3("viewPos", camera.GetPosition());
	m.Draw(shader);
}