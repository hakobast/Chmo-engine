#ifndef TEXTURE_ANIMATOR_H
#define TEXTURE_ANIMATOR_H

#include "GameLogic.h"
#include "Texture2D.h"
#include "smart_pointer.h"
#include "GameTime.h"
#include "SpriteRenderer.h"
#include "TextureAnimationClip.h"

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