#pragma once
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <Vector3.h>
#include <MyVector3.h>
#include <InitialMyMatrix3.h>

using namespace std;
using namespace sf;
using namespace gpp;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void draw();
	void unload();
	MyVector3 m_displacement{0,0,-6};
	MyVector3 m_endPoints[8];
	MyVector3 m_points[8];
	GLuint index;
	Clock clock;
	Time elapsed;

	void newPoints();



	// rotation values
	float m_rotationX = 0.0f;
	float m_rotationY = 0.0f;
	float m_rotationZ = 0.0f;

	float m_scale = 1.0f;
};