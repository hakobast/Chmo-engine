
#ifndef OOPTesting_ChmoEngine_h
#define OOPTesting_ChmoEngine_h


#include "LIBS.h"
#include "Engine.h"
#include "ActiveComponent.h"
#include "AssetManager.h"
#include "Component.h"
#include "GameLogic.h"
#include "GameObject.h"
#include "Material.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "TextureAnimationClip.h"
#include "TextureAtlas.h"
#include "TextureRegion.h"
#include "TextureTiled.h"
#include "Transform.h"

#include "../Systems/GameTime.h"
#include "../Systems/Input.h"

#if defined(_WIN32) || defined (__APPLE__) //TODO implement functionality for OpenGL ES
#include "../Components/Light.h"
#endif

#include "../Components/Camera.h"
#include "../Components/MeshRenderer.h"
#include "../Components/Renderer.h"
#include "../Components/SpriteRenderer.h"
#include "../Components/Terrain.h"
#include "../Components/TextureAnimator.h"

#include "../Extras/Color.h"
#include "../Extras/Matrix4.h"
#include "../Extras/smart_pointer.h"
#include "../Extras/Vectors.h"

#include "../Debug/Logger.h"

#endif