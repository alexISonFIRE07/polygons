/** -----------------------------------------
* @file    spaceObject.cpp
* @author  Alex Jarmer
* @version 1.1
*
* polygon projects class implentations 
*
* --------------------------------------- */

#include "spaceObject.h"
#include "constants.h"
#include <SFML/Graphics.hpp>
#include <iostream>


SpaceObject::SpaceObject()
{
	type = SpaceObjType::ASTEROID;
	location = getRandomLocation();
	velocity = getRandomVelocity();
	angleDeg = 0;
	radius = 20;
	timesDrawn = 0;

}

SpaceObject::SpaceObject(SpaceObjType type, double radius, Point location, Point velocity, double angle)
{
	setType(type);
	setRadius(radius);
	setLocation(location.x, location.y);
	setVelocity(velocity.x, velocity.y);
	setAngle(angle);
	timesDrawn = 0;
}

bool SpaceObject::setType(SpaceObjType type) {
	if (type == SpaceObjType::SHIP || type == SpaceObjType::ASTEROID
		|| type == SpaceObjType::PHOTON_TORPEDO)
		this->type = type;
	else this->type = SpaceObjType::ASTEROID;
	return true;
}

bool SpaceObject::setRadius(int radius)
{
	if (radius > 0 && radius < SCREEN_HEIGHT / 2) {
		this->radius = radius;
		return true;
	}
	else this->radius = 20;
}

bool SpaceObject::setLocation(double x, double y)
{
	while (x < 0)
		x += SCREEN_WIDTH;
	while (x > SCREEN_WIDTH)
		x -= SCREEN_WIDTH;
	location.x = x;

	while (y < 0)
		y += SCREEN_HEIGHT;
	while (y > SCREEN_HEIGHT)
		y -= SCREEN_HEIGHT;
	location.y = y;
	
	return true;
}

bool SpaceObject::setVelocity(double velocityX, double velocityY)
{
	if (velocityX <= 5 && velocityX >= -5) {
		velocity.x = velocityX;
	}
	if (velocityY <= 5 && velocityY >= -5) {
		velocity.y = velocityY;
	}
	else {
		velocity.x = getRandomVelocity().x;
		velocity.y = getRandomVelocity().y;
	};
	return true;
}

bool SpaceObject::setAngle(double angDeg)
{
		angleDeg = angDeg;
		return true;
}

void SpaceObject::changeAngle(double deltaDeg)
{
	if (type != SpaceObjType::SHIP)
		return;
	if (deltaDeg >= -5 && deltaDeg <= 5) {
		angleDeg += deltaDeg;
	}

}

void SpaceObject::draw(sf::RenderWindow& win) {
	if (type == SpaceObjType::SHIP)
		drawShip(win);
	if (type == SpaceObjType::ASTEROID)
		drawAsteroid(win);
	if (type == SpaceObjType::SHIP_EXPLODING)
		drawExplodingShip(win);
	if (type == SpaceObjType::SHIP_GONE) {
			type = SpaceObjType::SHIP;
			radius = 20;
			location = { SCREEN_HEIGHT / 2,SCREEN_WIDTH / 2 };
	}
	if (type == SpaceObjType::PHOTON_TORPEDO) {
		drawTorpedo(win);
		this->timesDrawn++;
	}
}

void SpaceObject::drawAsteroid(sf::RenderWindow& win) {
	//Configure a graphics object to be used for drawing our object
	//this code draws a simple pentagon.Feel free to modify it if you want.
	int points = 5;
	sf::CircleShape shape(radius, points); //radius from our SpaceObject

	sf::Vector2f midpoint(radius, radius);
	shape.setOrigin(midpoint);

	shape.setFillColor(sf::Color(0, 0, 0));
	shape.setOutlineThickness(1);
	shape.setOutlineColor(sf::Color(255, 255, 255));

	//apply our object position to the graphics object and draw it
	shape.setPosition(location.x, location.y);
	shape.setRotation(angleDeg);

	win.draw(shape);
	//Note: if asteroid is near the edge (within a radius) then we should 
	//draw it again on the other side of the screen so the part off the edge 
	//shows up immediately on the other edge. Code to do that should be added
	//here.
}

void SpaceObject::drawTorpedo(sf::RenderWindow& win) {
	//Configure a graphics object to be used for drawing our object
	//this code draws a simple pentagon.Feel free to modify it if you want.
	int points = 50;
	sf::CircleShape shape(radius, points); //radius from our SpaceObject

	sf::Vector2f midpoint(radius, radius);
	shape.setOrigin(midpoint);

	shape.setFillColor(sf::Color(0, 0, 0));
	shape.setOutlineThickness(1);
	shape.setOutlineColor(sf::Color(255, 255, 255));

	//apply our object position to the graphics object and draw it
	shape.setPosition(location.x, location.y);
	shape.setRotation(angleDeg);

	win.draw(shape);
	//Note: if asteroid is near the edge (within a radius) then we should 
	//draw it again on the other side of the screen so the part off the edge 
	//shows up immediately on the other edge. Code to do that should be added
	//here.
}

