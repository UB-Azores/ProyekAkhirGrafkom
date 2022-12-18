#include "Demo.h"
using namespace std;

Demo::Demo() {
}
Demo::~Demo() {
}

// Initialization Things
void Demo::Init() {
	//shaderProgram = BuildShader("vertexShader.vert", "fragmentShader.frag", nullptr);
	shadowmapShader = BuildShader("shadowMap.vert", "shadowMap.frag", nullptr);
	depthmapShader = BuildShader("depthMap.vert", "depthMap.frag", nullptr);

	BuildSkybox();

	BuildColoredPlane();

	// Pedestrian
	BuildHead();
	BuildBody();
	BuildHand();
	BuildLeg();

	// Windmill
	BuildFoundation();
	BuildCenter();
	BuildPinwheel();
	BuildPropeller();

	// Hedge
	BuildHedge();
	
	// Lamp
	BuildLamp();
	BuildGlass();

	// Tree
	BuildDarkOak();
	BuildBirch();
	BuildDarkLeaf();
	BuildBirchLeaf();

	// Road
	BuildCobble();
	BuildStone();

	InitCamera();

	BuildDepthMap();
}
void Demo::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO_default);
	glDeleteBuffers(1, &VBO_default);
	glDeleteBuffers(1, &EBO_default);

	glDeleteVertexArrays(1, &VAO_skybox);
	glDeleteBuffers(1, &VBO_skybox);
	glDeleteBuffers(1, &EBO_skybox);

	glDeleteVertexArrays(1, &VAO_plane);
	glDeleteBuffers(1, &VBO_plane);
	glDeleteBuffers(1, &EBO_plane);

	glDeleteVertexArrays(1, &VAO_head);
	glDeleteBuffers(1, &VBO_head);
	glDeleteBuffers(1, &EBO_head);
	glDeleteVertexArrays(1, &VAO_body);
	glDeleteBuffers(1, &VBO_body);
	glDeleteBuffers(1, &EBO_body);
	glDeleteVertexArrays(1, &VAO_hand);
	glDeleteBuffers(1, &VBO_hand);
	glDeleteBuffers(1, &EBO_hand);
	glDeleteVertexArrays(1, &VAO_leg);
	glDeleteBuffers(1, &VBO_leg);
	glDeleteBuffers(1, &EBO_leg);

	glDeleteVertexArrays(1, &VAO_foundation);
	glDeleteBuffers(1, &VBO_foundation);
	glDeleteBuffers(1, &EBO_foundation);
	glDeleteVertexArrays(1, &VAO_propeller);
	glDeleteBuffers(1, &VBO_propeller);
	glDeleteBuffers(1, &EBO_propeller);

	glDeleteVertexArrays(1, &VAO_hedge);
	glDeleteBuffers(1, &VBO_hedge);
	glDeleteBuffers(1, &EBO_hedge);

	glDeleteVertexArrays(1, &VAO_tree);
	glDeleteBuffers(1, &VBO_tree);
	glDeleteBuffers(1, &EBO_tree);
	glDeleteVertexArrays(1, &VAO_leaf);
	glDeleteBuffers(1, &VBO_leaf);
	glDeleteBuffers(1, &EBO_leaf);

	glDeleteVertexArrays(1, &VAO_road);
	glDeleteBuffers(1, &VBO_road);
	glDeleteBuffers(1, &EBO_road);

	glDeleteBuffers(1, &depthMapFBO);
}

// Running Things
void Demo::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.01f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.01f;
		}
	}

	// update camera movement
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
		kakiTanganGerak = true;
		gerakBadan = 0;
		arahBadan = 0.0f;
	}
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
		kakiTanganGerak = true;
		gerakBadan = 3;
		arahBadan = 3.1f;
	}
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
		kakiTanganGerak = true;
		gerakBadan = 1;
		arahBadan = 1.6f;
	}
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
		kakiTanganGerak = true;
		gerakBadan = 2;
		arahBadan = -1.6f;
	}
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		kakiTanganGerak = true;
		gerakBadan = 4;
		arahBadan = 0.8f;
	}
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		kakiTanganGerak = true;
		gerakBadan = 5;
		arahBadan = -0.8f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		kakiTanganGerak = true;
		gerakBadan = 6;
		arahBadan = -2.4f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		kakiTanganGerak = true;
		gerakBadan = 7;
		arahBadan = 2.4f;
	}
	if (glfwGetKey(window, GLFW_KEY_W) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_A) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) != GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) != GLFW_PRESS) {
		kakiTanganGerak = false;
		lebarGerakan = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
		if (camsNow == 1) {
			posCamY += 61.5;
			posCamZ += 19;
			viewCamY -= 5.5;
			viewCamZ -= 50;
			CAMERA_SPEED += 0.69f;

			camsNow = 2;
		}
		else if (camsNow == 2) {
			posCamY -= 61.5;
			posCamZ -= 19;
			viewCamY += 5.5;
			viewCamZ += 50;
			CAMERA_SPEED -= 0.69f;

			camsNow = 1;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
		drawAll = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		drawAll = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		drawAll = 2;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		drawAll = 3;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
		drawAll = 4;
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
		drawAll = 5;
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
		drawAll = 6;
	}
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
		drawAll = 7;
	}
}

void Demo::Update(double deltaTime) {
	angle += (float)((deltaTime * 1.5f) / 100);

	if ((lebarGerakan < -0.3f || lebarGerakan > 0.3f)) {
		speedX *= -1;
		speedZ *= -1;
	}
	lebarGerakan += (float)((deltaTime * speedX) / 1000);
}

