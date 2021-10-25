/** -----------------------------------------
* @file    game.cpp
* @author  Alex Jarmer
* @version 1.1
*
* polygon projects file that contains the 
* main function and the actual game
*
* --------------------------------------- */

#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "spaceObject.h"
#include <ctime>


/**--------------------------------------------------------------------
* printValues [other]:
*	Prints the values of an object for testing
* @param	object
* @return	void
*/
void printValues(SpaceObject obj);

/**--------------------------------------------------------------------
* objectsIntersect [other]:
*	takes two SpaceObject pointers, 
*	and returns true if the objects overlap on the screen 
* @param	object
* @return	bool
*/
bool objectsIntersect(SpaceObject* obj1, SpaceObject* obj2);

/*================================================
* findFirstNull
* finds the first instance of NULL in a pointer array
* @param array of type SpaceObject
* @param max - max number of array
*
* @return array int value that has the first instance of NULL
*/
int findFirstNull(SpaceObject* array[], int max);


//============================================================================
int main()
{
	//create graphics window
	sf::RenderWindow window(
		sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		"Polygons!",
		sf::Style::Titlebar | sf::Style::Close
	);
	window.setFramerateLimit(60);

	//create SpaceObjects
		//Creates asteroids;
		SpaceObject* asteroid[MAX_ASTEROIDS] = {NULL};
		for (int x = 0; x < 5; x++) {
			asteroid[x] = new SpaceObject();
		}

		//Creates ship
		SpaceObject* ship = NULL;
		ship = new SpaceObject(SpaceObjType::SHIP, 15, { SCREEN_HEIGHT / 2,SCREEN_WIDTH / 2 }, { 0,0 },90);
		
		//Creates torpedos
		SpaceObject* torpedo[MAX_PHOTONS] = { NULL };

		//random number generator seed
		srand(42);
		
		//game loop
	while (window.isOpen())
	{
		//handle user input (events and keyboard keys being pressed) ----
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
				//TODO Replace this code with findFirstNull Function
				int firstNullTorpedo = 0;
				for (int x = 0; x < MAX_PHOTONS; x++)
					if (torpedo[x] == NULL)
						firstNullTorpedo = x;
				torpedo[firstNullTorpedo] = new SpaceObject(SpaceObjType::PHOTON_TORPEDO, 2, ship->getLocation(), ship->getVelocity(), ship->getAngle());
				torpedo[firstNullTorpedo]->applyThrust(5);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			ship->changeAngle(-2);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			ship->changeAngle(2);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			ship->applyThrust(0.05);




		// update game objects ------------------------------------------
		for (int x = 0; x < MAX_ASTEROIDS; x++) {
			if (asteroid[x]) {
				asteroid[x]->updatePosition();
			}
		}

		for (int x = 0; x < MAX_PHOTONS; x++) {
			if (torpedo[x]) {
				torpedo[x]->updatePosition();
				if (torpedo[x]->getTimesDrawn() >= PHOTO_LIFESPAN)
					//TODO find out why delete is not allowing torpedo to render
					//delete torpedo[x];
					torpedo[x] = NULL;
			}
			
		}

		ship->updatePosition();

		//checks for object collision

		//Torpedo vs Asteroid 
		for (int x = 0; x < MAX_ASTEROIDS; x++) {
			for (int y = 0; y < MAX_PHOTONS; y++) {
				if (asteroid[x] && torpedo[y]) {
					if (objectsIntersect(asteroid[x], torpedo[y])) {
						delete torpedo[y];
						torpedo[y] = NULL;
						//makes astroid smaller
						asteroid[x]->splitAsteroid();
						//changes asteroid array element to NULL
						//TODO: find out why delete is throwing an execption 
						if (asteroid[x]->getRadius() < 5) {
							//delete asteroid[x];
							asteroid[x] = NULL;
						}
						//TODO: Don't just have asteroid get small, but create two smaller asteroids
						
						/*int fistNull= findFirstNull(asteroid, MAX_ASTEROIDS);
 						asteroid[fistNull] = new SpaceObject(SpaceObjType::ASTEROID, FIRST_SPLIT_ASTEROID,
							{ asteroid[x]->getLocation().x - 10, asteroid[x]->getLocation().y - 10 }, asteroid[x]->getRandomVelocity(), 45);
						asteroid[fistNull]->splitAsteroid();*/
					}
				}
			}
		}
		
		//Ship vs Asteroid Collision detection
		for (int x = 0; x < 5; x++) {
			if(ship->getType() == SpaceObjType::SHIP && asteroid[x] != NULL)
			if (objectsIntersect(asteroid[x], ship)) {
				ship->explode();
			}
		}

		// draw new frame ------------------------------------------------
		window.clear();
		for (int x = 0; x < MAX_ASTEROIDS; x++) {
			if (asteroid[x])
			asteroid[x]->draw(window);
		}
		for (int x = 0; x < MAX_PHOTONS; x++) {
			if (torpedo[x])
				torpedo[x]->draw(window);
		}
		//asteroid[0]->draw(window); 
		ship->draw(window);  
		window.display();
	}

	return 0;
}


void printValues(SpaceObject obj) {
	//std::cout << "TYPE: " << obj.type;
	std::cout << "Radius: " << obj.getRadius() << '\n';
	std::cout << "X Location: " << obj.getLocation().x << '\n';
	std::cout << "Y Location: " << obj.getLocation().y << '\n';
	std::cout << "X Velocity: " << obj.getVelocity().x << '\n';
	std::cout << "Y Velocity: " << obj.getVelocity().y << '\n';
	std::cout << "Angle: " << obj.getAngle() << '\n';
}

bool objectsIntersect(SpaceObject* obj1, SpaceObject* obj2) {
	int radiusSum = obj1->getRadius() + obj2->getRadius();
	int xDistApart = obj1->getLocation().x - obj2->getLocation().x;
	int yDistApart = obj1->getLocation().y - obj2->getLocation().y;


	if(xDistApart <= radiusSum && xDistApart >= -radiusSum)
		if (yDistApart <= radiusSum/2 && yDistApart >= -radiusSum/2)
			return true;
	return false;
}

int findFirstNull(SpaceObject* array[], int max) {
	for (int x = 0; x < max; x++) {
		if (array[x] == NULL) {
			return x;
		}
	}
}