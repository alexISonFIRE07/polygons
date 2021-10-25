#pragma once

/** -----------------------------------------
* @file    spaceObject.H
* @author  Alex Jarmer
* @version 1.1
*
* polygon projects header file
*
* --------------------------------------- */

#include "constants.h"
#include <SFML/Graphics.hpp>



struct Point {
	double x;
	double y;
};

enum class SpaceObjType 
{ SHIP, ASTEROID, PHOTON_TORPEDO, SHIP_EXPLODING,SHIP_GONE};

class SpaceObject {

public:
/**--------------------------------------------------------------------
* SpaceObject() [constructor default]:
*	Initializes object to:	
*	type:		ASTROID
*	location.x: 200
* 	location.y: 200
*	velocity.x:	5
*	velocity.y:	5
*	angleDeg:	45;
*	radius:		20;
*/
	SpaceObject();

/**--------------------------------------------------------------------
* SpaceObject(with params) [constructor]: 
*	Initializes object to given values
*	@param type
*	@param radius
*	@param location 
*	@param velocity
*	@param angle
*/
	SpaceObject(SpaceObjType type, double radius,
		Point location, Point velocity, double angle);


//=============================================
//mutators
/**--------------------------------------------------------------------
* setType [mutator]:
*	sets type to given value
*	@param type - the new type to be set
*
*	@return true if type set
*/

	bool setType(SpaceObjType type);

/**--------------------------------------------------------------------
* setRadius [mutator]:
*	sets radius to given value
*	@param radius - the new radius to be set
*	
*	@return true if radius set
*/
	bool setRadius(int radius);

/**--------------------------------------------------------------------
* setLocation [mutator]:
*	sets location to given value. determines if location is off screen
*	if so, it sets the value to value minues screen size (height or width)
*	@param x - the new x coodinate to be set
*	@param y - the new y coodinate to be set
* 
*	@return true if location set
*/
	bool setLocation(double x, double y);

/**--------------------------------------------------------------------
* setVelocity [mutator]:
*	sets velocity to given value. 
*	@param velocityX - the new x velocity (pixel per frame) to be set
*	@param velocityY - the new y velocity (pixel per frame) to be set
* 
*	@return true if velocity set
*/
	bool setVelocity(double velocityX, double velocityY);

/**--------------------------------------------------------------------
* setAngle [mutator]:
*	sets angle to given value.
*	@param angDeg - the new angle (in degrees) to be set
* 
*	@return true if angle set;
*/
	bool setAngle(double angDeg);

/**--------------------------------------------------------------------
* changeAngle [mutator]:
*	change angle by given amount.
*	@param deltaDeg - amount of change to angle (in degrees)
*/
	void changeAngle(double deltaDeg);

/** ---------------------------------------------------------------
*   Draws the spaceobject on the given window
*
* 	@param win - the window on which we�ll draw the ship
------------------------------------------------------------------
*/
	void draw(sf::RenderWindow& win);

/** -----------------------------------------------------------
*   Draws the spaceobject on the given window as an asteroid
*
* 	@param win - the window on which we�ll draw the ship
--------------------------------------------------------------- 
*/
	void drawAsteroid(sf::RenderWindow& win);

/** -----------------------------------------------------------
*   Draws the spaceobject on the given window as an torpedo
*
* 	@param win - the window on which we�ll draw the ship
---------------------------------------------------------------
*/
	void drawTorpedo(sf::RenderWindow& win);

/** ------------------------------------------------------------
*   Draws the spaceobject on the given window as a ship
*
* 	@param win - the window on which we�ll draw the ship
--------------------------------------------------------------- 
*/
	void drawShip(sf::RenderWindow& win);

//============================================
//accessors

/**--------------------------------------------------------------------
* getType [accessor]:
*	gets the current value of type
*	@return the type
*/
	SpaceObjType getType();

/**--------------------------------------------------------------------
* getRadius [accessor]:
*	gets the current value of radius
*	@return the radius
*/
	double getRadius() const;

/**--------------------------------------------------------------------
* getLocation [accessor]:
*	gets the current value of location
*	@return the location
*/
	Point getLocation() const;

/**--------------------------------------------------------------------
* getVelocity [accessor]:
*	gets the current value of velocity
*	@return the velocity
*/
	Point getVelocity() const;

/**--------------------------------------------------------------------
* getAngle [accessor]:
*	gets the current value of angle
*	@return the angle
*/
	double getAngle() const;

/**--------------------------------------------------------------------
* getTimesDrawn [accessor]:
*	gets the current value of timesDrawn
*	@return the number of times the instance was drawn
*/
double getTimesDrawn() const;


//============================================
//others

/**--------------------------------------------------------------------
* updatePosition [other]:
*	Updates the location based on the current velocity
*/
	void updatePosition();

/*================================================
* applyThrust
* simulates firing the engine.
* @param thrustAmount amount of thrust
* 
*/
	void applyThrust(double thrustAmount);

/*================================================
* getRandomLocation
* returns a Point structure that contains x (0-width) 
* and y (0-height).
* 
* @return	random location
*/
	Point getRandomLocation();

/*================================================
* getRandomVelocity
* returns a Point structure that contains x (-1,1)
* and y (-1,1).
*
* @return	random velocity
*/
	Point getRandomVelocity();

	/*================================================
* explode
* Updates some values to put ship in exploding state.
*/
	void explode();

/*================================================
* drawExplodingShip
* to make the ship visually explode when it hits an asteroid
* @param win - the window on which we�ll draw the ship
*/
	void drawExplodingShip(sf::RenderWindow& win);


/*================================================
* splitAsteroid
* Takes and asteroid and splits it in half
* @param index   index of asteroid to be split
*/

	void splitAsteroid();

private:
	SpaceObjType type;	  //type of object
	Point location;	  //current location (x,y)
	Point velocity;	  //current velocity (in pixels/frame)
	double angleDeg;	  //angle object is facing (in degrees)
	double radius;        //gross radius of object (for collision detection)
	int timesDrawn;		//times that the instance has been drawn
};
