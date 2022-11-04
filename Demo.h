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
	GLuint shaderProgram, VBO_default, VAO_default, EBO_default;

	float angle = 0;
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow *window);

	// Plane Things
	GLuint texture_plane, VBO_plane, VAO_plane, EBO_plane;

	void BuildColoredPlane();
	void DrawColoredPlane();

	// Pedestrian Things (1-2 png boy) (3-4 jpg) (5-7 png)
	std::string skinType = "skin5.png";
	GLuint texture_pedestrian, VBO_head, VAO_head, EBO_head, VBO_body, VAO_body, EBO_body, VBO_hand, VAO_hand, EBO_hand, VBO_leg, VAO_leg, EBO_leg;

	void BuildBody();
	void BuildLeg();
	void BuildHand();
	void BuildHead();
	void DrawBody();
	void DrawLeg(int rotate, double positionX, double positionY, double positionZ);
	void DrawHand(int rotate, double positionX, double positionY, double positionZ);
	void DrawHead();

	// Windmill Things
	GLuint	texture_foundation, VBO_foundation, VAO_foundation, EBO_foundation,
			texture_center,
			texture_pinwheel,
			texture_propeller, VBO_propeller, VAO_propeller, EBO_propeller;

	void BuildFoundation();
	void BuildPinwheel();
	void BuildCenter();
	void BuildPropeller();
	void DrawFoundation();
	void DrawCenter(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ);
	void DrawPinwheel(int rotate, double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ);
	void DrawPropeller(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ);

	/*
	// Lamp Things
	GLuint texture_lamp;

	void BuildLamp();
	void DrawLamp(double positionX, double positionY, double positionZ);

	// Hedge Things
	GLuint texture_hedge, VBO_hedge, VAO_hedge, EBO_hedge;

	void BuildHedge();
	void DrawHedge(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ);

	// Tree Things
	GLuint	texture_darkOak, texture_birch, VBO_tree, VAO_tree, EBO_tree,
			texture_darkLeaf, texture_birchLeaf, VBO_leaf, VAO_leaf, EBO_leaf;

	void BuildDarkOak();
	void BuildBirch();
	void BuildDarkLeaf();
	void BuildBirchLeaf();
	void DrawDarkOak(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ);
	void DrawBirch(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ);
	void DrawDarkLeaf(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ);
	void DrawBirchLeaf(double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ);

	// Road Things
	GLuint texture_cobble, texture_stone, VBO_road, VAO_road, EBO_road;

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