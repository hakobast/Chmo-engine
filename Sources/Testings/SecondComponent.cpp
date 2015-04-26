//
//  TestComponent.h
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#include <iostream>
#include "../CoreEngine/Engine.h"
#include "../CoreEngine/GameLogic.h"

using namespace std;

class SecondComponent: public Renderer
{
/*public:
    
    void Init()
    {

    }
    
    void Update()
    {
		static GLfloat vertices[] = {
			1.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f
		};

		getTransform()->applyTransformation();
		
		glTranslatef(0.0f, 0.0f, -5.0f);

		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableClientState(GL_VERTEX_ARRAY);

		glTranslatef(2.0f, 0.0f, -2.0f);


		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableClientState(GL_VERTEX_ARRAY);
    }*/
};