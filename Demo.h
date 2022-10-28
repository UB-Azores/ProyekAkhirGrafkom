#pragma once
#include "RenderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>
#include <vector>

class Demo :
	public RenderEngine
{
public:
	Demo();
	~Demo();
private:
	GLuint shaderProgram,
	//Plane
	texture1, VBO1, VAO1, EBO1,

	//Pedestrian
	texture2, VBO2, VAO2, EBO2, VBO3, VAO3, EBO3, VBO4, VAO4, EBO4, VBO5, VAO5, EBO5,

	//Windmill
	texture3, texture4, texture5, texture8, VBO6, VAO6, EBO6, VBO7, VAO7, EBO7, VBO8, VAO8, EBO8, VBO11, VAO11, EBO11,

	//Lamp
	texture6, VBO9, VAO9, EBO9,
		
	//Hedge	
	texture7, VBO10, VAO10, EBO10,
		
	//Tree
	texture9, texture10, texture11, texture12, VBO12, VAO12, EBO12, VBO13, VAO13, EBO13, VBO14, VAO14, EBO14, VBO15, VAO15, EBO15,
		
	//Road
	texture13, texture14, VBO16, VAO16, EBO16, VBO17, VAO17, EBO17;

	float angle = 0;
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow *window);
	
	// Plane Things
	void BuildColoredPlane();
	void DrawColoredPlane();

	// Pedestrian Things (1-2 png boy) (3-4 jpg) (5-7 png)
	std::string skinType = "skin1.png";
	void BuildBody();
	void BuildLeg();
	void BuildHand();
	void BuildHead();
	void DrawBody();
	void DrawLeg(int rotate, double positionX, double positionY, double positionZ);
	void DrawHand(int rotate, double positionX, double positionY, double positionZ);
	void DrawHead();

	/*
	// Windmill Things
	void BuildFoundation();
	void BuildPinwheel();
	void BuildCenter();
	void BuildPropeller();
	void DrawFoundation();
	void DrawCenter(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ);
	void DrawPinwheel(int rotate, double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ);
	void DrawPropeller(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ);

	// Lamp Things
	void BuildLamp();
	void DrawLamp(double positionX, double positionY, double positionZ);

	// Hedge Things
	void BuildHedge();
	void DrawHedge(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ);

	// Tree Things
	void BuildDarkOak();
	void BuildBirch();
	void BuildDarkLeaf();
	void BuildBirchLeaf();
	void DrawDarkOak(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ);
	void DrawBirch(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ);
	void DrawDarkLeaf(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ);
	void DrawBirchLeaf(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ);

	// Road Things
	void BuildCobble();
	void BuildStone();
	void DrawCobble(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ);
	void DrawStone(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ);
	/**/

	// Move Things
	float speedX = 1;
	float speedY = 1;
	float speedZ = 1;
	double pindahX = 0;
	double pindahY = 0;
	double pindahZ = 0;

	float lebarGerakan = 0;
	int gerakBadan = 0;
	float arahBadan = 0;
	bool kakiTanganGerak = false;

	// Camera Things
	double viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ;
	float CAMERA_SPEED, fovy;
	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void InitCamera();
};