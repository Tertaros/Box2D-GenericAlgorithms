#pragma once
#ifndef PERSONALROTATIONTEST_H
#define PERSONALROTATIONTEST_H
#include "Testbed/Framework/Test.h"

#define PI 3.14159265359f

class PersonalRotationTest: public Test
{
public:
	PersonalRotationTest(
	)
	{
		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody;

		//Polygon
		b2PolygonShape polygonShape;
		b2Vec2 vertices[6];
		for(int i = 0; i<6;i++)
		{
			float angle = -i / 6.0f * 360 * (PI / 180.f);
			vertices[i].Set(sinf(angle), cosf(angle));
		}
		vertices[0].Set(0, 4); //Pointy  edge
		polygonShape.Set(vertices, 6);

		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &polygonShape;
		myFixtureDef.density = 1;

		myBodyDef.position.Set(0, 10);
		body = m_world->CreateBody(&myBodyDef);
		body->CreateFixture(&myFixtureDef);

		body->SetGravityScale(0); //Disabling gravity

		clickedPoint = b2Vec2(0, 20);


	}

	void MouseDown(const b2Vec2& p)
	{
		clickedPoint = p;

		Test::MouseDown(p);
	}

	void Step(Settings* settings)
	{
		//Default physics renderign
		Test::Step(settings);

		glPointSize(4);
		glBegin(GL_POINTS);
		glVertex2f(clickedPoint.x, clickedPoint.y);
		glEnd();

		//Setting angle directly
		float bodyAngle = body->GetAngle();
		b2Vec2 toTarget = clickedPoint - body->GetPosition();
		float desiredAngle = atan2f(-toTarget.x, toTarget.y);;

	    g_debugDraw.DrawString(5, m_textLine, "Body angle %0.3f", bodyAngle*(180.f / PI));
		m_textLine += 15;
		g_debugDraw.DrawString(5, m_textLine, "Target angle %0.3f", desiredAngle*(180.f / PI));
		m_textLine += 15;

		//body->SetTransform(body->GetPosition(), desiredAngle);

		//Gradual shift
		float totalRotation = desiredAngle - bodyAngle;
		//To prevent unessarry long shifts for rotations bigger than 180
		while (totalRotation < -180 * (PI / 180.0f)) totalRotation += 360 * (PI / 180.0f);
		while (totalRotation >  180 * (PI / 180.0f)) totalRotation -= 360 * (PI / 180.0f);
		//float change = 1 * (PI / 180.0f);
		//float newAngle = bodyAngle + b2Min(change, b2Max(-change, totalRotation));

		//body->SetTransform(body->GetPosition(), newAngle);

		//Torque Never reaching its goal due to  angularMomentum
		//body->ApplyTorque(totalRotation < 0 ? -10 : 10,true);

		//Torque more precise
		float nextAngle = bodyAngle + body->GetAngularVelocity() / 3.f;//60.f
		totalRotation = desiredAngle - nextAngle;
		while (totalRotation < -180 * (PI / 180.0f)) totalRotation += 360 * (PI / 180.0f);
		while (totalRotation >  180 * (PI / 180.0f)) totalRotation -= 360 * (PI / 180.0f);
		//body->ApplyTorque(totalRotation < 0 ? -10 : 10,true);

		//Does not work   the for
		nextAngle = bodyAngle + body->GetAngularVelocity() / 60.0;
		totalRotation = desiredAngle - nextAngle;
		while (totalRotation < -180 * (PI / 180.0f)) totalRotation += 360 * (PI / 180.0f);
		while (totalRotation >  180 * (PI / 180.0f)) totalRotation -= 360 * (PI / 180.0f);
		float desiredAngularVelocity = totalRotation * 60;
		float impulse = body->GetInertia() * desiredAngularVelocity;// disregard time factor
		//body->ApplyAngularImpulse(impulse,true);
		

		//Impulse
		nextAngle = bodyAngle + body->GetAngularVelocity() / 3.0f;
		totalRotation = desiredAngle - nextAngle;
		while (totalRotation < -180 * (PI / 180.0f)) totalRotation += 360 * (PI / 180.0f);
		while (totalRotation >  180 * (PI / 180.0f)) totalRotation -= 360 * (PI / 180.0f);
		desiredAngularVelocity = totalRotation * 60;
		float change = 1 * (PI / 180.0f);
		desiredAngularVelocity = b2Min(change, b2Max(-change, desiredAngularVelocity));
		impulse = body->GetInertia()*desiredAngularVelocity;
		body->ApplyAngularImpulse(impulse,true);

		

	}

	static Test* Create()
	{
		return new PersonalRotationTest;
	}

private:
	b2Body* body;
	b2Vec2 clickedPoint;
};

#endif
