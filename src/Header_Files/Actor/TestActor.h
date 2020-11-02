#pragma once
#include "Actor.h"
#include "GameTransform.h"
#include "PhysicsBody.h"
#include "Space2D.h"

class TestActor :
	public Actor
{
public:
	void start() {

		body = addBehavior<PhysicsBody>();
		trans = addBehavior<GameTransform>();

		auto pos = s2d::GameUnits::Vec(3, 5);
		auto size = s2d::GameUnits::Vec(4, 4);

		trans->setPos(s2d::GameUnits::Point(pos.x + 0.5f, pos.y + 0.5f));

		//for (int i = 0; i < 7; i++) {
		//	int variance = i % 2 == 0 ? 1 : -1;
		//	auto dimvec = pos + s2d::GameUnits::Vec((0.75f + (float)i / 6) * i, variance * 2 * (float)i) * 60.0f;
		//	s2d::GameUnits::Poly b = s2d::GameUnits::Poly(s2d::GameUnits::Rectangle(s2d::GameUnits::Point(size.x, size.y), s2d::GameUnits::Dimension(dimvec.x, dimvec.y)));
		//	body->addPoly(b, false);
		//	body->setEdgeActive(i, 0, true);
		//	body->setType(CollisionType::Static);
		//}

		s2d::GameUnits::Poly b = s2d::GameUnits::Poly(s2d::GameUnits::Rectangle(s2d::GameUnits::Point(pos.x, pos.y), s2d::GameUnits::Dimension(size.x, size.y)));
		body->addPoly(b, true);
		//body->setEdgeActive(0, 0, true);
		body->setType(CollisionType::Static);

		body->setDensity(1.5f);

		Actor::start();
	}

	void draw(Renderer* renderer) {
		for (auto b : body->getBodies()) {
			auto drawn = ((s2d::PixelUnits::Poly)b).getDrawableSFMLPolygon(5.0, sf::Color(0, 255, 0, 50), sf::Color(255, 0, 0, 255));
			renderer->window->draw(drawn, renderer->states);
		}
		Actor::draw(renderer);
	}

	string getTag() const {
		return "terrain";
	}


	GameTransform* trans;
	PhysicsBody* body;
};

