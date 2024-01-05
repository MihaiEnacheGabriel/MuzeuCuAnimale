#pragma once
#include"Shader.h"
#include"Camera.h"
class Floor
{
	unsigned int floorVAO=0, floorVBO;
public:
	void renderFloor();
	void renderScene(const Shader& shader);
	void setUp(const Camera& camera,Shader& floorShader, unsigned int floorTexture);
};

