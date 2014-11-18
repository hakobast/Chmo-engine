//
//  GameLogicSystem.h
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#ifndef EngineTesting_RenderSystem_h
#define EngineTesting_RenderSystem_h

#include "Libs.h"

class RenderSystem :public System
{
public:
	virtual ~RenderSystem();
	void Init();
	void Update(float delta);
	void addComponent(Component &c);
	void removeComponent(Component &c);
};

#endif
