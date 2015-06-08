
#include <iostream>

#include "../../Sources/CoreEngine/ChmoEngine.h"
#include "../../Sources/Extras/GLUtils.h"

class HelloEngine : public GameLogic
{
public:
	void Init()
	{
		GameObject* camerObj = new GameObject("Camera");
		camerObj->getTransform()->Location.set(0.0f, 0.0f, 10.0f);

		Camera* camera = camerObj->addComponent<Camera>();
		camera->setProjectionMode(ProjectionMode::ORTHOGRAPHIC);
		camera->setOrthoSize(5.0f);
		camera->setFOVY(60.0f);

		AssetFile vertexShaderAsset = Engine::GetInstance().assetLoader->loadAsset("UnlitSprite.vert");
		AssetFile fragmentShaderAsset = Engine::GetInstance().assetLoader->loadAsset("UnlitSprite.frag");
		smart_pointer<Material> mat(new Material("Unlit",
			(char*)vertexShaderAsset.data, vertexShaderAsset.length,
			(char*)fragmentShaderAsset.data, fragmentShaderAsset.length));

		smart_pointer<Texture2D> textureTransparent = LoadTexture("vtr.bmp");
		mat->addTexture(textureTransparent);
		mat->setColor(Color::WHITE);

		for (int i = 0; i < 1; i++)
		{
			GameObject* obj = new GameObject("FirstGameObject");
			obj->addComponent<SpriteRenderer>()->setMainMaterial(mat);

			float scale = 1.0f;
			obj->getTransform()->Location.set(0.0f, 0.0f, -2.0f);
			//obj->getTransform()->RotateX(90);
			obj->getTransform()->ScaleLocal *= scale;
		}

		std::vector<unsigned int> indices{ 0, 1, 2, 3, 0, 2 };
		std::vector<Vector3> verts{ Vector3(-1.0f, -1.0f, 0.0f), Vector3(1.0f, -1.0f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), Vector3(-1.0f, 1.0f, 0.0f) };
		std::vector<Vector2> texcoords{ Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), Vector2(1.0f, 1.0f), Vector2(0.0f, 1.0f) };

		smart_pointer<Mesh> mesh(new Mesh);
		mesh->setSubMeshCount(1);
		mesh->setVertices(&verts);
		mesh->setTexCoords(&texcoords);
		mesh->setIndices(&indices);

		for (int i = 0; i < 0; i++)
		{
			GameObject* obj = new GameObject("MY OBJ");
			MeshRenderer* meshRend = obj->addComponent<MeshRenderer>();
			meshRend->setMainMaterial(mat);
			meshRend->setMesh(mesh);
			obj->getTransform()->Location.set(1.0f*i, 0.0f, -2.0f);
		}

		Engine::GetInstance().assetLoader->releaseAsset(&vertexShaderAsset);
		Engine::GetInstance().assetLoader->releaseAsset(&fragmentShaderAsset);
	}

	void Update()
	{
		frames++;
		time += GameTime::DeltaTime();

		if (time >= 1.0f)
		{
			Logger::Print("FPS %d", frames);
			
			//Logger::Print("DELTA TIME %f", GameTime::DeltaTime());
			//Logger::Print("TIME SINCE STARTED %f", GameTime::TimeSinceGameStarted());

			time = 0;
			frames = 0;
		}

		Vector2 v;
		Vector2 delta;
		if (Input::GetTouchCount() > 0)
		{
			for (int i = 0, len = Input::GetTouchCount(); i < len; i++)
			{
				const Touch& touch = Input::GetTouch(i);
				touch.getPosition(v);
				touch.getDeltaPosition(delta);
				Logger::Print("Touch: id=%d, pos=(%f,%f), action=%d", touch.getTouchId(), v.x, v.y, touch.getAction());
				Logger::Print("Touch: delta=(%f,%f)",  delta.x, delta.y);
			}
		}
	}

private:
	int frames = 0;
	GLfloat time;
};