

#include <iostream>
#include <chrono>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <memory>

#include "CoreEngine/ChmoEngine.h"

#include "Testings/Ship.h"
#include "Testings/FPSCounter.cpp"
#include "Testings/GLTestComponent.cpp"
#include "Testings/SecondComponent.cpp"
#include "Testings/TestComponent.cpp"
#include "CoreEngine/WinGLUTDisplayModule.h"
#include "CoreEngine/WinAssetLoader.h"
#include "CoreEngine/DisplayModuleObserver.h"


#define TARGET_FPS 60

void CreateGame();

int main(int argc, char **argv)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	WinAssetLoader* assetLoader = new WinAssetLoader;
	WinGLUTDisplayModule* displayModule = new WinGLUTDisplayModule(&argc, argv, GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH, 800, 600, "ENGINE");

	//creating engine
	Engine::getInstance().assetLoader = assetLoader;
	Engine::getInstance().displayModule = displayModule;
	Engine::getInstance().Create();

	CreateGame();

	glutMainLoop(); //TEMP

	return 0;
}

void CreateGame()
{
	//creating game logics
// 	GameObject* lightObj = new GameObject("FPSGameObject");
// 
// 	Light* light = lightObj->addComponent<Light>();
// 	light->setLight(0);
// 	light->setAmbient(Color(0.0f, 0.0f, 0.0f));
// 	light->setDiffuse(Color(1.0f, 0.0f, 0.0f));
// 	light->setSpecular(Color(0.0f, 0.0f, 0.0f));
// 	light->setLightType(POSITIONAL);
	//light->setLinearAttenuation(0.1f);
	//light->setSpotCutoff(15.0f);

	AssetFile vertexShaderAsset = Engine::getInstance().assetLoader->loadAsset("Resources/Shaders/UnlitSprite.vert");
	AssetFile fragmentShaderAsset = Engine::getInstance().assetLoader->loadAsset("Resources/Shaders/UnlitSprite.frag");

	smart_pointer<Material> mat(new Material("Unlit", (char*)vertexShaderAsset.data, vertexShaderAsset.length, (char*)fragmentShaderAsset.data, fragmentShaderAsset.length));

	Engine::getInstance().assetLoader->releaseAsset(&vertexShaderAsset);
	Engine::getInstance().assetLoader->releaseAsset(&fragmentShaderAsset);

	GameObject* camerObj = new GameObject("Camera");
	camerObj->addComponent<GLTestComponent>();
	camerObj->addComponent<FPSCounter>();
	camerObj->getTransform()->Location.set(0.0f, 0.0f, 10.0f);

	Camera* camera = camerObj->addComponent<Camera>();
	camera->setProjectionMode(ProjectionMode::PERSPECTIVE);
	camera->setOrthoSize(5.0f);
	camera->setFOVY(60.0f);

	int regions[4] = { 0, 0, 128, 128 };
	smart_pointer<Texture2D> texture = LoadTexture("Resources/heightmap2.bmp");
	smart_pointer<Texture2D> textureTransparent = LoadTexture("Resources/vtr.bmp");

	/*smart_pointer<Material> mat = Material::Unlit();*/
	mat->addTexture(textureTransparent);
	mat->setColor(Color::WHITE);

	for (int i = 0; i < 0; i++)
	{
		GameObject* obj = new GameObject("FirstGameObject");
// 		obj->addComponent<Terrain>();
// 		obj->getComponent<Terrain>()->setMainMaterial(mat);
// 		obj->getComponent<Terrain>()->build(texture, 1.0f);
		//obj->addComponent<TextureAnimator>()->addClip(clip); 
		//obj->getComponent<TextureAnimator>()->playClip(0);
		//obj->addComponent<GLTestComponent>();
		obj->addComponent<SpriteRenderer>()->setMainMaterial(mat);
		//obj->getComponent<SpriteRenderer>()->addMaterial(mat);
		//obj->getComponent<SpriteRenderer>()->setMainTexture(textureTransparent);
	//	obj->getComponent<SpriteRenderer>()->setColor(Color(1.0f,1.0f,1.0f,0.5f));
		//obj->getComponent<SpriteRenderer>()->setTextureFrame(rand() % 6);
		//obj->getComponent<SpriteRenderer>()->setSortingLayer(SortingLayer::Default, 2);
		//obj->getTransform()->Location.set(-10.0f + rand() % 20, -10.0f + rand() % 20, -20.0f);

		float scale = 1.0f;
		obj->getTransform()->Location.set(0.0f, 0.0f, -2.0f);
		//obj->getTransform()->RotateX(90);
		obj->getTransform()->ScaleLocal *= scale;
	}

	// **************** MODEL ****************
	// 	char* mesh_path = "C:/Users/user/Dropbox/Scripts/OBJ Loader/cube.obj";
	// 	char* mat_path = "C:/Users/user/Dropbox/Scripts/OBJ Loader/cube.mtl";
	// 
	// 	std::vector<GameObject*> objects = LoadModel(mesh_path, mat_path);
	// 
	// 	for (GameObject* obj : objects)
	// 	{
	// 		obj->getTransform()->Location.set(0.0f, 0.0f, 5.0f);
	// 		obj->getTransform()->RotateX(25);
	// 		obj->getTransform()->RotateY(25.0f);
	// 		obj->getTransform()->RotateZ(75.0f);
	// 	}
	// 
	// 	smart_pointer<Mesh>& mesh = objects[0]->getComponent<MeshRenderer>()->getSharedMesh();

	std::vector<unsigned int> indices{ 0, 1, 2, 3, 0, 2 };
	std::vector<Vector3> verts{ Vector3(-1.0f, -1.0f, 0.0f), Vector3(1.0f, -1.0f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), Vector3(-1.0f, 1.0f, 0.0f) };
	std::vector<Vector2> texcoords{ Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), Vector2(1.0f, 1.0f), Vector2(0.0f, 1.0f) };

	smart_pointer<Mesh> mesh(new Mesh);
	mesh->setSubMeshCount(1);
	mesh->setVertices(verts);
	mesh->setUVs(texcoords);
	mesh->setIndices(indices);

	for (int i = 0; i < 1; i++)
	{
		GameObject* obj = new GameObject("MY OBJ");
		MeshRenderer* meshRend = obj->addComponent<MeshRenderer>();
		meshRend->setMainMaterial(mat);
		meshRend->setMesh(mesh);

		obj->getTransform()->Location.set(0.0f, 0.0f, -2.0f);
	}
}