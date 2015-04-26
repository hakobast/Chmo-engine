#ifndef TEXTURE_ANIMATOR_H
#define TEXTURE_ANIMATOR_H

#include "../CoreEngine/GameLogic.h"
#include "../CoreEngine/Texture2D.h"
#include "../CoreEngine/TextureAnimationClip.h"
#include "../Extras/smart_pointer.h"
#include "../Systems/GameTime.h"
#include "SpriteRenderer.h"

class TextureAnimationClip;

class TextureAnimator: public GameLogic
{
private:
	std::vector<smart_pointer<TextureAnimationClip>> clips;
	GLfloat timeSincePlayed;
	smart_pointer<TextureAnimationClip> playingClip;

public:
	void addClip(smart_pointer<TextureAnimationClip> clip);
	void playClip(int index);
	void stop();
	void Update();
	void Init();
	void Create();
};

#endif