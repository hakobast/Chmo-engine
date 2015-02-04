
#include "TextureAnimator.h"


void TextureAnimator::Create()
{

}

void TextureAnimator::Init()
{

}

void TextureAnimator::Update()
{
	if (!playingClip.isEmpty())
	{
		playingClip->Update(GameTime::TimeSinceGameStarted() - timeSincePlayed,*getGameObject());
	}
}

void TextureAnimator::addClip(smart_pointer<TextureAnimationClip> clip)
{
	clips.push_back(clip);
}

void TextureAnimator::playClip(int index)
{
	if (index < clips.size())
	{
		playingClip = clips[index];
		timeSincePlayed = GameTime::TimeSinceGameStarted();
	}
}

void TextureAnimator::stop()
{
	if (!playingClip.isEmpty())
		playingClip.free();
}