void Demo::Render() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(55.0f / 255.0f, 198.0f / 255.0f, 255.0f / 255.0f, 1.0f);

	// Step 1 Render depth of scene to texture
	// ----------------------------------------
	glm::vec3 lightPos = glm::vec3(0.0f, 50.0f, -30.0f);

	glm::mat4 lightProjection, lightView;
	glm::mat4 lightSpaceMatrix;
	float near_plane = 10.0f;
	float far_plane = 200.0f;
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	lightView = glm::lookAt(glm::vec3(lightPos.x, lightPos.y, lightPos.z), glm::vec3(pindahX, pindahY, -54+pindahZ), glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;
	// render scene from light's point of view
	UseShader(this->depthmapShader);
	glUniformMatrix4fv(glGetUniformLocation(this->depthmapShader, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
	glViewport(0, 0, this->SHADOW_WIDTH, this->SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);

	// Pedestrian
	if (drawAll > 0) {
		DrawHead(this->depthmapShader);
		DrawBody(this->depthmapShader);
		DrawHand(this->depthmapShader, 1, 1.3, 4, 0);
		DrawHand(this->depthmapShader, 2, -1.3, 4, 0);
		DrawLeg(this->depthmapShader, 1, -0.5, 1, 0);
		DrawLeg(this->depthmapShader, 2, 0.5, 1, 0);
	}

	// Hedge Points
	const int totalHedge = 24;
	double hedgeX[totalHedge] = {};
	double hedgeZ[totalHedge] = {};
	double hedgeXSize[totalHedge] = {};
	double hedgeZSize[totalHedge] = {};

	hedgeX[0] = -26;
	hedgeZ[0] = -39;
	hedgeXSize[0] = 31;
	hedgeZSize[0] = 5;

	hedgeX[1] = -39;
	hedgeZ[1] = -26;
	hedgeXSize[1] = 5;
	hedgeZSize[1] = 31;

	hedgeX[2] = 26;
	hedgeZ[2] = -39;
	hedgeXSize[2] = 31;
	hedgeZSize[2] = 5;

	hedgeX[3] = 39;
	hedgeZ[3] = -26;
	hedgeXSize[3] = 5;
	hedgeZSize[3] = 31;

	hedgeX[4] = -26;
	hedgeZ[4] = 39;
	hedgeXSize[4] = 31;
	hedgeZSize[4] = 5;

	hedgeX[5] = -39;
	hedgeZ[5] = 26;
	hedgeXSize[5] = 5;
	hedgeZSize[5] = 31;

	hedgeX[6] = 26;
	hedgeZ[6] = 39;
	hedgeXSize[6] = 31;
	hedgeZSize[6] = 5;

	hedgeX[7] = 39;
	hedgeZ[7] = 26;
	hedgeXSize[7] = 5;
	hedgeZSize[7] = 31;

	hedgeX[8] = -26;
	hedgeZ[8] = -49;
	hedgeXSize[8] = 31;
	hedgeZSize[8] = 5;

	hedgeX[9] = -49;
	hedgeZ[9] = -26;
	hedgeXSize[9] = 5;
	hedgeZSize[9] = 31;

	hedgeX[10] = 26;
	hedgeZ[10] = -49;
	hedgeXSize[10] = 31;
	hedgeZSize[10] = 5;

	hedgeX[11] = 49;
	hedgeZ[11] = -26;
	hedgeXSize[11] = 5;
	hedgeZSize[11] = 31;

	hedgeX[12] = -26;
	hedgeZ[12] = 49;
	hedgeXSize[12] = 31;
	hedgeZSize[12] = 5;

	hedgeX[13] = -49;
	hedgeZ[13] = 26;
	hedgeXSize[13] = 5;
	hedgeZSize[13] = 31;

	hedgeX[14] = 26;
	hedgeZ[14] = 49;
	hedgeXSize[14] = 31;
	hedgeZSize[14] = 5;

	hedgeX[15] = 49;
	hedgeZ[15] = 26;
	hedgeXSize[15] = 5;
	hedgeZSize[15] = 31;

	hedgeX[16] = -31;
	hedgeZ[16] = -59;
	hedgeXSize[16] = 41;
	hedgeZSize[16] = 5;

	hedgeX[17] = -59;
	hedgeZ[17] = -31;
	hedgeXSize[17] = 5;
	hedgeZSize[17] = 41;

	hedgeX[18] = 31;
	hedgeZ[18] = -59;
	hedgeXSize[18] = 41;
	hedgeZSize[18] = 5;

	hedgeX[19] = 59;
	hedgeZ[19] = -31;
	hedgeXSize[19] = 5;
	hedgeZSize[19] = 41;

	hedgeX[20] = -31;
	hedgeZ[20] = 59;
	hedgeXSize[20] = 41;
	hedgeZSize[20] = 5;

	hedgeX[21] = -59;
	hedgeZ[21] = 31;
	hedgeXSize[21] = 5;
	hedgeZSize[21] = 41;

	hedgeX[22] = 31;
	hedgeZ[22] = 59;
	hedgeXSize[22] = 41;
	hedgeZSize[22] = 5;

	hedgeX[23] = 59;
	hedgeZ[23] = 31;
	hedgeXSize[23] = 5;
	hedgeZSize[23] = 41;

	// Lamp Points
	const int totalLamp = 24;
	double lampX[totalLamp] = {};
	double lampZ[totalLamp] = {};

	lampX[0] = -7.5;
	lampZ[0] = -39;

	lampX[1] = -7.5;
	lampZ[1] = -49;

	lampX[2] = -7.5;
	lampZ[2] = -59;

	lampX[3] = 7.5;
	lampZ[3] = -39;

	lampX[4] = 7.5;
	lampZ[4] = -49;

	lampX[5] = 7.5;
	lampZ[5] = -59;

	lampX[6] = -39;
	lampZ[6] = 7.5;

	lampX[7] = -49;
	lampZ[7] = 7.5;

	lampX[8] = -59;
	lampZ[8] = 7.5;

	lampX[9] = -39;
	lampZ[9] = -7.5;

	lampX[10] = -49;
	lampZ[10] = -7.5;

	lampX[11] = -59;
	lampZ[11] = -7.5;

	lampX[12] = -7.5;
	lampZ[12] = 39;

	lampX[13] = -7.5;
	lampZ[13] = 49;

	lampX[14] = -7.5;
	lampZ[14] = 59;

	lampX[15] = 7.5;
	lampZ[15] = 39;

	lampX[16] = 7.5;
	lampZ[16] = 49;

	lampX[17] = 7.5;
	lampZ[17] = 59;

	lampX[18] = 39;
	lampZ[18] = 7.5;

	lampX[19] = 49;
	lampZ[19] = 7.5;

	lampX[20] = 59;
	lampZ[20] = 7.5;

	lampX[21] = 39;
	lampZ[21] = -7.5;

	lampX[22] = 49;
	lampZ[22] = -7.5;

	lampX[23] = 59;
	lampZ[23] = -7.5;

	// Tree Points
	const int totalTree = 8;
	double treeX[totalTree] = {};
	double treeZ[totalTree] = {};
	string treeType[totalTree] = {};

	treeX[0] = -49;
	treeZ[0] = -49;
	treeType[0] = "Birch";

	treeX[1] = -59;
	treeZ[1] = -59;
	treeType[1] = "Oak";

	treeX[2] = 49;
	treeZ[2] = -49;
	treeType[2] = "Oak";

	treeX[3] = 59;
	treeZ[3] = -59;
	treeType[3] = "Birch";

	treeX[4] = 49;
	treeZ[4] = 49;
	treeType[4] = "Birch";

	treeX[5] = 59;
	treeZ[5] = 59;
	treeType[5] = "Oak";

	treeX[6] = -49;
	treeZ[6] = 49;
	treeType[6] = "Oak";

	treeX[7] = -59;
	treeZ[7] = 59;
	treeType[7] = "Birch";

	// Windmill
	if (drawAll > 1) {
		DrawFoundation(this->depthmapShader);

		DrawCenter(this->depthmapShader, 0, 25, -15, 1, 1, 5);
		DrawCenter(this->depthmapShader, 0, 25, -17.5, 1.5, 1.5, 1.5);
		DrawPinwheel(this->depthmapShader, 1, 0, 25, -17.5, 30, 2, 0.1);
		DrawPinwheel(this->depthmapShader, 1, 0, 25, -17.5, 2, 30, 0.1);
		DrawPropeller(this->depthmapShader, 0, 25, -16.5, 32, 4, 0.1);
		DrawPropeller(this->depthmapShader, 0, 25, -16.5, 4, 32, 0.1);

		DrawCenter(this->depthmapShader, 0, 10, -16.2, 5, 7.5, 0.5);
		DrawPinwheel(this->depthmapShader, 0, 0, 13.5, -16.5, 5, 0.5, 0.5);
		DrawPinwheel(this->depthmapShader, 0, 0, 10, -16.5, 5, 0.5, 0.5);
		DrawPinwheel(this->depthmapShader, 0, 0, 6.5, -16.5, 5, 0.5, 0.5);
		DrawPinwheel(this->depthmapShader, 0, -2.5, 10, -16.5, 0.5, 7.5, 0.5);
		DrawPinwheel(this->depthmapShader, 0, 0, 10, -16.5, 0.5, 7.5, 0.5);
		DrawPinwheel(this->depthmapShader, 0, 2.5, 10, -16.5, 0.5, 7.5, 0.5);
	}

	// Hedge
	if (drawAll > 2) {
		for (int i = 0; i < totalHedge; i++) {
			DrawPinwheel(this->depthmapShader, 0, hedgeX[i], -0.25, hedgeZ[i], hedgeXSize[i], 0.5, hedgeZSize[i]);
			DrawHedge(this->depthmapShader, hedgeX[i], 2.5, hedgeZ[i], hedgeXSize[i], 5, hedgeZSize[i]);
		}
	}

	// Lamp
	if (drawAll > 3) {
		for (int i = 0; i < totalLamp; i++) {
			DrawPinwheel(this->depthmapShader, 0, lampX[i], -0.25, lampZ[i], 1.5, 0.5, 1.5);
			DrawCenter(this->depthmapShader, lampX[i], 1, lampZ[i], 0.75, 4, 0.75);
			DrawPinwheel(this->depthmapShader, 0, lampX[i], 3, lampZ[i], 2, 0.5, 2);
			DrawLamp(this->depthmapShader, lampX[i], 3.75, lampZ[i]);
		}
	}

	// Tree
	if (drawAll > 4) {
		for (int i = 0; i < totalTree; i++) {
			if (treeType[i] == "Oak") {
				DrawDarkOak(this->depthmapShader, treeX[i], -0.5, treeZ[i], 1.5, 10, 1.5);
				DrawDarkLeaf(this->depthmapShader, treeX[i] + 1.5, 10, treeZ[i] - 1, 4.5, 5, 4.5);
				DrawDarkLeaf(this->depthmapShader, treeX[i] - 1.5, 12.5, treeZ[i], 4.5, 5, 4.5);
				DrawDarkLeaf(this->depthmapShader, treeX[i] - 3, 9.5, treeZ[i] + 1, 4.5, 5, 4.5);
			}
			else {
				DrawBirch(this->depthmapShader, treeX[i], -0.5, treeZ[i], 1.5, 10, 1.5);
				DrawBirchLeaf(this->depthmapShader, treeX[i] - 1.5, 10, treeZ[i] - 1, 4.5, 5, 4.5);
				DrawBirchLeaf(this->depthmapShader, treeX[i] + 1.5, 12.5, treeZ[i], 4.5, 5, 4.5);
				DrawBirchLeaf(this->depthmapShader, treeX[i] + 3, 9.5, treeZ[i] + 1, 4.5, 5, 4.5);
			}
		}
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	// Step 2 Render scene normally using generated depth map
	// ------------------------------------------------------
	glViewport(0, 0, this->screenWidth, this->screenHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Pass perspective projection matrix
	UseShader(this->shadowmapShader);
	glm::mat4 projection = glm::perspective(fovy, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 200.0f);
	GLint projLoc = glGetUniformLocation(this->shadowmapShader, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// LookAt camera (position, target/direction, up)
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	GLint viewLoc = glGetUniformLocation(this->shadowmapShader, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// Setting Light Attributes
	glUniformMatrix4fv(glGetUniformLocation(this->shadowmapShader, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
	glUniform3f(glGetUniformLocation(this->shadowmapShader, "viewPos"), posCamX, posCamY, posCamZ);
	glUniform3f(glGetUniformLocation(this->shadowmapShader, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// Configure Shaders
	glUniform1i(glGetUniformLocation(this->shadowmapShader, "diffuseTexture"), 0);
	glUniform1i(glGetUniformLocation(this->shadowmapShader, "shadowMap"), 1);

	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ZERO);

	// Skybox
	if (drawAll > 6) {
		DrawSkybox(this->shadowmapShader);
	}

	// Light Source
	DrawPinwheel(this->shadowmapShader, 0, lightPos.x, lightPos.y, lightPos.z, 1, 1, 1);

	// Plane
	DrawColoredPlane(this->shadowmapShader);

	// Road
	const int totalRoad = 16;
	double roadX[totalRoad] = {};
	double roadZ[totalRoad] = {};
	double roadLength[totalRoad] = {};
	string roadType[totalRoad] = {};
	int turnType[totalRoad] = {};

	roadX[0] = 0;
	roadZ[0] = -60;
	roadLength[0] = 10;
	roadType[0] = "Vertical";

	roadX[1] = 0;
	roadZ[1] = -30;
	roadType[1] = "Turn";
	turnType[1] = 4;

	roadX[2] = 33;
	roadZ[2] = 0;
	roadLength[2] = 10;
	roadType[2] = "Horizontal";

	roadX[3] = 30;
	roadZ[3] = 0;
	roadType[3] = "Turn";
	turnType[3] = 1;

	roadX[4] = 0;
	roadZ[4] = 33;
	roadLength[4] = 10;
	roadType[4] = "Vertical";

	roadX[5] = 0;
	roadZ[5] = 30;
	roadType[5] = "Turn";
	turnType[5] = 2;

	roadX[6] = -63;
	roadZ[6] = 0;
	roadLength[6] = 10;
	roadType[6] = "Horizontal";

	roadX[7] = -30;
	roadZ[7] = 0;
	roadType[7] = "Turn";
	turnType[7] = 3;

	roadX[8] = -30;
	roadZ[8] = -30;
	roadType[8] = "Turn";
	turnType[8] = 5;

	roadX[9] = 30;
	roadZ[9] = -30;
	roadType[9] = "Turn";
	turnType[9] = 6;

	roadX[10] = 30;
	roadZ[10] = 30;
	roadType[10] = "Turn";
	turnType[10] = 7;

	roadX[11] = -30;
	roadZ[11] = 30;
	roadType[11] = "Turn";
	turnType[11] = 8;

	roadX[12] = -30;
	roadZ[12] = -30;
	roadLength[12] = 20;
	roadType[12] = "Horizontal";

	roadX[13] = -30;
	roadZ[13] = 30;
	roadLength[13] = 20;
	roadType[13] = "Horizontal";

	roadX[14] = -30;
	roadZ[14] = -30;
	roadLength[14] = 20;
	roadType[14] = "Vertical";

	roadX[15] = 30;
	roadZ[15] = -30;
	roadLength[15] = 20;
	roadType[15] = "Vertical";

	if (drawAll > 5) {
		for (int i = 0; i < totalRoad; i++) {
			if (roadType[i] != "Turn") {
				for (int j = 0; j < roadLength[i]; j++) {
					if (roadType[i] == "Vertical") {
						DrawCobble(this->shadowmapShader, roadX[i], -0.5, roadZ[i] + (j * 3), 3, 0.1, 3);
						DrawStone(this->shadowmapShader, roadX[i] + 3, -0.5, roadZ[i] + (j * 3), 3, 0.1, 3);
						DrawStone(this->shadowmapShader, roadX[i] - 3, -0.5, roadZ[i] + (j * 3), 3, 0.1, 3);
					}
					else {
						DrawCobble(this->shadowmapShader, roadX[i] + (j * 3), -0.5, roadZ[i], 3, 0.1, 3);
						DrawStone(this->shadowmapShader, roadX[i] + (j * 3), -0.5, roadZ[i] + 3, 3, 0.1, 3);
						DrawStone(this->shadowmapShader, roadX[i] + (j * 3), -0.5, roadZ[i] - 3, 3, 0.1, 3);
					}
				}
			}
			else {
				DrawCobble(this->shadowmapShader, roadX[i], -0.5, roadZ[i], 3, 0.1, 3);
				if (turnType[i] == 1) {
					DrawCobble(this->shadowmapShader, roadX[i], -0.5, roadZ[i] - 3, 3, 0.1, 3);
					DrawCobble(this->shadowmapShader, roadX[i] + 3, -0.5, roadZ[i], 3, 0.1, 3);
					DrawCobble(this->shadowmapShader, roadX[i], -0.5, roadZ[i] + 3, 3, 0.1, 3);
				}
				else if (turnType[i] == 2) {
					DrawCobble(this->shadowmapShader, roadX[i] + 3, -0.5, roadZ[i], 3, 0.1, 3);
					DrawCobble(this->shadowmapShader, roadX[i], -0.5, roadZ[i] + 3, 3, 0.1, 3);
					DrawCobble(this->shadowmapShader, roadX[i] - 3, -0.5, roadZ[i], 3, 0.1, 3);
				}
				else if (turnType[i] == 3) {
					DrawCobble(this->shadowmapShader, roadX[i], -0.5, roadZ[i] + 3, 3, 0.1, 3);
					DrawCobble(this->shadowmapShader, roadX[i] - 3, -0.5, roadZ[i], 3, 0.1, 3);
					DrawCobble(this->shadowmapShader, roadX[i], -0.5, roadZ[i] - 3, 3, 0.1, 3);
				}
				else if (turnType[i] == 4) {
					DrawCobble(this->shadowmapShader, roadX[i] - 3, -0.5, roadZ[i], 3, 0.1, 3);
					DrawCobble(this->shadowmapShader, roadX[i], -0.5, roadZ[i] - 3, 3, 0.1, 3);
					DrawCobble(this->shadowmapShader, roadX[i] + 3, -0.5, roadZ[i], 3, 0.1, 3);
				}
				else if (turnType[i] == 5) {
					DrawCobble(this->shadowmapShader, roadX[i] + 3, -0.5, roadZ[i], 3, 0.1, 3);
					DrawCobble(this->shadowmapShader, roadX[i], -0.5, roadZ[i] + 3, 3, 0.1, 3);
				}
				else if (turnType[i] == 6) {
					DrawCobble(this->shadowmapShader, roadX[i], -0.5, roadZ[i] + 3, 3, 0.1, 3);
					DrawCobble(this->shadowmapShader, roadX[i] - 3, -0.5, roadZ[i], 3, 0.1, 3);
				}
				else if (turnType[i] == 7) {
					DrawCobble(this->shadowmapShader, roadX[i] - 3, -0.5, roadZ[i], 3, 0.1, 3);
					DrawCobble(this->shadowmapShader, roadX[i], -0.5, roadZ[i] - 3, 3, 0.1, 3);
				}
				else if (turnType[i] == 8) {
					DrawCobble(this->shadowmapShader, roadX[i], -0.5, roadZ[i] - 3, 3, 0.1, 3);
					DrawCobble(this->shadowmapShader, roadX[i] + 3, -0.5, roadZ[i], 3, 0.1, 3);
				}

				for (int j = 0; j < 3; j++) {
					DrawStone(this->shadowmapShader, roadX[i], -0.5, roadZ[i] - 3 + (j * 3), 3, 0.1, 3);
					DrawStone(this->shadowmapShader, roadX[i] + 3, -0.5, roadZ[i] - 3 + (j * 3), 3, 0.1, 3);
					DrawStone(this->shadowmapShader, roadX[i] - 3, -0.5, roadZ[i] - 3 + (j * 3), 3, 0.1, 3);
				}
			}
		}
	}

	// Pedestrian
	if (drawAll > 0) {
		DrawHead(this->shadowmapShader);
		DrawBody(this->shadowmapShader);
		DrawHand(this->shadowmapShader, 1, 1.3, 4, 0);
		DrawHand(this->shadowmapShader, 2, -1.3, 4, 0);
		DrawLeg(this->shadowmapShader, 1, -0.5, 1, 0);
		DrawLeg(this->shadowmapShader, 2, 0.5, 1, 0);
	}
	
	// Windmill
	if (drawAll > 1) {
		DrawFoundation(this->shadowmapShader);

		DrawCenter(this->shadowmapShader, 0, 25, -15, 1, 1, 5);
		DrawCenter(this->shadowmapShader, 0, 25, -17.5, 1.5, 1.5, 1.5);
		DrawPinwheel(this->shadowmapShader, 1, 0, 25, -17.5, 30, 2, 0.1);
		DrawPinwheel(this->shadowmapShader, 1, 0, 25, -17.5, 2, 30, 0.1);
		DrawPropeller(this->shadowmapShader, 0, 25, -16.5, 32, 4, 0.1);
		DrawPropeller(this->shadowmapShader, 0, 25, -16.5, 4, 32, 0.1);

		DrawCenter(this->shadowmapShader, 0, 10, -16.2, 5, 7.5, 0.5);
		DrawPinwheel(this->shadowmapShader, 0, 0, 13.5, -16.5, 5, 0.5, 0.5);
		DrawPinwheel(this->shadowmapShader, 0, 0, 10, -16.5, 5, 0.5, 0.5);
		DrawPinwheel(this->shadowmapShader, 0, 0, 6.5, -16.5, 5, 0.5, 0.5);
		DrawPinwheel(this->shadowmapShader, 0, -2.5, 10, -16.5, 0.5, 7.5, 0.5);
		DrawPinwheel(this->shadowmapShader, 0, 0, 10, -16.5, 0.5, 7.5, 0.5);
		DrawPinwheel(this->shadowmapShader, 0, 2.5, 10, -16.5, 0.5, 7.5, 0.5);
	}
	
	// Hedge
	if (drawAll > 2) {
		for (int i = 0; i < totalHedge; i++) {
			DrawPinwheel(this->shadowmapShader, 0, hedgeX[i], -0.25, hedgeZ[i], hedgeXSize[i], 0.5, hedgeZSize[i]);
			DrawHedge(this->shadowmapShader, hedgeX[i], 2.5, hedgeZ[i], hedgeXSize[i], 5, hedgeZSize[i]);
		}
	}
	
	// Lamp
	if (drawAll > 3) {
		for (int i = 0; i < totalLamp; i++) {
			DrawPinwheel(this->shadowmapShader, 0, lampX[i], -0.25, lampZ[i], 1.5, 0.5, 1.5);
			DrawCenter(this->shadowmapShader, lampX[i], 1, lampZ[i], 0.75, 4, 0.75);
			DrawPinwheel(this->shadowmapShader, 0, lampX[i], 3, lampZ[i], 2, 0.5, 2);
			DrawLamp(this->shadowmapShader, lampX[i], 3.75, lampZ[i]);
		}
	}

	// Tree
	if (drawAll > 4) {
		for (int i = 0; i < totalTree; i++) {
			if (treeType[i] == "Oak") {
				DrawDarkOak(this->shadowmapShader, treeX[i], -0.5, treeZ[i], 1.5, 10, 1.5);
				DrawDarkLeaf(this->shadowmapShader, treeX[i] + 1.5, 10, treeZ[i] - 1, 4.5, 5, 4.5);
				DrawDarkLeaf(this->shadowmapShader, treeX[i] - 1.5, 12.5, treeZ[i], 4.5, 5, 4.5);
				DrawDarkLeaf(this->shadowmapShader, treeX[i] - 3, 9.5, treeZ[i] + 1, 4.5, 5, 4.5);
			}
			else {
				DrawBirch(this->shadowmapShader, treeX[i], -0.5, treeZ[i], 1.5, 10, 1.5);
				DrawBirchLeaf(this->shadowmapShader, treeX[i] - 1.5, 10, treeZ[i] - 1, 4.5, 5, 4.5);
				DrawBirchLeaf(this->shadowmapShader, treeX[i] + 1.5, 12.5, treeZ[i], 4.5, 5, 4.5);
				DrawBirchLeaf(this->shadowmapShader, treeX[i] + 3, 9.5, treeZ[i] + 1, 4.5, 5, 4.5);
			}
		}
	}

	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);

	// Windmill Glass
	if (drawAll > 1) {
		DrawGlass(this->shadowmapShader, 0, 10, -16.5, 5, 7.5, 0.5);
	}

	// Lamp Glass
	if (drawAll > 3) {
		for (int i = 0; i < totalLamp; i++) {
			DrawGlass(this->shadowmapShader, lampX[i], 4, lampZ[i], 2, 2, 2);
		}
	}

	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
}

// Skybox Things
void Demo::BuildSkybox() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture_skybox);
	glBindTexture(GL_TEXTURE_2D, texture_skybox);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("skybox.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, (1.0f / 4.0f), (1.0f / 3.0f), 0, 0, -1,  // 0
		0.5, -0.5, 0.5,  (2.0f / 4.0f), (1.0f / 3.0f), 0, 0, -1,   // 1
		0.5,  0.5, 0.5,  (2.0f / 4.0f), (2.0f / 3.0f), 0, 0, -1,   // 2
		-0.5,  0.5, 0.5, (1.0f / 4.0f), (2.0f / 3.0f), 0, 0, -1,  // 3

		// right	
		0.5, -0.5,  0.5, (2.0f / 4.0f), (1.0f / 3.0f), -1, 0, 0,  // 4
		0.5, -0.5, -0.5, (3.0f / 4.0f), (1.0f / 3.0f), -1, 0, 0,  // 5
		0.5,  0.5, -0.5, (3.0f / 4.0f), (2.0f / 3.0f), -1, 0, 0,  // 6
		0.5,  0.5,  0.5, (2.0f / 4.0f), (2.0f / 3.0f), -1, 0, 0,  // 7

		// back
		-0.5, -0.5, -0.5, (3.0f / 4.0f), (1.0f / 3.0f), 0, 0, 1, // 8 
		0.5,  -0.5, -0.5, (4.0f / 4.0f), (1.0f / 3.0f), 0, 0, 1, // 9
		0.5,   0.5, -0.5, (4.0f / 4.0f), (2.0f / 3.0f), 0, 0, 1, // 10
		-0.5,  0.5, -0.5, (3.0f / 4.0f), (2.0f / 3.0f), 0, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, (0.0f / 4.0f), (1.0f / 3.0f), 1, 0, 0, // 12
		-0.5, -0.5,  0.5, (1.0f / 4.0f), (1.0f / 3.0f), 1, 0, 0, // 13
		-0.5,  0.5,  0.5, (1.0f / 4.0f), (2.0f / 3.0f), 1, 0, 0, // 14
		-0.5,  0.5, -0.5, (0.0f / 4.0f), (2.0f / 3.0f), 1, 0, 0, // 15

		// upper
		0.5, 0.5,  0.5,  (1.0f / 4.0f), (2.0f / 3.0f),  0, -1, 0,  // 16
		-0.5, 0.5,  0.5, (2.0f / 4.0f), (2.0f / 3.0f),  0, -1, 0, // 17
		-0.5, 0.5, -0.5, (2.0f / 4.0f), (3.0f / 3.0f),  0, -1, 0, // 18
		0.5, 0.5, -0.5,  (1.0f / 4.0f), (3.0f / 3.0f),  0, -1, 0, // 19

		// bottom
		-0.5, -0.5, -0.5, (1.0f / 4.0f), (0.0f / 3.0f), 0, 1, 0, // 20
		0.5, -0.5, -0.5,  (2.0f / 4.0f), (0.0f / 3.0f), 0, 1, 0,  // 21
		0.5, -0.5,  0.5,  (2.0f / 4.0f), (1.0f / 3.0f), 0, 1, 0,  // 22
		-0.5, -0.5,  0.5, (1.0f / 4.0f), (1.0f / 3.0f), 0, 1, 0, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO_skybox);
	glGenBuffers(1, &VBO_skybox);
	glGenBuffers(1, &EBO_skybox);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_skybox);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_skybox);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_skybox);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);;

	// define Vector Normal pointer layout 1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawSkybox(GLuint shader)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_skybox);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO_skybox); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(0, 25, 0));
	model = glm::scale(model, glm::vec3(200, 200, 200));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// Plane Things
void Demo::BuildColoredPlane()
{
	// Load and create a texture 
	glGenTextures(1, &texture_plane);
	glBindTexture(GL_TEXTURE_2D, texture_plane);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("grass.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	//// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-100.0, -0.5, -100.0,  0,  0, 0, 1, 0,
		 100.0, -0.5, -100.0, 10,  0, 0, 1, 0,
		 100.0, -0.5,  100.0, 10, 10, 0, 1, 0,
		-100.0, -0.5,  100.0,  0, 10, 0, 1, 0,
	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &VAO_plane);
	glGenBuffers(1, &VBO_plane);
	glGenBuffers(1, &EBO_plane);

	glBindVertexArray(VAO_plane);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_plane);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_plane);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define Vector Normal pointer layout 1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}
void Demo::DrawColoredPlane(GLuint shader)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_plane);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO_plane); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// Pedestrian Things
void Demo::BuildHead() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture_pedestrian);
	glBindTexture(GL_TEXTURE_2D, texture_pedestrian);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image(skinType.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, (2.0f / 16.0f), (4.0f / 8.0f), 0, 0, 1,  // 0
		0.5, -0.5, 0.5,  (4.0f / 16.0f), (4.0f / 8.0f), 0, 0, 1,   // 1
		0.5,  0.5, 0.5,  (4.0f / 16.0f), (6.0f / 8.0f), 0, 0, 1,   // 2
		-0.5,  0.5, 0.5, (2.0f / 16.0f), (6.0f / 8.0f), 0, 0, 1,  // 3

		// right	
		0.5, -0.5,  0.5, (4.0f / 16.0f), (4.0f / 8.0f), 1, 0, 0,  // 4
		0.5, -0.5, -0.5, (6.0f / 16.0f), (4.0f / 8.0f), 1, 0, 0,  // 5
		0.5,  0.5, -0.5, (6.0f / 16.0f), (6.0f / 8.0f), 1, 0, 0,  // 6
		0.5,  0.5,  0.5, (4.0f / 16.0f), (6.0f / 8.0f), 1, 0, 0,  // 7

		// back
		-0.5, -0.5, -0.5, (6.0f / 16.0f), (4.0f / 8.0f), 0, 0, -1, // 8 
		0.5,  -0.5, -0.5, (8.0f / 16.0f), (4.0f / 8.0f), 0, 0, -1, // 9
		0.5,   0.5, -0.5, (8.0f / 16.0f), (6.0f / 8.0f), 0, 0, -1, // 10
		-0.5,  0.5, -0.5, (6.0f / 16.0f), (6.0f / 8.0f), 0, 0, -1, // 11

		// left
		-0.5, -0.5, -0.5, (0.0f / 16.0f), (4.0f / 8.0f), -1, 0, 0, // 12
		-0.5, -0.5,  0.5, (2.0f / 16.0f), (4.0f / 8.0f), -1, 0, 0, // 13
		-0.5,  0.5,  0.5, (2.0f / 16.0f), (6.0f / 8.0f), -1, 0, 0, // 14
		-0.5,  0.5, -0.5, (0.0f / 16.0f), (6.0f / 8.0f), -1, 0, 0, // 15

		// upper
		0.5, 0.5,  0.5,  (2.0f / 16.0f), (6.0f / 8.0f),  0, 1, 0,  // 16
		-0.5, 0.5,  0.5, (4.0f / 16.0f), (6.0f / 8.0f),  0, 1, 0, // 17
		-0.5, 0.5, -0.5, (4.0f / 16.0f), (8.0f / 8.0f),  0, 1, 0, // 18
		0.5, 0.5, -0.5,  (2.0f / 16.0f), (8.0f / 8.0f),  0, 1, 0, // 19

		// bottom
		-0.5, -0.5, -0.5, (4.0f / 16.0f), (6.0f / 8.0f), 0, -1, 0, // 20
		0.5, -0.5, -0.5,  (6.0f / 16.0f), (6.0f / 8.0f), 0, -1, 0,  // 21
		0.5, -0.5,  0.5,  (6.0f / 16.0f), (8.0f / 8.0f), 0, -1, 0,  // 22
		-0.5, -0.5,  0.5, (4.0f / 16.0f), (8.0f / 8.0f), 0, -1, 0, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO_head);
	glGenBuffers(1, &VBO_head);
	glGenBuffers(1, &EBO_head);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_head);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_head);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_head);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);;

	// define Vector Normal pointer layout 1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawHead(GLuint shader)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_pedestrian);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO_head); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(0 + pindahX, 6, -50 + pindahZ));

	model = glm::rotate(model, arahBadan, glm::vec3(0, 1, 0));

	model = glm::scale(model, glm::vec3(1.5, 1.5, 1.5));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildBody() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture_pedestrian);
	glBindTexture(GL_TEXTURE_2D, texture_pedestrian);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image(skinType.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, (5.0f / 16.0f), (0.0f / 8.0f), 0, 0, 1,  // 0
		0.5, -0.5, 0.5,  (7.0f / 16.0f), (0.0f / 8.0f), 0, 0, 1,   // 1
		0.5,  0.5, 0.5,  (7.0f / 16.0f), (3.0f / 8.0f), 0, 0, 1,   // 2
		-0.5,  0.5, 0.5, (5.0f / 16.0f), (3.0f / 8.0f), 0, 0, 1,  // 3

		// right	
		0.5, -0.5,  0.5, (4.0f / 16.0f), (0.0f / 8.0f), 1, 0, 0,  // 4
		0.5, -0.5, -0.5, (5.0f / 16.0f), (0.0f / 8.0f), 1, 0, 0,  // 5
		0.5,  0.5, -0.5, (5.0f / 16.0f), (3.0f / 8.0f), 1, 0, 0,  // 6
		0.5,  0.5,  0.5, (4.0f / 16.0f), (3.0f / 8.0f), 1, 0, 0,  // 7

		// back
		-0.5, -0.5, -0.5, (8.0f / 16.0f), (0.0f / 8.0f),  0, 0, -1, // 8 
		0.5,  -0.5, -0.5, (10.0f / 16.0f), (0.0f / 8.0f), 0, 0, -1, // 9
		0.5,   0.5, -0.5, (10.0f / 16.0f), (3.0f / 8.0f), 0, 0, -1,  // 10
		-0.5,  0.5, -0.5, (8.0f / 16.0f), (3.0f / 8.0f),  0, 0, -1, // 11

		// left
		-0.5, -0.5, -0.5, (7.0f / 16.0f), (0.0f / 8.0f), -1, 0, 0, // 12
		-0.5, -0.5,  0.5, (8.0f / 16.0f), (0.0f / 8.0f), -1, 0, 0, // 13
		-0.5,  0.5,  0.5, (8.0f / 16.0f), (3.0f / 8.0f), -1, 0, 0, // 14
		-0.5,  0.5, -0.5, (7.0f / 16.0f), (3.0f / 8.0f), -1, 0, 0, // 15

		// upper
		0.5, 0.5,  0.5,  (5.0f / 16.0f), (3.0f / 8.0f),  0, 1, 0,  // 16
		-0.5, 0.5,  0.5, (7.0f / 16.0f), (3.0f / 8.0f),  0, 1, 0, // 17
		-0.5, 0.5, -0.5, (7.0f / 16.0f), (4.0f / 8.0f),  0, 1, 0, // 18
		0.5, 0.5, -0.5,  (5.0f / 16.0f), (4.0f / 8.0f),  0, 1, 0, // 19

		// bottom
		-0.5, -0.5, -0.5, (7.0f / 16.0f), (3.0f / 8.0f), 0, -1, 0,  // 20
		0.5, -0.5, -0.5,  (9.0f / 16.0f), (3.0f / 8.0f), 0, -1, 0,  // 21
		0.5, -0.5,  0.5,  (9.0f / 16.0f), (4.0f / 8.0f), 0, -1, 0,  // 22
		-0.5, -0.5,  0.5, (7.0f / 16.0f), (4.0f / 8.0f), 0, -1, 0, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO_body);
	glGenBuffers(1, &VBO_body);
	glGenBuffers(1, &EBO_body);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_body);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_body);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_body);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define Vector Normal pointer layout 1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawBody(GLuint shader)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_pedestrian);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO_body); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(0 + pindahX, 4, -50 + pindahZ));

	model = glm::rotate(model, arahBadan, glm::vec3(0, 1, 0));

	model = glm::scale(model, glm::vec3(2, 3, 1));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildHand() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture_pedestrian);
	glBindTexture(GL_TEXTURE_2D, texture_pedestrian);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image(skinType.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, (11.0f / 16.0f), (0.0f / 8.0f), 0, 0, 1,  // 0
		0.5, -0.5, 0.5,  (12.0f / 16.0f), (0.0f / 8.0f), 0, 0, 1,   // 1
		0.5,  0.5, 0.5,  (12.0f / 16.0f), (3.0f / 8.0f), 0, 0, 1,   // 2
		-0.5,  0.5, 0.5, (11.0f / 16.0f), (3.0f / 8.0f), 0, 0, 1,  // 3

		// right	
		0.5, -0.5,  0.5, (10.0f / 16.0f), (0.0f / 8.0f), 1, 0, 0,  // 4
		0.5, -0.5, -0.5, (11.0f / 16.0f), (0.0f / 8.0f), 1, 0, 0,  // 5
		0.5,  0.5, -0.5, (11.0f / 16.0f), (3.0f / 8.0f), 1, 0, 0,  // 6
		0.5,  0.5,  0.5, (10.0f / 16.0f), (3.0f / 8.0f), 1, 0, 0,  // 7

		// back
		-0.5, -0.5, -0.5, (13.0f / 16.0f), (0.0f / 8.0f), 0, 0, -1,// 8 
		0.5,  -0.5, -0.5, (14.0f / 16.0f), (0.0f / 8.0f), 0, 0, -1,// 9
		0.5,   0.5, -0.5, (14.0f / 16.0f), (3.0f / 8.0f), 0, 0, -1,// 10
		-0.5,  0.5, -0.5, (13.0f / 16.0f), (3.0f / 8.0f), 0, 0, -1,// 11

		// left
		-0.5, -0.5, -0.5, (12.0f / 16.0f), (0.0f / 8.0f), -1, 0, 0, // 12
		-0.5, -0.5,  0.5, (13.0f / 16.0f), (0.0f / 8.0f), -1, 0, 0, // 13
		-0.5,  0.5,  0.5, (13.0f / 16.0f), (3.0f / 8.0f), -1, 0, 0, // 14
		-0.5,  0.5, -0.5, (12.0f / 16.0f), (3.0f / 8.0f), -1, 0, 0, // 15

		// upper
		0.5, 0.5,  0.5,  (11.0f / 16.0f), (3.0f / 8.0f),  0, 1, 0,  // 16
		-0.5, 0.5,  0.5, (12.0f / 16.0f), (3.0f / 8.0f),  0, 1, 0, // 17
		-0.5, 0.5, -0.5, (12.0f / 16.0f), (4.0f / 8.0f),  0, 1, 0, // 18
		0.5, 0.5, -0.5,  (11.0f / 16.0f), (4.0f / 8.0f),  0, 1, 0, // 19

		// bottom
		-0.5, -0.5, -0.5, (12.0f / 16.0f), (3.0f / 8.0f), 0, -1, 0, // 20
		0.5, -0.5, -0.5,  (13.0f / 16.0f), (3.0f / 8.0f), 0, -1, 0,  // 21
		0.5, -0.5,  0.5,  (13.0f / 16.0f), (4.0f / 8.0f), 0, -1, 0,  // 22
		-0.5, -0.5,  0.5, (12.0f / 16.0f), (4.0f / 8.0f), 0, -1, 0, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO_hand);
	glGenBuffers(1, &VBO_hand);
	glGenBuffers(1, &EBO_hand);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_hand);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_hand);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_hand);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define Vector Normal pointer layout 1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawHand(GLuint shader, int rotate, double positionX, double positionY, double positionZ)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_pedestrian);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO_hand); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(pindahX, pindahY, -50 + pindahZ));

	model = glm::rotate(model, arahBadan, glm::vec3(0, 1, 0));

	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));

	if (kakiTanganGerak) {
		if (rotate == 1) {
			model = glm::rotate(model, lebarGerakan, glm::vec3(1, 0, 0));
		}
		else if (rotate == 2) {
			model = glm::rotate(model, -lebarGerakan, glm::vec3(1, 0, 0));
		}
	}

	model = glm::scale(model, glm::vec3(0.7, 3, 1));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildLeg() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture_pedestrian);
	glBindTexture(GL_TEXTURE_2D, texture_pedestrian);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image(skinType.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, (1.0f / 16.0f), (0.0f / 8.0f), 0, 0, 1,  // 0
		0.5, -0.5, 0.5,  (2.0f / 16.0f), (0.0f / 8.0f), 0, 0, 1,   // 1
		0.5,  0.5, 0.5,  (2.0f / 16.0f), (3.0f / 8.0f), 0, 0, 1,   // 2
		-0.5,  0.5, 0.5, (1.0f / 16.0f), (3.0f / 8.0f), 0, 0, 1,  // 3

		// right	
		0.5, -0.5,  0.5, (0.0f / 16.0f), (0.0f / 8.0f), 1, 0, 0,  // 4
		0.5, -0.5, -0.5, (1.0f / 16.0f), (0.0f / 8.0f), 1, 0, 0,  // 5
		0.5,  0.5, -0.5, (1.0f / 16.0f), (3.0f / 8.0f), 1, 0, 0,  // 6
		0.5,  0.5,  0.5, (0.0f / 16.0f), (3.0f / 8.0f), 1, 0, 0,  // 7

		// back
		-0.5, -0.5, -0.5, (3.0f / 16.0f), (0.0f / 8.0f), 0, 0, -1, // 8 
		0.5,  -0.5, -0.5, (4.0f / 16.0f), (0.0f / 8.0f), 0, 0, -1, // 9
		0.5,   0.5, -0.5, (4.0f / 16.0f), (3.0f / 8.0f), 0, 0, -1, // 10
		-0.5,  0.5, -0.5, (3.0f / 16.0f), (3.0f / 8.0f), 0, 0, -1, // 11

		// left
		-0.5, -0.5, -0.5, (2.0f / 16.0f), (0.0f / 8.0f), -1, 0, 0, // 12
		-0.5, -0.5,  0.5, (3.0f / 16.0f), (0.0f / 8.0f), -1, 0, 0, // 13
		-0.5,  0.5,  0.5, (3.0f / 16.0f), (3.0f / 8.0f), -1, 0, 0, // 14
		-0.5,  0.5, -0.5, (2.0f / 16.0f), (3.0f / 8.0f), -1, 0, 0, // 15

		// upper
		0.5, 0.5,  0.5,  (1.0f / 16.0f), (3.0f / 8.0f), 0, 1, 0,   // 16
		-0.5, 0.5,  0.5, (2.0f / 16.0f), (3.0f / 8.0f), 0, 1, 0,  // 17
		-0.5, 0.5, -0.5, (2.0f / 16.0f), (4.0f / 8.0f), 0, 1, 0,  // 18
		0.5, 0.5, -0.5,  (1.0f / 16.0f), (4.0f / 8.0f), 0, 1, 0,  // 19

		// bottom
		-0.5, -0.5, -0.5, (2.0f / 16.0f), (3.0f / 8.0f), 0, -1, 0, // 20
		0.5, -0.5, -0.5,  (3.0f / 16.0f), (3.0f / 8.0f), 0, -1, 0,  // 21
		0.5, -0.5,  0.5,  (3.0f / 16.0f), (4.0f / 8.0f), 0, -1, 0,  // 22
		-0.5, -0.5,  0.5, (2.0f / 16.0f), (4.0f / 8.0f), 0, -1, 0, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO_leg);
	glGenBuffers(1, &VBO_leg);
	glGenBuffers(1, &EBO_leg);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_leg);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_leg);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_leg);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define Vector Normal pointer layout 1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawLeg(GLuint shader, int rotate, double positionX, double positionY, double positionZ)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_pedestrian);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO_leg); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(pindahX, pindahY, -50 + pindahZ));

	model = glm::rotate(model, arahBadan, glm::vec3(0, 1, 0));

	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));

	if (kakiTanganGerak) {
		if (rotate == 1) {
			model = glm::rotate(model, lebarGerakan, glm::vec3(1, 0, 0));
		}
		else if (rotate == 2) {
			model = glm::rotate(model, -lebarGerakan, glm::vec3(1, 0, 0));
		}
	}

	model = glm::scale(model, glm::vec3(1, 3, 1));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// Windmill Things
