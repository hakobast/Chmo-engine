//
//  Transform.h
//  OpenGLTesting
//
//  Created by Hakob on 11/7/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#ifndef OpenGLTesting_Renderer_h
#define OpenGLTesting_Renderer_h

#include <GL\glut.h>
#include "Component.h"
#include "Behaviour.h"

using namespace std;

class Renderer : public Behaviour
{
public:
	~Renderer();
	void Init();
	void Update(float deltaTime);
};

#endif