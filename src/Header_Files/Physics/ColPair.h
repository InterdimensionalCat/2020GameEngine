#pragma once
#include "Space2D.h"
#include <array>
#include "Space2D.h"
#include <memory>

class PhysicsBody;
class RigidBody;
class StaticBody;


//key used to search the map of collisions
struct PairKey {
	PairKey(PhysicsBody* A, const size_t An, PhysicsBody* B, const size_t Bn) {
		if (A < B) {
			bmin = A;
			minnum = An;
			bmax = B;
			maxnum = Bn;
		}
		else {
			bmin = B;
			minnum = Bn;
			bmax = A;
			maxnum = An;
		}
	}

	PhysicsBody* bmin;
	PhysicsBody* bmax;
	size_t minnum;
	size_t maxnum;

	const bool operator==(const PairKey& other) {
		return false;
	}
};

//data structure used for collisiosn
//contains both rigid bodies involved in the collsion
//as well as the MTV angle and magnitude
struct ColPair
{
public:
	//construct a collisionPair with the two potentially
	//colliding bodies
	ColPair(PhysicsBody* A, const size_t& ANum, PhysicsBody* B, const size_t& BNum);

	//the two objects in question
	PhysicsBody* A;
	PhysicsBody* B;

	size_t ABodyNum;
	size_t BBodyNum;

	//test if two colPairs are duplicates;
	bool operator==(const ColPair &other);

	//perform pre-calculations
	void preUpdate(float invDT);

	//resolve collision
	void solveCollision();

	s2d::NormalVec normal = s2d::NormalVec(1,0);
	float seperation;
	std::array<s2d::Point, 2> contactPoints;

	//accumulated impulse and position updates
	float accImp = 0.0f;
	float accPos = 0.0f;
	float accTan = 0.0f;

	//precalculated variables
	float normalMass = 0.0f;
	float tangentMass = 0.0f;
	float bias = 0.0f;
	float friction = 0.0f;

	//true if a collision occured
	bool valid;

	void update(const ColPair& other);
};

bool RigidPairSAT(ColPair &pair);
bool RigidStaticSAT(ColPair &pair);
bool RigidOneWaySAT(ColPair &pair);
bool dummySAT(ColPair &pair);