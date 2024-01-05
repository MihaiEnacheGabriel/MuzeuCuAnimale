﻿#include<filesystem>
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
#include"ObjRenderer.h"
namespace fs = std::filesystem;

const unsigned int width = 800;
const unsigned int height = 800;


#pragma comment (lib,"glew32.lib")
#pragma comment(lib,"glfw3dll.lib")
#pragma comment (lib,"OpenGl32.lib")
#pragma comment (lib,"assimp.lib")

unsigned int CreateTexture(const std::string& strTexturePath);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
double prevTime = 0.0;
double crntTime = 0.0;
double timeDiff = 0.5;
// Keeps track of the amount of frames in timeDiff
unsigned int counter = 0;




//void processInput(GLFWwindow* window);
float skyboxVertices[] =
{
	//   Coordinates
	-1.0f, -1.0f,  1.0f,//        7--------6
	 1.0f, -1.0f,  1.0f,//       /|       /|
	 1.0f, -1.0f, -1.0f,//      4--------5 |
	-1.0f, -1.0f, -1.0f,//      | |      | |
	-1.0f,  1.0f,  1.0f,//      | 3------|-2
	 1.0f,  1.0f,  1.0f,//      |/       |/
	 1.0f,  1.0f, -1.0f,//      0--------1
	-1.0f,  1.0f, -1.0f
};