void Demo::BuildFoundation() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture_foundation);
	glBindTexture(GL_TEXTURE_2D, texture_foundation);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("redBrick.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -1, 0.9f,  0, 0,  0, 0, 1, // 0
		0.5, -1, 0.9f,   4, 0,  0, 0, 1, // 1
		0.25f, 1, 0.45f,  4, 4,0, 0, 1, // 2
		-0.25f, 1, 0.45f, 0, 4,0, 0, 1,  // 3

		// right1
		0.5, -1, 0.9f, 0, 0, 1, 0, 0.5, // 4
		1, -1, 0,      4, 0, 1, 0, 0.5, // 5
		0.5, 1, 0,     4, 4, 1, 0, 0.5, // 6
		0.25f, 1, 0.45f, 0, 4,1, 0, 0.5,  // 7

		// right2
		1, -1, 0,       0, 0, 1, 0, -0.5, // 8 
		0.5f, -1, -0.9f,  4, 0,1, 0, -0.5, // 9
		0.25f, 1, -0.45f, 4, 4,1, 0, -0.5, // 10
		0.5, 1, 0,      0, 4,1, 0, -0.5, // 11

		// back
		0.5, -1, -0.9f,   0, 0, 0, 0, -1,  // 12
		-0.5, -1, -0.9f,  4, 0, 0, 0, -1,  // 13
		-0.25f, 1, -0.45f, 4, 4, 0, 0, -1,  // 14
		0.25f, 1, -0.45f,  0, 4, 0, 0, -1,  // 15

		// left2
		-0.5, -1, -0.9f,  0, 0, -1, 0, -0.5, // 16
		-1, -1, 0,       4, 0, -1, 0, -0.5, // 17
		-0.5, 1, 0,      4, 4, -1, 0, -0.5, // 18
		-0.25f, 1, -0.45f, 0, 4, -1, 0, -0.5, // 19

		// left1
		-1, -1, 0,      0, 0, -1, 0, 0.5, // 20
		-0.5, -1, 0.9f,  4, 0, -1, 0, 0.5, // 21
		-0.25f, 1, 0.45f, 4, 4, -1, 0, 0.5, // 22
		-0.5, 1, 0,     0, 4, -1, 0, 0.5, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO_foundation);
	glGenBuffers(1, &VBO_foundation);
	glGenBuffers(1, &EBO_foundation);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_foundation);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_foundation);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_foundation);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define Vector Normal pointer layout 1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawFoundation(GLuint shader)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_foundation);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO_foundation); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(0, 19, 0));

	model = glm::scale(model, glm::vec3(20, 20, 20));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildCenter() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture_center);
	glBindTexture(GL_TEXTURE_2D, texture_center);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("grayBrick.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0, 0, 0, 1,// 0
		0.5, -0.5, 0.5, 1, 0, 0, 0, 1,  // 1
		0.5,  0.5, 0.5, 1, 1, 0, 0, 1,  // 2
		-0.5,  0.5, 0.5, 0, 1, 0, 0, 1, // 3

		// right
		0.5,  0.5,  0.5, 0, 0, 1, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0, 1, 0, 0, // 5
		0.5, -0.5, -0.5, 1, 1, 1, 0, 0, // 6
		0.5, -0.5,  0.5, 0, 1, 1, 0, 0, // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, 0, 0, -1, // 8 
		0.5,  -0.5, -0.5, 1, 0, 0, 0, -1,// 9
		0.5,   0.5, -0.5, 1, 1, 0, 0, -1,// 10
		-0.5,  0.5, -0.5, 0, 1, 0, 0, -1,// 11

		// left
		-0.5, -0.5, -0.5, 0, 0, -1, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, -1, 0, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, -1, 0, 0, // 14
		-0.5,  0.5, -0.5, 0, 1, -1, 0, 0, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0, 0, 1, 0, // 16
		-0.5, 0.5,  0.5, 1, 0,0, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,0, 1, 0,  // 18
		0.5, 0.5, -0.5, 0, 1, 0, 1, 0,  // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, 0, -1, 0,// 20
		0.5, -0.5, -0.5, 1, 0, 0, -1, 0, // 21
		0.5, -0.5,  0.5, 1, 1, 0, -1, 0, // 22
		-0.5, -0.5,  0.5, 0, 1,0, -1, 0, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO_default);
	glGenBuffers(1, &VBO_default);
	glGenBuffers(1, &EBO_default);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_default);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_default);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_default);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define Vector Normal pointer layout 1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawCenter(GLuint shader, double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	UseShader(shader);

	// Bind diffuse map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_center);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO_default); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));

	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildPinwheel() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture_pinwheel);
	glBindTexture(GL_TEXTURE_2D, texture_pinwheel);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("whiteBrick.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0, 0, 0, 1, // 0
		0.5, -0.5, 0.5, 1, 0,  0, 0, 1, // 1
		0.5,  0.5, 0.5, 1, 1,  0, 0, 1, // 2
		-0.5,  0.5, 0.5, 0, 1, 0, 0, 1, // 3

		// right
		0.5,  0.5,  0.5, 0, 0, 1, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0, 1, 0, 0, // 5
		0.5, -0.5, -0.5, 1, 1, 1, 0, 0, // 6
		0.5, -0.5,  0.5, 0, 1, 1, 0, 0, // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, 0, 0, -1, // 8 
		0.5,  -0.5, -0.5, 1, 0, 0, 0, -1, // 9
		0.5,   0.5, -0.5, 1, 1, 0, 0, -1, // 10
		-0.5,  0.5, -0.5, 0, 1, 0, 0, -1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, -1, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, -1, 0, 0,// 13
		-0.5,  0.5,  0.5, 1, 1, -1, 0, 0,// 14
		-0.5,  0.5, -0.5, 0, 1, -1, 0, 0,// 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   0, 1, 0, // 16
		-0.5, 0.5,  0.5, 1, 0,  0, 1, 0,// 17
		-0.5, 0.5, -0.5, 1, 1,  0, 1, 0,// 18
		0.5, 0.5, -0.5, 0, 1,   0, 1, 0,// 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, 0, -1, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  0, -1, 0, // 21
		0.5, -0.5,  0.5, 1, 1,  0, -1, 0, // 22
		-0.5, -0.5,  0.5, 0, 1, 0, -1, 0, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO_default);
	glGenBuffers(1, &VBO_default);
	glGenBuffers(1, &EBO_default);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_default);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_default);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_default);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define Vector Normal pointer layout 1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawPinwheel(GLuint shader, int rotate, double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_pinwheel);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO_default); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));

	if (rotate == 1) {
		model = glm::rotate(model, angle, glm::vec3(0, 0, 1));
	}

	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildPropeller() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture_propeller);
	glBindTexture(GL_TEXTURE_2D, texture_propeller);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("propeller.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0, 0, 0, 1,  // 0
		0.5, -0.5, 0.5, 1, 0,  0, 0, 1,   // 1
		0.5,  0.5, 0.5, 1, 1,  0, 0, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1, 0, 0, 1,   // 3

		// right
		0.5,  0.5,  0.5, 0, 0, 1, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0, 1, 0, 0,  // 5
		0.5, -0.5, -0.5, 1, 1, 1, 0, 0,  // 6
		0.5, -0.5,  0.5, 0, 1, 1, 0, 0,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, 0, 0, -1, // 8 
		0.5,  -0.5, -0.5, 10, 0, 0, 0, -1, // 9
		0.5,   0.5, -0.5, 10, 10,0, 0, -1,  // 10
		-0.5,  0.5, -0.5, 0, 10, 0, 0, -1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, -1, 0, 0,  // 12
		-0.5, -0.5,  0.5, 1, 0, -1, 0, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, -1, 0, 0, // 14
		-0.5,  0.5, -0.5, 0, 1, -1, 0, 0, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,  0, 1, 0,  // 16
		-0.5, 0.5,  0.5, 1, 0, 0, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1, 0, 1, 0,  // 18
		0.5, 0.5, -0.5, 0, 1,  0, 1, 0,  // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, 0, -1, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  0, -1, 0, // 21
		0.5, -0.5,  0.5, 1, 1,  0, -1, 0, // 22
		-0.5, -0.5,  0.5, 0, 1, 0, -1, 0, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO_propeller);
	glGenBuffers(1, &VBO_propeller);
	glGenBuffers(1, &EBO_propeller);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_propeller);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_propeller);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_propeller);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define Vector Normal pointer layout 1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawPropeller(GLuint shader, double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_propeller);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO_propeller); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));
	
	model = glm::rotate(model, angle, glm::vec3(0, 0, 1));
	
	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// Hedge Things
