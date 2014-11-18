//
//  GameLogicSystem.h
//  EngineTesting
//
//  Created by Hakob on 11/13/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#ifndef EngineTesting_GameLogicSystem_h
#define EngineTesting_GameLogicSystem_h

#include "Libs.h"

class GameLogicSystem:public System
{
public:
    virtual ~GameLogicSystem();
    void Init();
    void Update(float delta);
    void addComponent(Component &c);
    void removeComponent(Component &c);
};

#endif
