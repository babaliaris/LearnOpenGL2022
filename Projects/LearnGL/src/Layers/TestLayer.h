#pragma once
#include <core/Layer.h>
#include <core/logger.h>

class TestLayer : public LearnOpenGL::Layer
{
public:

	void OnStart() override
	{
		LEARN_OPENGL_INFO("TestLayer OnStart()");
	}

	void OnUpdate() override
	{
		LEARN_OPENGL_INFO("TestLayer OnUpdate()");
	}

};