unsigned int skyboxIndices[] =
{
	// Right
	1, 2, 6,
	6, 5, 1,
	// Left
	0, 4, 7,
	7, 3, 0,
	// Top
	4, 5, 6,
	6, 7, 4,
	// Bottom
	0, 3, 2,
	2, 1, 0,
	// Back
	0, 1, 5,
	5, 4, 0,
	// Front
	3, 7, 6,
	6, 2, 3
};
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
Camera* camera = nullptr;
int main()
{
	// Initialize GLFW
	glfwInit();


	GLFWwindow* window = glfwCreateWindow(width, height, "Proiect", NULL, NULL);
	glfwSetKeyCallback(window, key_callback);
	camera = new Camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	processInput(window);
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glewInit();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);





	// Generates Shader objects

	Shader skyboxShader("skyboxShader.vs", "skyboxShader.fs");
	Shader floorShader("floor.vs", "floor.fs");
	Shader Cageshader("firstObj.vs", "firstObj.fs");
	Shader Horseshader("firstObj.vs", "firstObj.fs");
	Shader ParrotShader("firstObj.vs", "firstObj.fs");
	Shader FenceShader("firstObj.vs", "firstObj.fs");
	Shader MountainShader("firstObj.vs", "firstObj.fs");
	Shader IguanaShader("firstObj.vs", "firstObj.fs");
	Shader WallShader("firstObj.vs", "firstObj.fs");
	Shader FocaShader("firstObj.vs", "firstObj.fs");
	Shader LionShader("firstObj.vs", "firstObj.fs");
	Shader WolfShader("firstObj.vs", "firstObj.fs");
	Shader PenguinShader("firstObj.vs", "firstObj.fs");
	Shader CaimanShader("firstObj.vs", "firstObj.fs");
	Shader BearShader("firstObj.vs", "firstObj.fs");
	Shader HumanShader("firstObj.vs", "firstObj.fs");
	Shader TreeShader("firstObj.vs", "firstObj.fs");
	Shader FoxShader("firstObj.vs", "firstObj.fs");
	// Take care of all the light related things
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);

	

	skyboxShader.Use();
	glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox"), 0);

	floorShader.Use();
	glUniform1i(glGetUniformLocation(floorShader.ID, "floorTexture"), 0);
	


	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Enables Cull Facing
	glEnable(GL_CULL_FACE);
	// Keeps front faces
	glCullFace(GL_FRONT);
	// Uses counter clock-wise standard
	glFrontFace(GL_CCW);


	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string cageObjFileName = (parentDir + "\\OBJ\\OBJ\\Kennel_Dog_Corona.obj");
	std::string horseObjFileName = (parentDir + "\\OBJ\\Horse\\Horse.obj");
	std::string parrotObjFileName = (parentDir + "\\OBJ\\Parrot\\10032_Parrot_V1_L3.obj");
	std::string fenceObjFileName = (parentDir + "\\OBJ\\Fence\\fence.obj");
	std::string IguanaObjFileName = (parentDir + "\\OBJ\\Iguana\\Iguana.obj");
	std::string mountainObjFileName = (parentDir + "\\OBJ\\Mountain\\mountain\\mount.blend1.obj");
	std::string focaObjFileName = (parentDir + "\\OBJ\\foca\\foca.obj");
	std::string lionObjFileName = (parentDir + "\\OBJ\\Lion\\lion.obj");
	std::string wolfObjFileName = (parentDir + "\\OBJ\\Wolf\\Wolf.obj");
	std::string penguinObjFileName = (parentDir + "\\OBJ\\Penguin\\Penguin.obj");
	std::string bearObjFileName = (parentDir + "\\OBJ\\Bear\\bear.obj");
	std::string caimanObjFileName = (parentDir + "\\OBJ\\Caiman\\caiman.obj");
	std::string HumanObjFileName = (parentDir + "\\OBJ\\Human\\Human\\ObjFbx\\Human.obj");
	std::string TreeObjFileName = (parentDir + "\\OBJ\\Tree\\Tree\\Tree.obj");
	std::string foxObjFileName = (parentDir + "\\OBJ\\Fox\\fox.obj");
	Model Cage(cageObjFileName, false);
	Model Horse(horseObjFileName, false);
	Model Parrot(parrotObjFileName, false);
	Model Fence(fenceObjFileName, false);
	Model Mountain(mountainObjFileName, false);
	Model Iguana(IguanaObjFileName, false);
	Model Foca(focaObjFileName, false);
	Model Lion(lionObjFileName, false);
	Model Wolf(wolfObjFileName, false);
	Model Penguin(penguinObjFileName, false);
	Model Bear(bearObjFileName, false);
	Model Caiman(caimanObjFileName, false);
	Model Human(HumanObjFileName, false);
	Model Tree(TreeObjFileName, false);
	Model Fox(foxObjFileName, false);
	std::string WallObjFileName = (parentDir + "\\OBJ\\Wall\\BrickWall.obj");
	Model Wall(WallObjFileName, false);
	// Create VAO, VBO, and EBO for the skybox
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	unsigned int floorTexture = CreateTexture(parentDir + "\\Floor\\grass.jpg");

	// All the faces of the cubemap (make sure they are in this exact order)
	std::string facesCubemap[6] =
	{
		parentDir + "/Skybox/right.jpg",
		parentDir + "/Skybox/left.jpg",
		parentDir + "/Skybox/top.jpg",
		parentDir + "/Skybox/bottom.jpg",
		parentDir + "/Skybox/front.jpg",
		parentDir + "/Skybox/back.jpg"
	};

	// Creates the cubemap texture object
	unsigned int cubemapTexture;
	glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// These are very important to prevent seams
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// This might help with seams on some systems
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// Cycles through all the textures and attaches them to the cubemap object
	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(i == 0);
		unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			//stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture: " << facesCubemap[i] << std::endl;
			stbi_image_free(data);
		}
	}

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Updates counter and times
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;
		if (timeDiff >= 1.0 / 30.0)
		{
			// Creates new title
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string ms = std::to_string((timeDiff / counter) * 1000);

			// Resets times and counter
			prevTime = crntTime;
			counter = 0;

			// Use this if you have disabled VSync
			//camera.Inputs(window);
		}
		// Specify the color of the background


		Floor floor;
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//renderFloor
		glViewport(0, 0, width, height);
		floorShader.Use();
		floor.setUp(*camera, floorShader, floorTexture);
		floor.renderScene(floorShader);

		camera->Inputs(window);
		processInput(window);
		camera->updateMatrix(45.0f, 0.1f, 100.0f);

		//glViewport(0, 0, width, height);
		ObjRenderer render;
		//render.Renderer(Horseshader, *camera, Horse, glm::vec3(-0.0f, -7.7f, 20.0f), glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f);
		
		glViewport(0, 0, width, height);
		render.Renderer1(Cageshader, *camera, Cage, glm::vec3(-250.0f, -7.7f, -180.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), 90.0f);

		glViewport(0, 0, width, height);
		render.Renderer(ParrotShader, *camera, Parrot, glm::vec3(-255.0f, 2.7f, -178.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.9f, 0.1f, 1.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(ParrotShader, *camera, Parrot, glm::vec3(-250.0f, 2.7f, -181.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.3f, 0.2f, 0.5f), -90.0f);

		glViewport(0, 0, width, height);
		render.Renderer1(Cageshader, *camera, Cage, glm::vec3(-290.0f, -7.7f, -180.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), 90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(IguanaShader, *camera, Iguana, glm::vec3(-290.0f, -6.0f, -180.0f), glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(1.0f, 1.0f, 1.0f), 10.0f);

		glViewport(0, 0, width, height);
		render.Renderer(FocaShader, *camera, Foca, glm::vec3(30.0f, -7.7f, 30.0f), glm::vec3(0.14f, 0.14f, 0.14f), glm::vec3(1.0f, 0.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer1(FocaShader, *camera, Foca, glm::vec3(60.0f, -7.7f, 30.0f), glm::vec3(0.14f, 0.14f, 0.14f), glm::vec3(1.0f, 0.0f, 0.0f), -90.0f, glm::vec3(0.0f, 0.0f, 1.0f), 95.0f);

		glViewport(0, 0, width, height);
		render.Renderer(LionShader, *camera, Lion, glm::vec3(-170.0f, -7.7f, 30.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer1(LionShader, *camera, Lion, glm::vec3(-175.0f, -7.7f, 50.0f), glm::vec3(0.13f, 0.13f, 0.13f), glm::vec3(1.0f, 0.0f, 0.0f), -90.0f, glm::vec3(0.0f, 0.0f, 1.0f), 150.0f);

		glViewport(0, 0, width, height);
		render.Renderer(WolfShader, *camera, Wolf, glm::vec3(-400.0f, -7.7f, 80.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(WolfShader, *camera, Wolf, glm::vec3(-415.0f, -7.7f, 65.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(WolfShader, *camera, Wolf, glm::vec3(-435.0f, -7.7f, 75.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.0f, 0.0f), -90.0f);

		glViewport(0, 0, width, height);
		render.Renderer1(PenguinShader, *camera, Penguin, glm::vec3(-180.0f, -7.7f, 225.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.0f, 0.0f), -90.0f, glm::vec3(0.0f, 0.0f, 1.0f), 90.0f);
		glViewport(0, 0, width, height);
		render.Renderer1(PenguinShader, *camera, Penguin, glm::vec3(-200.0f, -7.7f, 240.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.0f, 0.0f), -90.0f, glm::vec3(0.0f, 0.0f, 1.0f), 180.0f);
		glViewport(0, 0, width, height);
		render.Renderer1(PenguinShader, *camera, Penguin, glm::vec3(-250.0f, -7.7f, 230.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.0f, 0.0f), -90.0f, glm::vec3(0.0f, 0.0f, 1.0f), 45.0f);
		glViewport(0, 0, width, height);
		render.Renderer1(PenguinShader, *camera, Penguin, glm::vec3(-220.0f, -7.7f, 220.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.0f, 0.0f), -90.0f, glm::vec3(0.0f, 0.0f, 1.0f), 130.0f);

		glViewport(0, 0, width, height);
		render.Renderer1(CaimanShader, *camera, Caiman, glm::vec3(-90.0f, -7.7f, 320.0f), glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(1.0f, 0.0f, 0.0f), -90.0f, glm::vec3(0.0f, 0.0f, 1.0f), 145.0f);
		glViewport(0, 0, width, height);
		render.Renderer1(CaimanShader, *camera, Caiman, glm::vec3(-140.0f, -7.7f, 320.0f), glm::vec3(0.20f, 0.20f, 0.20f), glm::vec3(1.0f, 0.0f, 0.0f), -90.0f, glm::vec3(0.0f, 0.0f, 1.0f), 75.0f);

		glViewport(0, 0, width, height);
		render.Renderer1(FoxShader, *camera, Fox, glm::vec3(-100.0f, -7.7f, -230.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.0f, 0.0f), -90.0f, glm::vec3(0.0f, 0.0f, 1.0f), -30.0f);

		glViewport(0, 0, width, height);
		render.Renderer1(BearShader, *camera, Bear, glm::vec3(200.0f, -7.7f, 350.0f), glm::vec3(0.30f, 0.30f, 0.30f), glm::vec3(1.0f, 0.0f, 0.0f), -90.0f, glm::vec3(0.0f, 0.0f, 1.0f), 250.0f);
		//animal fences

		glViewport(0, 0, width, height);

		// Define the positions for the rectangles
		std::vector<glm::vec3> positions = {
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(200.0f, 0.0f, 0.0f),
			glm::vec3(-300.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 300.0f),
			glm::vec3(300.0f, 0.0f, 300.0f),
			glm::vec3(-100.0f, 0.0f, 200.0f),
			glm::vec3(0.0f, 0.0f, -300.0f),
			glm::vec3(150.0f, 0.0f, -200.0f),
			glm::vec3(-200.0f, 0.0f, -300.0f),
			glm::vec3(-500.0f, 0.0f, -200.0f)
		};

		for (const auto& pos : positions) {
			float offsetX = pos.x;
			float offsetZ = pos.z;

			// Render fences for the bottom
			for (int i = 0; i < 5; i++) {
				render.Renderer(FenceShader, *camera, Fence, glm::vec3(-170.0f + i * 30.0f + offsetX, -7.7f, offsetZ), glm::vec3(15.0f, 18.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f);
			}

			// Render fences for the top edge
			for (int i = 0; i < 5; i++) {
				render.Renderer(FenceShader, *camera, Fence, glm::vec3(-170.0f + i * 30.0f + offsetX, -7.7f, 90.0f + offsetZ), glm::vec3(15.0f, 18.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f);
			}

			// Render fences for the left edge
			for (int i = 1; i < 4; i++) {
				render.Renderer(FenceShader, *camera, Fence, glm::vec3(-200.0f + offsetX, -7.7f, i * 30.0f + offsetZ), glm::vec3(15.0f, 18.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
			}

			// Render fences for the right edge
			for (int i = 1; i < 4; i++) {
				render.Renderer(FenceShader, *camera, Fence, glm::vec3(-50.0f + offsetX, -7.7f, i * 30.0f + offsetZ), glm::vec3(15.0f, 18.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
			}
		}
		int z = 550;
		for(int i=0;i<21;i++)
		{
			glViewport(0, 0, width, height);
			render.Renderer(WallShader, *camera, Wall, glm::vec3(-800.0f, -6.0f, z), glm::vec3(23.0f, 23.0f, 23.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f);
			z -= 50;
		}
		 z = 550;
		for (int i = 0; i < 21; i++)
		{
			glViewport(0, 0, width, height);
			render.Renderer(WallShader, *camera, Wall, glm::vec3(500.0f, -6.0f, z), glm::vec3(23.0f, 23.0f, 23.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f);
			z -= 50;
		}
		int x = 470;
		for (int i = 0; i < 26; i++)
		{
			glViewport(0, 0, width, height);
			render.Renderer(WallShader, *camera, Wall, glm::vec3(x, -6.0f,585.0f), glm::vec3(23.0f, 23.0f, 23.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f);
			x -= 50;
		}
		x = 485;
		for (int i = 0; i < 26; i++)
		{
			glViewport(0, 0, width, height);
			render.Renderer(WallShader, *camera, Wall, glm::vec3(x, -6.0f, -480.0f), glm::vec3(23.0f, 23.0f, 23.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
			x -= 50;
		}
		float radius = 5000.0f;
		float angle = 90.0f;
		int num_segments = 200; // Increase this for a smoother circle
		for (int i = 0; i < num_segments; i++) {
			float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
			float x = radius * cosf(theta);
			float z = radius * sinf(theta);
			glViewport(0, 0, width, height);
			if (angle == 90.0f)
				angle = 180.0f;
			else
				angle = 90.0f;
			render.Renderer(MountainShader, *camera, Mountain, glm::vec3(x, 2.7f, z), glm::vec3(100.0f, 100.0f, 100.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f);
		}


		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(200.0f, -6.0f, -480.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(-50.0f, -6.0f, -40.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(-250.0f, -6.0f, -200.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(341.0f, -6.0f, 100.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(210.0f, -6.0f, 30.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(-21.0f, -6.0f, -210.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(500.0f, -6.0f, 300.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(-590.0f, -6.0f, 21.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(-450.0f, -6.0f, 145.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(-340.0f, -6.0f, 210.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(-450.0f, -6.0f, 145.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(210.0f, -6.0f, -550.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(-40.0f, -6.0f, 25.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(-550.0f, -6.0f, -550.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(318.0f, -6.0f, 456.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(120.0f, -6.0f, -550.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(-410.0f, -6.0f, 625.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(410.0f, -6.0f, 450.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(213.0f, -6.0f, -435.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(567.0f, -6.0f, -100.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(HumanShader, *camera, Human, glm::vec3(610.0f, -6.0f, 100.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f);
		glViewport(0, 0, width, height);
		render.Renderer(TreeShader, *camera, Tree, glm::vec3(150.0f, -2.0f, 100.0f), glm::vec3(45.0f, 45.0f, 45.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
		glViewport(0, 0, width, height);
		render.Renderer(TreeShader, *camera, Tree, glm::vec3(340.0f, -2.0f, -100.0f), glm::vec3(45.0f, 45.0f, 45.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
		glViewport(0, 0, width, height);
		render.Renderer(TreeShader, *camera, Tree, glm::vec3(210.0f, -2.0f, 430.0f), glm::vec3(45.0f, 45.0f, 45.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
		glViewport(0, 0, width, height);
		glViewport(0, 0, width, height);
		render.Renderer(TreeShader, *camera, Tree, glm::vec3(-150.0f, -2.0f, 170.0f), glm::vec3(45.0f, 45.0f, 45.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
		render.Renderer(TreeShader, *camera, Tree, glm::vec3(-200.0f, -2.0f, -360.0f), glm::vec3(45.0f, 45.0f, 45.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
		glViewport(0, 0, width, height);
		render.Renderer(TreeShader, *camera, Tree, glm::vec3(-520.0f, -2.0f, 300.0f), glm::vec3(45.0f, 45.0f, 45.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
		glViewport(0, 0, width, height);
		render.Renderer(TreeShader, *camera, Tree, glm::vec3(520.0f, -2.0f, -200.0f), glm::vec3(45.0f, 45.0f, 45.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
		glViewport(0, 0, width, height);
		render.Renderer(TreeShader, *camera, Tree, glm::vec3(320.0f, -2.0f, -400.0f), glm::vec3(45.0f, 45.0f, 45.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
		glViewport(0, 0, width, height);
		render.Renderer(TreeShader, *camera, Tree, glm::vec3(-520.0f, -2.0f, -200.0f), glm::vec3(45.0f, 45.0f, 45.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);
		glViewport(0, 0, width, height);
		render.Renderer(TreeShader, *camera, Tree, glm::vec3(420.0f, -2.0f, 400.0f), glm::vec3(45.0f, 45.0f, 45.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);


		glDepthFunc(GL_LEQUAL);
		skyboxShader.Use();
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		// We make the mat4 into a mat3 and then a mat4 again in order to get rid of the last row and column
		// The last row and column affect the translation of the skybox (which we don't want to affect)
		view = glm::mat4(glm::mat3(glm::lookAt(camera->position, camera->position + camera->forward, camera->up)));
		projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


		// Draws the cubemap as the last object so we can save a bit of performance by discarding all fragments
		// where an object is present (a depth of 1.0f will always fail against any object's depth value)
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Switch back to the normal depth function
		glDepthFunc(GL_LESS);


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, (float)timeDiff);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, (float)timeDiff);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, (float)timeDiff);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, (float)timeDiff);
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		camera->ProcessKeyboard(UP, (float)timeDiff);
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		camera->ProcessKeyboard(DOWN, (float)timeDiff);

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		camera->Reset(width, height);

	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

	camera->Reshape(width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	camera->MouseControl((float)xpos, (float)ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yOffset)
{
	camera->ProcessMouseScroll((float)yOffset);
}
unsigned int CreateTexture(const std::string& strTexturePath)
{
	unsigned int textureId = -1;

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(strTexturePath.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else {
		std::cout << "Failed to load texture: " << strTexturePath << std::endl;
	}
	stbi_image_free(data);

	return textureId;
}
