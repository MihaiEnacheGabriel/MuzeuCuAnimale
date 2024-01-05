#pragma once
#include<filesystem>
#include <stdio.h>
#include <math.h> 

#include <GL/glew.h>
#include <glfw3.h>

#include <GLM.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <stb_image.h>
#include"Shader.h"
#include"Camera.h"
#include"Floor.h"
#include"ModelLoader.h"
class ObjRenderer
{
public:
	void Renderer(Shader& shader, Camera& camera, Model& m, glm::vec3 translate,glm::vec3 scale, glm::vec3 rotate,float angle);
};

