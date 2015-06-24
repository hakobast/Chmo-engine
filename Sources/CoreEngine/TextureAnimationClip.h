#ifndef TEXTURE_ANIMATION_CLIP_H
#define TEXTURE_ANIMATION_CLIP_H

#include <string>

#include "../Components/TextureAnimator.h"
#include "../Extras/smart_pointer.h"
#include "Texture2D.h"
#include "GameObject.h"

enum AnimationType
{
	ONCE_FIRST,
	ONCE_LAST,
	LOOP,
	PING_PONG
};

class TextureAnimator;

class TextureAnimationClip: public RemovableObject
{
friend class TextureAnimator;
private:
	smart_pointer<Texture2D> texture;
	int startFrame;
	int endFrame;
	int baseFPS;
	int currentFPS;
	int frameCount;
	void Update(GLfloat t, GameObject& obj);
public:
	const std::string clipName;
	AnimationType animType = AnimationType::PING_PONG;
	TextureAnimationClip(const std::string clipName, smart_pointer<Texture2D> texture, int startFrame, int endFrame, int fps);
	TextureAnimationClip(const std::string clipName, smart_pointer<Texture2D> texture, int fps);
};

#endif