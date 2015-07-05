#include "TestComponent.h"
#include "FPSCounter.cpp"

void TestComponent::Create()
{

}

void TestComponent::Init()
{
	GameObject* camerObj = new GameObject("Camera");
	Camera* camera = camerObj->addComponent<Camera>();
	camera->setProjectionMode(ProjectionMode::ORTHOGRAPHIC);
	camera->setOrthoSize(5.0f);

	camerObj->addComponent<FPSCounter>();
	camerObj->getTransform()->setPosition(Vector3(0.0f, 0.0f, 10.0f));

	smart_pointer<Material> mat = AssetManager::LoadMaterial("UnlitSprite",
		"Resources/Shaders/UnlitSprite.vert",
		"Resources/Shaders/UnlitSprite.frag");

 	smart_pointer<Texture2D> texture = AssetManager::LoadTexture("Resources/af_0.png");
	smart_pointer<Texture2D> secondTexture = AssetManager::LoadTexture("Resources/Burn.png");

 	mat->setMainTexture(texture);
	mat->setTexture(secondTexture, "secondTexture");
	
	BitmapFontRenderer* bitFontRend = (new GameObject("BitmapRenderer"))->addComponent<BitmapFontRenderer>();
	bitFontRend->setFont(AssetManager::LoadFont("Resources/af.fnt"));
	bitFontRend->setMainMaterial(mat);
	bitFontRend->setColor(Color::RED());
	bitFontRend->setSortingLayer(1, 0);

	SpriteRenderer* spRend = (new GameObject("SpriteRenderer"))->addComponent<SpriteRenderer>();
	spRend->setMainMaterial(bitFontRend->getMaterial());
	//spRend->setMainMaterial(mat);
	spRend->getMaterial()->setColor("Color", Color::YELLOW());
	//spRend->setColor(Color::GREEN());
	spRend->setSortingLayer(1, 1);
}

void TestComponent::Update()
{

}