void Demo::BuildHedge() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture_hedge);
	glBindTexture(GL_TEXTURE_2D, texture_hedge);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("hedge.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0, 0.0f, 0.0f, 1.0f, // 0
		0.5, -0.5, 0.5, 2, 0,  0.0f, 0.0f, 1.0f,  // 1
		0.5,  0.5, 0.5, 2, 2,  0.0f, 0.0f, 1.0f,   // 2
		-0.5,  0.5, 0.5, 0, 2, 0.0f, 0.0f, 1.0f, // 3

		// right
		0.5,  0.5,  0.5, 0, 0, 1.0f, 0.0f, 0.0f, // 4
		0.5,  0.5, -0.5, 2, 0, 1.0f, 0.0f, 0.0f,  // 5
		0.5, -0.5, -0.5, 2, 2, 1.0f, 0.0f, 0.0f, // 6
		0.5, -0.5,  0.5, 0, 2, 1.0f, 0.0f, 0.0f,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, 0.0f, 0.0f, -1.0f,  // 8 
		0.5,  -0.5, -0.5, 2, 0, 0.0f, 0.0f, -1.0f,  // 9
		0.5,   0.5, -0.5, 2, 2, 0.0f, 0.0f, -1.0f, // 10
		-0.5,  0.5, -0.5, 0, 2, 0.0f, 0.0f, -1.0f, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, -1.0f, 0.0f, 0.0f,  // 12
		-0.5, -0.5,  0.5, 2, 0, -1.0f, 0.0f, 0.0f,  // 13
		-0.5,  0.5,  0.5, 2, 2, -1.0f, 0.0f, 0.0f, // 14
		-0.5,  0.5, -0.5, 0, 2, -1.0f, 0.0f, 0.0f,  // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,  0.0f, 1.0f, 0.0f, // 16
		-0.5, 0.5,  0.5, 2, 0, 0.0f, 1.0f, 0.0f, // 17
		-0.5, 0.5, -0.5, 2, 2, 0.0f, 1.0f, 0.0f,  // 18
		0.5, 0.5, -0.5, 0, 2,  0.0f, 1.0f, 0.0f,  // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, 0.0f, -1.0f, 0.0f, // 20
		0.5, -0.5, -0.5, 2, 0,  0.0f, -1.0f, 0.0f,  // 21
		0.5, -0.5,  0.5, 2, 2,  0.0f, -1.0f, 0.0f,  // 22
		-0.5, -0.5,  0.5, 0, 2, 0.0f, -1.0f, 0.0f,  // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO_hedge);
	glGenBuffers(1, &VBO_hedge);
	glGenBuffers(1, &EBO_hedge);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_hedge);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_hedge);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_hedge);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define Vector Normal pointer layout 1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawHedge(GLuint shader, double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_hedge);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO_hedge); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));

	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// Lamp Things