void SpaceObject::drawShip(sf::RenderWindow& win) {
	// draw ship
	sf::ConvexShape shipShape;
	shipShape.setPointCount(3);
	shipShape.setPoint(0, sf::Vector2f(10, 0));
	shipShape.setPoint(1, sf::Vector2f(0, 25));
	shipShape.setPoint(2, sf::Vector2f(20, 25));

	sf::Vector2f midpoint(10, 15);
	shipShape.setOrigin(midpoint);

	shipShape.setFillColor(sf::Color(0, 0, 0));
	shipShape.setOutlineThickness(1);
	shipShape.setOutlineColor(sf::Color(255, 255, 255));

	shipShape.setPosition(location.x, location.y);
	shipShape.setRotation(angleDeg);
	win.draw(shipShape);
}

SpaceObjType SpaceObject::getType() {
	return type;
}

double SpaceObject::getRadius() const
{
	return radius;
}

Point SpaceObject::getLocation() const
{
	return location;
}

Point SpaceObject::getVelocity() const
{
	return velocity;
}

double SpaceObject::getAngle() const
{
	return angleDeg;
}

double SpaceObject::getTimesDrawn() const {
	return timesDrawn;
}

void SpaceObject::updatePosition()
{
	double xLoc = getLocation().x;
	double yLoc = getLocation().y;
	double xVel = getVelocity().x;
	double yVel = getVelocity().y;

	xLoc += xVel;
	yLoc += yVel;

	setLocation(xLoc, yLoc);
}


void SpaceObject::applyThrust(double thrustAmount) {
	double engineThrust = thrustAmount;
	double forcex = cos((angleDeg - 90) * PI / 180) * engineThrust;
	double forcey = sin((angleDeg - 90) * PI / 180) * engineThrust;
	velocity.x = velocity.x + forcex;
	velocity.y = velocity.y + forcey;
}

Point SpaceObject::getRandomLocation() {
	double x = rand() % SCREEN_WIDTH;
	double y = rand() % SCREEN_HEIGHT;

	return { x,y };
}

Point SpaceObject::getRandomVelocity() {
	double x = ((double)rand() / (RAND_MAX));
	double y = ((double)rand() / (RAND_MAX));

	x -= ((double)rand() / (RAND_MAX));
	y -= ((double)rand() / (RAND_MAX));

	return { x,y };
}

void SpaceObject::explode() {
	type = SpaceObjType::SHIP_EXPLODING;
	velocity = { 0,0 };
}

void SpaceObject::drawExplodingShip(sf::RenderWindow& win) {
	int points = 100;
	sf::CircleShape shape(radius, points); //radius from our SpaceObject

	sf::Vector2f midpoint(radius, radius);
	shape.setOrigin(midpoint);

	shape.setFillColor(sf::Color(255, 255, 255));
	shape.setOutlineThickness(1);
	shape.setOutlineColor(sf::Color(255, 255, 255));

	//apply our object position to the graphics object and draw it
	shape.setPosition(location.x, location.y);
	shape.setRotation(angleDeg);
	radius += .3;
	win.draw(shape);
	if (radius >= SCREEN_HEIGHT / 10) {
		type = SpaceObjType::SHIP_GONE;
	}
}

void SpaceObject::splitAsteroid() {
	if (this->getRadius() > 5) {
		this->setRadius(this->getRadius() / 2);
		this->setLocation(this->getLocation().x + 10, this->getLocation().y + 10);
	}
	else { 
		delete [] this; 
	}
}
	
	//TODO make splitAsteroid function make two smaller asteroids rather than one.
	//code below are "notes"...

		/*for (int z = 0; z < MAX_ASTEROIDS; z++) {
		* int firstNullAsteroid = 0;
			if (this[z] == NULL) {
				firstNullAsteroid = z;
				this[firstNullAsteroid] = new SpaceObject(SpaceObjType::ASTEROID, this->getRadius() / 2,
					{ this->getLocation().x - 10, this->getLocation().y - 10 }, this->getRandomVelocity(), 45);
			}
		}


		this[firstNullAsteroid] = new SpaceObject(SpaceObjType::ASTEROID, FIRST_SPLIT_ASTEROID,
			{ asteroid[x]->getLocation().x - 10, asteroid[x]->getLocation().y - 10 }, asteroid[x]->getRandomVelocity(), 45);
	}
}*/

