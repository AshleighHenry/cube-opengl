#include <Game.h>

bool updatable = false;

gpp::Vector3 v3;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube"),
m_points{ {-1,1,1}, {-1,-1,1},{1,-1,1},{1,1,1},{ -1,1,-1 },{ -1,-1,-1 },{ 1,-1,-1 },{ 1,1,-1 } }
{
	for (int i = 0; i <8; i++)
	{
		m_endPoints[i] = m_points[i];
	}
	
	index = glGenLists(1);
}

Game::~Game(){}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning){

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Right)
				{
					m_displacement.x += 1;
				}
				if (event.key.code == Keyboard::Left)
				{
					m_displacement.x -= 1;
				}
				if (event.key.code == Keyboard::Up)
				{
					m_displacement.y += 1;
				}
				if (event.key.code == Keyboard::Down)
				{
					m_displacement.y -= 1;
				}
				if (event.key.code == Keyboard::Q)
				{
					m_displacement.z -= 1;
				}
				if (event.key.code == Keyboard::E)
				{
					m_displacement.z += 1;
				}
				if (event.key.code == Keyboard::Z)
				{
					if (m_rotationZ <= 359)
					{
						m_rotationZ += 1;
					}					
				}
				if (event.key.code == Keyboard::X)
				{
					if (m_rotationX <= 359)
					{
						m_rotationX += 1;
					}
				}
				if (event.key.code == Keyboard::Y)
				{
					if (m_rotationY <= 359)
					{
						m_rotationY += 1;
					}
				}
			}
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	glDeleteLists(1, 1); // delete the list si we can assign the end points
	// glNewList(index, GL_COMPILE);
	// Creates a new Display List
	// Initalizes and Compiled to GPU
	// https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml
	glNewList(index, GL_COMPILE);
	glBegin(GL_QUADS);
	{
		//Front Face
		glColor3f(0.0f, 0.0f, 1.0f); // blue
		glVertex3f(m_endPoints[0].x, m_endPoints[0].y, m_endPoints[0].z);
		glVertex3f(m_endPoints[1].x, m_endPoints[1].y, m_endPoints[1].z);
		glVertex3f(m_endPoints[2].x, m_endPoints[2].y, m_endPoints[2].z);
		glVertex3f(m_endPoints[3].x, m_endPoints[3].y, m_endPoints[3].z);

		//Back Face
		glColor3f(1.0f, 1.0f, 1.0f); // white
		glVertex3f(m_endPoints[4].x, m_endPoints[4].y, m_endPoints[4].z);
		glVertex3f(m_endPoints[5].x, m_endPoints[5].y, m_endPoints[5].z);
		glVertex3f(m_endPoints[6].x, m_endPoints[6].y, m_endPoints[6].z);
		glVertex3f(m_endPoints[7].x, m_endPoints[7].y, m_endPoints[7].z);

		//Complete the faces of the Cube
		// bottom face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(m_endPoints[1].x, m_endPoints[1].y, m_endPoints[1].z);
		glVertex3f(m_endPoints[2].x, m_endPoints[2].y, m_endPoints[2].z);
		glVertex3f(m_endPoints[6].x, m_endPoints[6].y, m_endPoints[6].z);
		glVertex3f(m_endPoints[5].x, m_endPoints[5].y, m_endPoints[5].z);
		// left face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(m_endPoints[0].x, m_endPoints[0].y, m_endPoints[0].z);
		glVertex3f(m_endPoints[1].x, m_endPoints[1].y, m_endPoints[1].z);
		glVertex3f(m_endPoints[5].x, m_endPoints[5].y, m_endPoints[5].z);
		glVertex3f(m_endPoints[4].x, m_endPoints[4].y, m_endPoints[4].z);
		
		// top face
		//
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(m_endPoints[0].x, m_endPoints[0].y, m_endPoints[0].z);
		glVertex3f(m_endPoints[4].x, m_endPoints[4].y, m_endPoints[4].z);
		glVertex3f(m_endPoints[7].x, m_endPoints[7].y, m_endPoints[7].z);
		glVertex3f(m_endPoints[3].x, m_endPoints[3].y, m_endPoints[3].z);
		
		//
		//// right face
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(m_endPoints[3].x, m_endPoints[3].y, m_endPoints[3].z);
		glVertex3f(m_endPoints[2].x, m_endPoints[2].y, m_endPoints[2].z);
		glVertex3f(m_endPoints[6].x, m_endPoints[6].y, m_endPoints[6].z);
		glVertex3f(m_endPoints[7].x, m_endPoints[7].y, m_endPoints[7].z);
	}
	glEnd();
	glEndList();
}