void Demo::BuildLamp() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture
	glGenTextures(1, &texture_lamp);
	glBindTexture(GL_TEXTURE_2D, texture_lamp);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("lamp.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0, 0, 0, 1, // 0
		0.5, -0.5, 0.5, 1, 0,  0, 0, 1,  // 1
		0.5,  0.5, 0.5, 1, 1,  0, 0, 1,  // 2
		-0.5,  0.5, 0.5, 0, 1, 0, 0, 1,  // 3
		// right
		0.5,  0.5,  0.5, 0, 0, 1, 0, 0, // 4
		0.5,  0.5, -0.5, 1, 0, 1, 0, 0, // 5
		0.5, -0.5, -0.5, 1, 1, 1, 0, 0, // 6
		0.5, -0.5,  0.5, 0, 1, 1, 0, 0, // 7
		// back
		-0.5, -0.5, -0.5, 0, 0, 0, 0, -1, // 8
		0.5,  -0.5, -0.5, 1, 0, 0, 0, -1, // 9
		0.5,   0.5, -0.5, 1, 1, 0, 0, -1, // 10
		-0.5,  0.5, -0.5, 0, 1, 0, 0, -1,  // 11
		// left
		-0.5, -0.5, -0.5, 0, 0, -1, 0, 0,// 12
		-0.5, -0.5,  0.5, 1, 0, -1, 0, 0,// 13
		-0.5,  0.5,  0.5, 1, 1, -1, 0, 0,// 14
		-0.5,  0.5, -0.5, 0, 1, -1, 0, 0,// 15
		// upper
		0.5, 0.5,  0.5, 0, 0,  0, 1, 0, // 16
		-0.5, 0.5,  0.5, 1, 0, 0, 1, 0, // 17
		-0.5, 0.5, -0.5, 1, 1, 0, 1, 0, // 18
		0.5, 0.5, -0.5, 0, 1,  0, 1, 0, // 19
		// bottom
		-0.5, -0.5, -0.5, 0, 0, 0, -1, 0,// 20
		0.5, -0.5, -0.5, 1, 0,  0, -1, 0,// 21
		0.5, -0.5,  0.5, 1, 1,  0, -1, 0,// 22
		-0.5, -0.5,  0.5, 0, 1, 0, -1, 0,// 23
	};
	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};
	glGenVertexArrays(1, &VAO_default);
	glGenBuffers(1, &VBO_default);
	glGenBuffers(1, &EBO_default);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_default);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_default);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_default);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// define Vector Normal pointer layout 1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawLamp(GLuint shader, double positionX, double positionY, double positionZ)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_lamp);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO_default); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));
	model = glm::scale(model, glm::vec3(1.25, 1.25, 1.25));
	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildGlass() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture
	glGenTextures(1, &texture_glass);
	glBindTexture(GL_TEXTURE_2D, texture_glass);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("glass.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0, 0, 0, 1, // 0
		0.5, -0.5, 0.5, 1, 0,  0, 0, 1,  // 1
		0.5,  0.5, 0.5, 1, 1,  0, 0, 1,  // 2
		-0.5,  0.5, 0.5, 0, 1, 0, 0, 1,  // 3
		// right
		0.5,  0.5,  0.5, 0, 0, 1, 0, 0, // 4
		0.5,  0.5, -0.5, 1, 0, 1, 0, 0, // 5
		0.5, -0.5, -0.5, 1, 1, 1, 0, 0, // 6
		0.5, -0.5,  0.5, 0, 1, 1, 0, 0, // 7
		// back
		-0.5, -0.5, -0.5, 0, 0, 0, 0, -1, // 8
		0.5,  -0.5, -0.5, 1, 0, 0, 0, -1, // 9
		0.5,   0.5, -0.5, 1, 1, 0, 0, -1, // 10
		-0.5,  0.5, -0.5, 0, 1, 0, 0, -1,  // 11
		// left
		-0.5, -0.5, -0.5, 0, 0, -1, 0, 0,// 12
		-0.5, -0.5,  0.5, 1, 0, -1, 0, 0,// 13
		-0.5,  0.5,  0.5, 1, 1, -1, 0, 0,// 14
		-0.5,  0.5, -0.5, 0, 1, -1, 0, 0,// 15
		// upper
		0.5, 0.5,  0.5, 0, 0,  0, 1, 0, // 16
		-0.5, 0.5,  0.5, 1, 0, 0, 1, 0, // 17
		-0.5, 0.5, -0.5, 1, 1, 0, 1, 0, // 18
		0.5, 0.5, -0.5, 0, 1,  0, 1, 0, // 19
		// bottom
		-0.5, -0.5, -0.5, 0, 0, 0, -1, 0,// 20
		0.5, -0.5, -0.5, 1, 0,  0, -1, 0,// 21
		0.5, -0.5,  0.5, 1, 1,  0, -1, 0,// 22
		-0.5, -0.5,  0.5, 0, 1, 0, -1, 0,// 23
	};
	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};
	glGenVertexArrays(1, &VAO_default);
	glGenBuffers(1, &VBO_default);
	glGenBuffers(1, &EBO_default);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_default);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_default);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_default);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// define Vector Normal pointer layout 1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawGlass(GLuint shader, double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_glass);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO_default); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));
	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));
	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// Tree Things
