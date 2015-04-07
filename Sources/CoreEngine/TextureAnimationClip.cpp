
#include "TextureAnimationClip.h"

TextureAnimationClip::TextureAnimationClip(const std::string clipName, smart_pointer<Texture2D> texture,
	int startFrame, int endFrame, int fps) :clipName(clipName), texture(texture), startFrame(startFrame), endFrame(endFrame), baseFPS(fps)
{
	frameCount = endFrame - startFrame + 1;
}

TextureAnimationClip::TextureAnimationClip(const std::string clipName, smart_pointer<Texture2D> texture,
	int fps) : TextureAnimationClip(clipName, texture, 0, texture->getFrameCount()-1, fps)
{

}

void TextureAnimationClip::Update(GLfloat t, GameObject& obj)
{
	GLfloat frameTime = 1.0f / baseFPS;
	GLfloat framesTime = frameCount*frameTime;
	GLint frame = (int)(t / frameTime);
	 
	switch (animType)
	{
	case ONCE_FIRST:
		if (frame >= frameCount)
			frame = startFrame;
		break;
	case ONCE_LAST:
		if (frame >= frameCount)
			frame = endFrame;
		break;
	case LOOP:
		frame %= frameCount;
		break;
	case PING_PONG:
		if ((frame/frameCount)%2 == 0)
			frame %= frameCount;
		else
			frame = (frameCount-1) - frame%frameCount;
		break;
	}

	SpriteRenderer* spRend = obj.getComponent<SpriteRenderer>();
	if (spRend != NULL)
	{
		spRend->setMainTexture(texture);
		spRend->setTextureFrame(frame);
	}
}