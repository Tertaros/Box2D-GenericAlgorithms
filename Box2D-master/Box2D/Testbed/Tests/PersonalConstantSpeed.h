#pragma once
#ifndef PERSONALCONSTANTSPEED_H
#define PERSONALCONSTANTSPEED_H
#include "Testbed/Framework/Test.h"

class PersonalConstantSpeed: public Test
{
public:
	PersonalConstantSpeed()
	{
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody;

		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(1, 1);

		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &polygonShape;
		myFixtureDef.density = 1;

		myBodyDef.position.Set(0, 10);
		body = m_world->CreateBody(&myBodyDef);
		body->CreateFixture(&myFixtureDef);

		myBodyDef.type = b2_staticBody;
		myBodyDef.position.Set(0, 0);
		b2Body* staticBody = m_world->CreateBody(&myBodyDef);

		//4 walls;
		polygonShape.SetAsBox(20, 1, b2Vec2(0, 0), 0); //Ground
		staticBody->CreateFixture(&myFixtureDef);
		polygonShape.SetAsBox(20, 1, b2Vec2(0, 40), 0);//Top
		staticBody->CreateFixture(&myFixtureDef);
		polygonShape.SetAsBox(1, 20, b2Vec2(-20, 20), 0);//left
		staticBody->CreateFixture(&myFixtureDef);
		polygonShape.SetAsBox(1, 20, b2Vec2(20, 20), 0);//Right
		staticBody->CreateFixture(&myFixtureDef);

		moveState = MS_STOP;
	}

	void Keyboard(int key)
	{
		switch (key)
		{
		case GLFW_KEY_Q:
			moveState = MS_LEFT;
			break;
		case GLFW_KEY_W:
			moveState = MS_STOP;
			break;
		case GLFW_KEY_E:
			moveState = MS_RIGHT;
			break;
		}
	}

	void Step(Settings*settings)
	{
		//Default physics renderign
		Test::Step(settings);

		//Setting Velocity Directly
		b2Vec2 vel = body->GetLinearVelocity();
		//switch (moveState)
		//{
		//case MS_LEFT: vel.x = -5;
		//	break;
		//case MS_STOP: vel.x = 0; 
		//	break;
		//case MS_RIGHT: vel.x = 5;
		//	break;
		//}


		//Gradual Target Velocity
		//switch (moveState)
		//{
		//case MS_STOP: vel.x *= 0.98; 
		//	break;
		//case MS_LEFT: vel.x = b2Max(vel.x - 0.1f, -5.0f);
		//	break;
		//case MS_RIGHT: vel.x = b2Max(vel.x - 0.1f, 5.0f);
		//	break;

		//}

		//body->SetLinearVelocity(vel);


		//Gradual force
		float force = 0;
		//switch (moveState)
		//{
		//case MS_STOP: force = vel.x *-10; break;
		//case MS_LEFT: if (force = vel.x > -5) force = -50; break;
		//case MS_RIGHT: if (force = vel.x > 5) force = 50; break;
		//}
		//
		//Instantanious velocity with force

		float desiredVel = 0;
		//switch (moveState)
		//{
		//case MS_STOP: desiredVel = 0; break;
		//case MS_LEFT: desiredVel = -5; break;
		//case MS_RIGHT: desiredVel = 5; break;
		//}

		//float velChange = desiredVel - vel.x;
		//force = body->GetMass()*velChange / (1 / 60.0f); //f=mv/t;
		//body->ApplyForce(b2Vec2(force, 0), body->GetWorldCenter(), true);

		//Velocity with impulses

		switch (moveState)
		{
		case MS_STOP: desiredVel = 0; break;
		case MS_LEFT: desiredVel = -5; break;
		case MS_RIGHT: desiredVel = 5; break;
		}

		float velChange = desiredVel - vel.x;
		float impulse = body->GetMass()*velChange;
		body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(),true);

	}
	static Test* Create()
	{
		return new PersonalConstantSpeed;
	}
private:
	enum MoveState
	{
		MS_STOP,
		MS_LEFT,
		MS_RIGHT,
	};

	b2Body*body;
	MoveState moveState;

};

#endif
