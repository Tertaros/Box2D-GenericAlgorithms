#pragma once
#ifndef PERSONALTESTFIXTURES_H
#define PERSONALTESTFIXTURES_H
#include "Testbed/Framework/Test.h"

#define PI 3.14159265359f
class PersonalTestFixtures: public Test
{
public:
	PersonalTestFixtures()
	{
#pragma region Fixtures
		//b2BodyDef myBodyDef;
		//myBodyDef.type = b2_dynamicBody;
		//myBodyDef.position.Set(-10, 20);

		//b2Body* dynamicBody1 = m_world->CreateBody(&myBodyDef);

		//b2CircleShape circleShape;
		//circleShape.m_p.Set(0, 0);
		//circleShape.m_radius = 1; 

		//b2FixtureDef myFixtureDef;
		//myFixtureDef.density = 1; //Density/Mass
		//myFixtureDef.shape = &circleShape;
		//dynamicBody1->CreateFixture(&myFixtureDef);

		////Polygon
		////Set each vertex of Polygon in an array
		//b2Vec2 vertices[5];
		//vertices[0].Set(-1, 2);
		//vertices[1].Set(-1, 0);
		//vertices[2].Set(0, -3);
		//vertices[3].Set(1, 0);
		//vertices[4].Set(1, 1);

		//b2PolygonShape polygonShape;
		//polygonShape.Set(vertices, 5);

		//myFixtureDef.shape = &polygonShape;
		//myBodyDef.position.Set(0, 20);// in the middle
		//b2Body* dynamicBody2 = m_world->CreateBody(&myBodyDef);
		//dynamicBody2->CreateFixture(&myFixtureDef);

		////Rectangle
		//polygonShape.SetAsBox(2, 1);
		//myBodyDef.position.Set(10, 20);

		//b2Body*dynamicBody3 = m_world->CreateBody(&myBodyDef);
		//dynamicBody3->CreateFixture(&myFixtureDef);

		//Multiple Fixtures in one

		//b2BodyDef myBodyDef;
		//myBodyDef.type = b2_dynamicBody;
		//myBodyDef.position.Set(-10, 20);

		//b2Body* dynamicBody1 = m_world->CreateBody(&myBodyDef);

		//b2CircleShape circleShape;
		//circleShape.m_p.Set(0, 0);
		//circleShape.m_radius = 1;

		//b2FixtureDef myFixtureDef;
		//myFixtureDef.density = 1; //Density/Mass
		//myFixtureDef.shape = &circleShape;
		//dynamicBody1->CreateFixture(&myFixtureDef);

		////Polygon
		////Set each vertex of Polygon in an array
		//b2Vec2 vertices[5];
		//vertices[0].Set(-1, 2);
		//vertices[1].Set(-1, 0);
		//vertices[2].Set(0, -3);
		//vertices[3].Set(1, 0);
		//vertices[4].Set(1, 1);

		//b2PolygonShape polygonShape;
		//polygonShape.Set(vertices, 5);

		//myFixtureDef.shape = &polygonShape;
		//myBodyDef.position.Set(0, 20);// in the middle
		////b2Body* dynamicBody2 = m_world->CreateBody(&myBodyDef);
		//dynamicBody1->CreateFixture(&myFixtureDef);

		////Rectangle
		//polygonShape.SetAsBox(2, 1);
		//myBodyDef.position.Set(10, 20);

		////b2Body*dynamicBody3 = m_world->CreateBody(&myBodyDef);
		//dynamicBody1->CreateFixture(&myFixtureDef);

		////Edge
		//myBodyDef.type = b2_staticBody; // change body type
		//myBodyDef.position.Set(0, 0);//middle, bottom

		//b2EdgeShape edgeShape;
		//edgeShape.Set(b2Vec2(-15, 0), b2Vec2(15, 0));
		//b2Body* staticBody = m_world->CreateBody(&myBodyDef);
		//myFixtureDef.shape = &edgeShape;
		//staticBody->CreateFixture(&myFixtureDef);
#pragma endregion

#pragma region Friction and Restitution
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody;
		myBodyDef.position.Set(0, 20);//middle
		b2Body* dynamicBody = m_world->CreateBody(&myBodyDef);

		//prepare a shape definition
		b2PolygonShape polygonShape;
		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &polygonShape;
		myFixtureDef.density = 1;
		myFixtureDef.friction = 0;
		//add four squares shaped fixtures around the body center
		for(int i=0; i<4;i++)
		{
			b2Vec2 pos(sinf(i * 90 * (PI / 180.f)), cosf(i * 90 * (PI / 180.f))); //radial placement
			polygonShape.SetAsBox(1, 1, pos, 0); // a 2x2 rectangle
			myFixtureDef.friction = i / 4.0f; //A different friction for each wing
			myFixtureDef.restitution= i / 4.0f; //A different friction for each wing
			dynamicBody->CreateFixture(&myFixtureDef);
			
		}
		//floor
		myBodyDef.type = b2_staticBody;
		myBodyDef.position.Set(0, 0);
		b2Body* staticBody = m_world->CreateBody(&myBodyDef);
		b2EdgeShape edgeShape;
		edgeShape.Set(b2Vec2(-15, 0), b2Vec2(15, 3));
		myFixtureDef.shape = &edgeShape;
		staticBody->CreateFixture(&myFixtureDef);
#pragma endregion 
	}


	void Step(Settings* settings)
	{
		//Default physics renderign
		Test::Step(settings);
	}

	static Test* Create()
	{
		return new PersonalTestFixtures;
	}

private:
};

#endif

