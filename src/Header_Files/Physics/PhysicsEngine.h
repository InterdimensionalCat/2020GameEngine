//PhysicsEngine.h
/*
  The physics engine.
  Its really complicated and I am not going to be able to simplify it anytime soon
  so for the moment this is a solo effort, feel free to ignore everything outside the ABI
*/
#pragma once
#include <map>
#include "ColPair.h"
#include "SweepAndPrune.h"
#include "collisionEvent.h"

class PhysicsBody;

//physics units: pixels, physics grid:
//        y-
//    x-      x+
//        y+
class PhysicsEngine
{
public:


	PhysicsEngine();

	void updatePhysics(const float deltaTime);

	void addBody(std::shared_ptr<PhysicsBody> b);

	//sweep and prune container
	SweepAndPrune sweeper;

private:

	friend class CollisionEvent;
	friend class Level;

	void sweepAndPrune();

	//Move all objects according to the forces they have
	void moveBodies(const float dt);

	//integretes forces in each body
	void integrateForce(const float dt);


	std::vector<std::shared_ptr<PhysicsBody>> bodies;

	//container storing all generated possible collisions on a particular
	//physics update
	std::map<PairKey, ColPair> collisions;

	//gravity vector
	//gravity is typically 10 meters per second squared
	s2d::Vec gravity;

	//number of times the engine resolves collisions in a frame
	int iterations;

};

//necessasary for the map to function
inline bool operator<(const PairKey &lhs, const PairKey &rhs) {
	if (lhs.bmin.get() < rhs.bmin.get()) {
		return true;
	}

	if (lhs.bmin.get() == rhs.bmin.get() && lhs.bmax.get() < rhs.bmax.get()) {
		return true;
	}

	return false;
}