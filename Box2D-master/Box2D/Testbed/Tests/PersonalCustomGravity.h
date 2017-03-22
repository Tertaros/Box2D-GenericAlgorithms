#pragma once
#ifndef PERSONALCUSTOMGRAVITY_H
#define PERSONALCUSTOMGRAVITY_H
#include "Testbed/Framework/Test.h"

class PersonalCustomGravity: public Test
{
public:
	PersonalCustomGravity(
	)
	{
		//body definition
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody;

		//shape definition
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(1, 1); //a 2x2 rectangle

									 //fixture definition
		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &polygonShape;
		myFixtureDef.density = 1;
		//create identical bodies in different positions
		for (int i = 0; i < 3; i++) {
			myBodyDef.position.Set(-10 + i * 10, 20);
			bodies[i] = m_world->CreateBody(&myBodyDef);
			bodies[i]->CreateFixture(&myFixtureDef);

		}

		//a static floor to drop things on
		myBodyDef.type = b2_staticBody;
		myBodyDef.position.Set(0, 0);
		b2EdgeShape edgeShape;
		myFixtureDef.shape = &edgeShape;
		edgeShape.Set(b2Vec2(-15, 0), b2Vec2(15, 0));
		m_world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);

		forceOn = false;
		torqueOn = false;

		bodies[0]->SetGravityScale(0);
	}

	void Keyboard(int key)
	{
		switch (key)
		{
		case GLFW_KEY_Q:
			//apply gradual force upwards
			forceOn = !forceOn;
			//bodies[0]->ApplyForce(b2Vec2(0, 50), bodies[0]->GetWorldCenter(), true);
			bodies[0]->ApplyForce(b2Vec2(0, 50), bodies[0]->GetWorldPoint(b2Vec2(1, 1)), true);
			break;
		case GLFW_KEY_W:
			//apply immediate force upwards
			//bodies[1]->ApplyLinearImpulse(b2Vec2(0, 50), bodies[1]->GetWorldCenter(), true);
			bodies[1]->ApplyLinearImpulse(b2Vec2(0, 50), bodies[1]->GetWorldPoint(b2Vec2(1, 1)), true);
			break;
		case GLFW_KEY_E:
			//teleport or 'warp' to new location
			bodies[2]->SetTransform(b2Vec2(10, 20), 0);
			break;
			//Angular Movement
		case GLFW_KEY_A:
			bodies[0]->ApplyTorque(20, true);
			torqueOn = !torqueOn;
			break;
		case GLFW_KEY_S:
			bodies[1]->ApplyAngularImpulse(20, true);
			break;
		default:
			//run default behaviour
			Test::Keyboard(key);
		}
	}
	void Step(Settings* settings)
	{
		//Default physics renderign
		Test::Step(settings);

		if (forceOn)
		{
			//bodies[0]->ApplyForce(b2Vec2(0, 50), bodies[0]->GetWorldCenter(),true);
			bodies[0]->ApplyForce(b2Vec2(0, 50), bodies[0]->GetWorldPoint(b2Vec2(1, 0)), true);
		}

		if (torqueOn)
		{
			bodies[0]->ApplyTorque(20, true);
		}
	}

	static Test* Create()
	{
		return new PersonalCustomGravity;
	}

private:
	b2Body* bodies[3];
	bool forceOn;
	bool torqueOn;
};

#endif
