#pragma once
#ifndef PERSONALTEST_H
#define PERSONALTEST_H
#include "Testbed/Framework/Test.h"

#define PI 3.14159265359f

class PersonalTest: public Test
{
public:
	PersonalTest()
	{
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody; //Dynamic Body;
		myBodyDef.position.Set(0, 20);
		myBodyDef.angle = 0;

		dynamicBody = m_world->CreateBody(&myBodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(1, 1);

		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &boxShape;
		boxFixtureDef.density = 1;

		//Dynamic Bodies
		dynamicBody->CreateFixture(&boxFixtureDef);

		//dynamicBody->SetTransform(b2Vec2(10, 20), 1);
		dynamicBody->SetTransform(b2Vec2(10, 20), 45 * (PI / 180.f)); //45 degrees counter clockwise
		dynamicBody->SetLinearVelocity(b2Vec2(-5, 5));
		dynamicBody->SetAngularVelocity(-90 * (PI / 180.f));

		//Static Bodies
		myBodyDef.type = b2_staticBody;
		myBodyDef.position.Set(0, 10);
		b2Body* staticBody = m_world->CreateBody(&myBodyDef);//adds body to world
		staticBody->CreateFixture(&boxFixtureDef);

		//Kinematic Bodies
		myBodyDef.type = b2_kinematicBody; //this will be a kinematic body
		myBodyDef.position.Set(-18, 11); 
		b2Body* kinematicBody = m_world->CreateBody(&myBodyDef);
		kinematicBody->CreateFixture(&boxFixtureDef);

		kinematicBody->SetLinearVelocity(b2Vec2(1, 0)); //move right 1 unit per second
		kinematicBody->SetAngularVelocity(360 * (PI / 180));


	}


	void Step(Settings*settings)
	{
		//Default physics renderign
		Test::Step(settings);

		//Basic text 
		
		g_debugDraw.DrawString(5, m_textLine, "Now we have a Personal Test");
		m_textLine += 15;

		b2Vec2 pos = dynamicBody->GetPosition();
		float angle = dynamicBody->GetAngle();
		b2Vec2 vel = dynamicBody->GetLinearVelocity();
		float angularVel = dynamicBody->GetAngularVelocity();
		g_debugDraw.DrawString(5, m_textLine,
			"Position:%0.3f,%0.3f Angle:%0.3f", pos.x, pos.y, angle* (180.f / PI));
		m_textLine += 15;
		g_debugDraw.DrawString(5, m_textLine,
			"Velocity:%0.3f,%0.3f Angular velocity:%0.3f", vel.x, vel.y, angularVel*(180.f / PI));
		m_textLine + 15;

		//Code to iterate over all the bodies
		//Iterates over the body list
		//for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext())
		//{
		//	//do something with the body 'b'
		//}

		//Removing a body 
		//m_world->DestroyBody(dynamicBody);
	}
	static Test* Create()
	{
		return new PersonalTest;
	}
private:
	b2Body* dynamicBody;



};

#endif
