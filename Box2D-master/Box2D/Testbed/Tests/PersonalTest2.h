#pragma once
#ifndef classDefine
#define classDefine
#include "Testbed/Framework/Test.h"

class className: public Test
{
public:
	className(
	)
	{}


	void Step(Settings* settings)
	{
		//Default physics renderign
		Test::Step(settings);
	}

	static Test* Create()
	{
		return new className;
	}

private:
};

#endif