void Game::update()
{

	for (int i = 0; i <8; i++)
	{
		m_endPoints[i] = m_points[i];
		m_endPoints[i] = MyMatrix3::rotationX(m_rotationX) * m_endPoints[i];
		m_endPoints[i] = MyMatrix3::rotationZ(m_rotationZ) * m_endPoints[i];
		m_endPoints[i] = MyMatrix3::rotationZ(m_rotationY) * m_endPoints[i];
		m_endPoints[i] += m_displacement;
	}

	newPoints();
	cout << "Update up" << endl;
}

void Game::draw()
{
	//cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//cout << "Drawing Cube " << endl;
	glLoadIdentity();
	//glRotatef(rotationAngle, 0, 0, 1); // Rotates the camera on Y Axis

	glCallList(1);

	window.display();
	
}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

void Game::newPoints()
{


	glDeleteLists(1, 1); // delete the list si we can assign the end points
						 
	glNewList(index, GL_COMPILE);
	glBegin(GL_QUADS);
	{
		//Front Face
		glColor3f(0.0f, 0.0f, 1.0f); // blue
		glVertex3f(m_endPoints[0].x, m_endPoints[0].y, m_endPoints[0].z);
		glVertex3f(m_endPoints[1].x, m_endPoints[1].y, m_endPoints[1].z);
		glVertex3f(m_endPoints[2].x, m_endPoints[2].y, m_endPoints[2].z);
		glVertex3f(m_endPoints[3].x, m_endPoints[3].y, m_endPoints[3].z);

		//Back Face
		glColor3f(1.0f, 1.0f, 1.0f); // white
		glVertex3f(m_endPoints[4].x, m_endPoints[4].y, m_endPoints[4].z);
		glVertex3f(m_endPoints[5].x, m_endPoints[5].y, m_endPoints[5].z);
		glVertex3f(m_endPoints[6].x, m_endPoints[6].y, m_endPoints[6].z);
		glVertex3f(m_endPoints[7].x, m_endPoints[7].y, m_endPoints[7].z);

		//Complete the faces of the Cube
		// bottom face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(m_endPoints[1].x, m_endPoints[1].y, m_endPoints[1].z);
		glVertex3f(m_endPoints[2].x, m_endPoints[2].y, m_endPoints[2].z);
		glVertex3f(m_endPoints[6].x, m_endPoints[6].y, m_endPoints[6].z);
		glVertex3f(m_endPoints[5].x, m_endPoints[5].y, m_endPoints[5].z);
		// left face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(m_endPoints[0].x, m_endPoints[0].y, m_endPoints[0].z);
		glVertex3f(m_endPoints[1].x, m_endPoints[1].y, m_endPoints[1].z);
		glVertex3f(m_endPoints[5].x, m_endPoints[5].y, m_endPoints[5].z);
		glVertex3f(m_endPoints[4].x, m_endPoints[4].y, m_endPoints[4].z);

		// top face
		//
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(m_endPoints[0].x, m_endPoints[0].y, m_endPoints[0].z);
		glVertex3f(m_endPoints[4].x, m_endPoints[4].y, m_endPoints[4].z);
		glVertex3f(m_endPoints[7].x, m_endPoints[7].y, m_endPoints[7].z);
		glVertex3f(m_endPoints[3].x, m_endPoints[3].y, m_endPoints[3].z);

		//
		//// right face
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(m_endPoints[3].x, m_endPoints[3].y, m_endPoints[3].z);
		glVertex3f(m_endPoints[2].x, m_endPoints[2].y, m_endPoints[2].z);
		glVertex3f(m_endPoints[6].x, m_endPoints[6].y, m_endPoints[6].z);
		glVertex3f(m_endPoints[7].x, m_endPoints[7].y, m_endPoints[7].z);
	}
	glEnd();
	glEndList();
}