void Demo::BuildDarkOak() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture
	glGenTextures(1, &texture_darkOak);
	glBindTexture(GL_TEXTURE_2D, texture_darkOak);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("darkOak.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-1, 0, -1, 0, 0, 0, 0, 1,  // 0
		1, 0, -1, 5, 0,  0, 0, 1,  // 1
		0.25,  1, -0.25, 5, 5, 0, 0, 1,   // 2
		-0.25,  1, -0.25, 0, 5, 0, 0, 1,  // 3
		// right
		1, 0, -1, 0, 0, 1, 0, 0,  // 0
		1, 0, 1, 5, 0, 1, 0, 0,   // 1
		0.25,  1, 0.25, 5, 5,  1, 0, 0,  // 2
		0.25,  1, -0.25, 0, 5, 1, 0, 0,  // 3
		// back
		1, 0, 1, 0, 0, 0, 0, -1,  // 0
		-1, 0, 1, 5, 0,  0, 0, -1,  // 1
		-0.25,  1, 0.25, 5, 5,  0, 0, -1,  // 2
		0.25,  1, 0.25, 0, 5, 0, 0, -1,  // 3
		// left
		-1, 0, 1, 0, 0, -1, 0, 0,  // 0
		-1, 0, -1, 5, 0,  -1, 0, 0,  // 1
		-0.25,  1, -0.25, 5, 5,  -1, 0, 0,  // 2
		-0.25,  1, 0.25, 5, 5, -1, 0, 0,  // 3
	};
	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14
	};
	glGenVertexArrays(1, &VAO_tree);
	glGenBuffers(1, &VBO_tree);
	glGenBuffers(1, &EBO_tree);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_tree);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_tree);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_tree);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// define Vector Normal pointer layout 1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawDarkOak(GLuint shader, double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_darkOak);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO_tree); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));
	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));
	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildBirch() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture
	glGenTextures(1, &texture_birch);
	glBindTexture(GL_TEXTURE_2D, texture_birch);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("birch.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-1, 0, -1, 0, 0, 0, 0, 1,  // 0
		1, 0, -1, 5, 0,  0, 0, 1,  // 1
		0.25,  1, -0.25, 5, 5,  0, 0, 1,  // 2
		-0.25,  1, -0.25, 0, 5,  0, 0, 1, // 3
		// right
		1, 0, -1, 0, 0, 1, 0, 0,  // 0
		1, 0, 1, 5, 0, 1, 0, 0,   // 1
		0.25,  1, 0.25, 5, 5,  1, 0, 0,  // 2
		0.25,  1, -0.25, 0, 5, 1, 0, 0,  // 3
		// back
		1, 0, 1, 0, 0, 0, 0, -1,  // 0
		-1, 0, 1, 5, 0, 0, 0, -1,   // 1
		-0.25,  1, 0.25, 5, 5, 0, 0, -1,   // 2
		0.25,  1, 0.25, 0, 5, 0, 0, -1,  // 3
		// left
		-1, 0, 1, 0, 0, -1, 0, 0,  // 0
		-1, 0, -1, 5, 0, -1, 0, 0,   // 1
		-0.25,  1, -0.25, 5, 5,  -1, 0, 0,  // 2
		-0.25,  1, 0.25, 5, 5, -1, 0, 0,  // 3
	};
	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14
	};
	glGenVertexArrays(1, &VAO_tree);
	glGenBuffers(1, &VBO_tree);
	glGenBuffers(1, &EBO_tree);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_tree);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_tree);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_tree);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// define Vector Normal pointer layout 1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawBirch(GLuint shader, double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_birch);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO_tree); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));
	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));
	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildDarkLeaf() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture
	glGenTextures(1, &texture_darkLeaf);
	glBindTexture(GL_TEXTURE_2D, texture_darkLeaf);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("darkLeaf.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0, 0, 0, 1,  // 0
		0.5, -0.5, 0.5, 5, 0,  0, 0, 1,  // 1
		0.5,  0.5, 0.5, 5, 1,  0, 0, 1,  // 2
		-0.5,  0.5, 0.5, 0, 1, 0, 0, 1,  // 3
		// right
		0.5,  0.5,  0.5, 0, 0, 1, 0, 0,  // 4
		0.5,  0.5, -0.5, 5, 0, 1, 0, 0,  // 5
		0.5, -0.5, -0.5, 5, 1, 1, 0, 0,  // 6
		0.5, -0.5,  0.5, 0, 1, 1, 0, 0,  // 7
		// back
		-0.5, -0.5, -0.5, 0, 0, 0, 0, -1, // 8
		0.5,  -0.5, -0.5, 5, 0, 0, 0, -1, // 9
		0.5,   0.5, -0.5, 5, 1, 0, 0, -1, // 10
		-0.5,  0.5, -0.5, 0, 1, 0, 0, -1, // 11
		// left
		-0.5, -0.5, -0.5, 0, 0, -1, 0, 0, // 12
		-0.5, -0.5,  0.5, 5, 0, -1, 0, 0, // 13
		-0.5,  0.5,  0.5, 5, 1, -1, 0, 0, // 14
		-0.5,  0.5, -0.5, 0, 1, -1, 0, 0, // 15
		// upper
		0.5, 0.5,  0.5, 0, 0,  0, 1, 0,  // 16
		-0.5, 0.5,  0.5, 5, 0, 0, 1, 0,  // 17
		-0.5, 0.5, -0.5, 5, 5, 0, 1, 0,  // 18
		0.5, 0.5, -0.5, 0, 5,  0, 1, 0,  // 19
		// bottom
		-0.5, -0.5, -0.5, 0, 0, 0, -1, 0, // 20
		0.5, -0.5, -0.5, 5, 0,  0, -1, 0, // 21
		0.5, -0.5,  0.5, 5, 5,  0, -1, 0, // 22
		-0.5, -0.5,  0.5, 0, 5, 0, -1, 0, // 23
	};
	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};
	glGenVertexArrays(1, &VAO_leaf);
	glGenBuffers(1, &VBO_leaf);
	glGenBuffers(1, &EBO_leaf);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_leaf);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_leaf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_leaf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// define Vector Normal pointer layout 1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawDarkLeaf(GLuint shader, double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_darkLeaf);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO_leaf); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));
	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));
	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildBirchLeaf() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture
	glGenTextures(1, &texture_birchLeaf);
	glBindTexture(GL_TEXTURE_2D, texture_birchLeaf);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("birchLeaf.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0, 0, 0, 1,  // 0
		0.5, -0.5, 0.5, 5, 0,  0, 0, 1,  // 1
		0.5,  0.5, 0.5, 5, 1,  0, 0, 1,  // 2
		-0.5,  0.5, 0.5, 0, 1, 0, 0, 1,  // 3
		// right
		0.5,  0.5,  0.5, 0, 0, 1, 0, 0,  // 4
		0.5,  0.5, -0.5, 5, 0, 1, 0, 0,  // 5
		0.5, -0.5, -0.5, 5, 1, 1, 0, 0,  // 6
		0.5, -0.5,  0.5, 0, 1, 1, 0, 0,  // 7
		// back
		-0.5, -0.5, -0.5, 0, 0, 0, 0, -1, // 8
		0.5,  -0.5, -0.5, 5, 0, 0, 0, -1, // 9
		0.5,   0.5, -0.5, 5, 1, 0, 0, -1, // 10
		-0.5,  0.5, -0.5, 0, 1, 0, 0, -1, // 11
		// left
		-0.5, -0.5, -0.5, 0, 0, -1, 0, 0, // 12
		-0.5, -0.5,  0.5, 5, 0, -1, 0, 0, // 13
		-0.5,  0.5,  0.5, 5, 1, -1, 0, 0, // 14
		-0.5,  0.5, -0.5, 0, 1, -1, 0, 0, // 15
		// upper
		0.5, 0.5,  0.5, 0, 0,   0, 1, 0, // 16
		-0.5, 0.5,  0.5, 5, 0,  0, 1, 0, // 17
		-0.5, 0.5, -0.5, 5, 5,  0, 1, 0, // 18
		0.5, 0.5, -0.5, 0, 5,   0, 1, 0, // 19
		// bottom
		-0.5, -0.5, -0.5, 0, 0, 0, -1, 0, // 20
		0.5, -0.5, -0.5, 5, 0,  0, -1, 0, // 21
		0.5, -0.5,  0.5, 5, 5,  0, -1, 0, // 22
		-0.5, -0.5,  0.5, 0, 5, 0, -1, 0, // 23
	};
	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};
	glGenVertexArrays(1, &VAO_leaf);
	glGenBuffers(1, &VBO_leaf);
	glGenBuffers(1, &EBO_leaf);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_leaf);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_leaf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_leaf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// define Vector Normal pointer layout 1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawBirchLeaf(GLuint shader, double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_birchLeaf);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO_leaf); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));
	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));
	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// Road Things
