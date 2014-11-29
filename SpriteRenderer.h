
#include "Renderer.h"
#include "Texture2D.h"
#include "Color.h"

class SpriteRenderer : public Renderer
{
public:
	~SpriteRenderer();
	void Create();
	void Init();
	void Update();
	void setTexture(Texture2D* txt, int frame = 0);
	Color color;
private:
	int frame;
	Texture2D* texture;
};