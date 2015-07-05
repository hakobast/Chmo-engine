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

	SpriteRenderer* spRend = getGameObject()->addComponent<SpriteRenderer>();
	smart_pointer<Material> mat = AssetManager::LoadMaterial("UnlitSprite",
		"Resources/Shaders/UnlitSprite.vert",
		"Resources/Shaders/UnlitSprite.frag");

	smart_pointer<Texture2D> texture = AssetManager::LoadTexture("Resources/af_0.png");
	mat->setMainTexture(texture);
	mat->setColor(Color::WHITE);

	spRend->setMainMaterial(mat);
}

void TestComponent::Update()
{

}