void Demo::BuildCobble() {
	glGenTextures(1, &texture_cobble);
	glBindTexture(GL_TEXTURE_2D, texture_cobble);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("cobble.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	//// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// upper
		0.5, 0.5,  0.5, 0, 0,  0, 1, 0, // 16
		-0.5, 0.5,  0.5, 1, 0, 0, 1, 0, // 17
		-0.5, 0.5, -0.5, 1, 1, 0, 1, 0, // 18
		0.5, 0.5, -0.5, 0, 1,  0, 1, 0, // 19
	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &VAO_road);
	glGenBuffers(1, &VBO_road);
	glGenBuffers(1, &EBO_road);

	glBindVertexArray(VAO_road);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_road);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_road);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define Vector Normal pointer layout 1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}
void Demo::DrawCobble(GLuint shader, double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_cobble);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO_road); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));
	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));
	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildStone() {
	glGenTextures(1, &texture_stone);
	glBindTexture(GL_TEXTURE_2D, texture_stone);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("stone.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	//// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// upper
		0.5, 0.5,  0.5, 0, 0,  0, 1, 0, // 16
		-0.5, 0.5,  0.5, 1, 0, 0, 1, 0, // 17
		-0.5, 0.5, -0.5, 1, 1, 0, 1, 0, // 18
		0.5, 0.5, -0.5, 0, 1,  0, 1, 0, // 19
	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &VAO_road);
	glGenBuffers(1, &VBO_road);
	glGenBuffers(1, &EBO_road);

	glBindVertexArray(VAO_road);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_road);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_road);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define Vector Normal pointer layout 1
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}
void Demo::DrawStone(GLuint shader, double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	UseShader(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_stone);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glBindVertexArray(VAO_road); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ));
	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));
	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// Camera Things
