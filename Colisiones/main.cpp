#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#pragma comment( lib, "glu32.lib" )

// Window settings
const unsigned int screenWidth = 500;
const unsigned int screenHeight = 500;

//Variables
GLfloat cameraZ = 0.0f;
GLfloat rotateY = 0.0f;
GLint colorIndex = 0;

GLfloat colors[3][3] = {
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f }
};

enum Direction {
	NEGATIVE,
	POSITIVE
};

enum Direction rotationDir = POSITIVE;

//Animation variables
double start_time;
double current_time;
double speed = 0.01;

//Cube vertices
GLfloat cube_vertices[8][3] = {
	{ 0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 0 V0
	{ -0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 1 V1
	{ -0.5 ,-0.5, -0.5 },    //Coordenadas Vértice 2 V2
	{ 0.5 ,-0.5, -0.5 },    //Coordenadas Vértice 3 V3
	{ 0.5 ,0.5, 0.5 },    //Coordenadas Vértice 4 V4
	{ 0.5 ,0.5, -0.5 },    //Coordenadas Vértice 5 V5
	{ -0.5 ,0.5, -0.5 },    //Coordenadas Vértice 6 V6
	{ -0.5 ,0.5, 0.5 },    //Coordenadas Vértice 7 V7
};

//Prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void init();
//void processInput(GLFWwindow* window);

void mainLoop(GLFWwindow* window);
void drawCube();

int main() {

	// Initialize and configure GLFW
	if (!glfwInit()) {
		std::cout << "GLFW init failed.\n";
		return -1;
	}
	std::cout << "GLFW init: OK!\n";

	// Create window and context
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Practica 1", NULL, NULL);
	glfwMakeContextCurrent(window);

	// Set callback functions
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	
	// Load OpenGL function pointers (GLEW)
	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW init failed.\n";
		return -2;
	}
	std::cout << "GLEW init: OK!\n";

	// Setup render window
	init();
	
	//Application loop
	mainLoop(window);

	// Clear GLFW resources
	glfwTerminate();
	
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Negro de fondo
	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//void processInput(GLFWwindow* window) {
	
//}

void mainLoop(GLFWwindow* window) {
	start_time = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {

		//Process input, duh
		//processInput(window);

		//Update object values
		if (rotationDir == POSITIVE) {
			rotateY += 0.2f;
			if (rotateY > 360.0f) {
				rotateY = 0.0f;
			}
		}
		else {
			rotateY -= 0.2f;
			if (rotateY < 0.0f) {
				rotateY = 360.0f;
			}
		}

		//Render
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		
		//glOrtho(-2.0, 2.0, -2.0, 2.0, -100.0, 100.0);
		//glFrustum(-0.01f, 0.01f, -0.01f, 0.01f, 0.001f, 100.0f);
		gluPerspective(45.0f, (float)screenWidth / (float)screenWidth, 0.01, 1000.0);
		gluLookAt(0.0f, 1.0f, 5.0f + cameraZ, 0.0f, 0.0f, cameraZ, 0.0f, 1.0f, 0.0f);

		glRotatef(rotateY, 0, 1.0, 0);
		glColor3fv(colors[colorIndex]);
		drawCube();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void drawCube() {
	glBegin(GL_POLYGON);	//Front	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3fv(cube_vertices[0]);
	glVertex3fv(cube_vertices[4]);
	glVertex3fv(cube_vertices[7]);
	glVertex3fv(cube_vertices[1]);
	glEnd();

	glBegin(GL_POLYGON);	//Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3fv(cube_vertices[0]);
	glVertex3fv(cube_vertices[3]);
	glVertex3fv(cube_vertices[5]);
	glVertex3fv(cube_vertices[4]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3fv(cube_vertices[6]);
	glVertex3fv(cube_vertices[5]);
	glVertex3fv(cube_vertices[3]);
	glVertex3fv(cube_vertices[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3fv(cube_vertices[1]);
	glVertex3fv(cube_vertices[7]);
	glVertex3fv(cube_vertices[6]);
	glVertex3fv(cube_vertices[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3fv(cube_vertices[0]);
	glVertex3fv(cube_vertices[1]);
	glVertex3fv(cube_vertices[2]);
	glVertex3fv(cube_vertices[3]);
	glEnd();

	glBegin(GL_POLYGON);  //Top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3fv(cube_vertices[4]);
	glVertex3fv(cube_vertices[5]);
	glVertex3fv(cube_vertices[6]);
	glVertex3fv(cube_vertices[7]);
	glEnd();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		cameraZ += 1.0f;
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		cameraZ -= 1.0f;
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		rotationDir = POSITIVE;
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		rotationDir = NEGATIVE;
	if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
		if (mods == GLFW_MOD_CONTROL) {
			colorIndex--;
		}
		else {
			colorIndex++;
		}
		if (colorIndex > 2) {
			colorIndex = 0;
		}
		else if (colorIndex < 0) {
			colorIndex = 2;
		}
	}
}