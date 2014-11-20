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
#include "ActiveComponent.h"

using namespace std;

class Renderer : public ActiveComponent
{
protected:
	~Renderer();
public:
	void Init();
	void Update();
};

#endif