void Demo::InitCamera()
{
	posCamX = 0.0;
	posCamY = 8.5;
	posCamZ = -70.0;
	viewCamX = 0.0;
	viewCamY = 6.5;
	viewCamZ = 0.0;

	upCamX = 0.0;
	upCamY = 1.0;
	upCamZ = 0.0;
	CAMERA_SPEED = 0.01;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void Demo::MoveCamera(float speed)
{
	float x = (viewCamX - posCamX) / 2;
	float z = (viewCamZ - posCamZ) / 2;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
	pindahX += x * speed;
	pindahZ += z * speed;
}
void Demo::StrafeCamera(float speed)
{
	float x = (viewCamX - posCamX)/2;
	float z = (viewCamZ - posCamZ)/2;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
	pindahX += orthoX * speed;
	pindahZ += orthoZ * speed;
}

// Shadow Things
void Demo::BuildDepthMap() {
	// configure depth map FBO
	// -----------------------
	glGenFramebuffers(1, &depthMapFBO);
	// create depth texture
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, this->SHADOW_WIDTH, this->SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int main(int argc, char** argv) {
	RenderEngine &app = Demo();
	//app.Start("Taman Kincir Angin", 1280, 720, true, false);
	app.Start("Taman Kincir Angin", 1920, 1080, true, true);
}