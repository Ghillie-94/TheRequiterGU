#include "Animation.h"

Animation::Animation(sf::Sprite* newAnimatedSprite, std::string newBaseFilePath, float framesPerSecond, std::string newFileType)
	: animatedSprite(newAnimatedSprite)
	, baseFilePath(newBaseFilePath)
	, fileType(newFileType)
	, currentClip(nullptr)
	, animations()
	, currentFrame(0)
	, timePerFrame(sf::seconds(1.0f / framesPerSecond))
	, aniClock()
	, isPlaying(false)
{
}

Animation::Animation()
{
}

void Animation::AddClip(std::string clipName, int numFrames, bool shouldLoop)
{
	Clip newClip;

	for (int i = 0; i < numFrames; ++i)
	{
		newClip.textures.push_back(sf::Texture());
		newClip.textures[i].loadFromFile(baseFilePath + "_" + clipName + "_" + std::to_string(i + 1) + "." + fileType);
	}

	//add clip to map
	animations[clipName] = newClip;
}

void Animation::Play()
{
	isPlaying = true;
}

void Animation::Play(std::string clipToPlay)
{
	if (animations.find(clipToPlay) != animations.end())
	{
		if (currentClip != &(animations[clipToPlay]))
		{
			currentClip = &(animations[clipToPlay]);
			isPlaying = true;
		}
	}
}

void Animation::Stop()
{
	isPlaying = false;
	currentFrame = 0;
}

void Animation::Pause()
{
	isPlaying = false;
}

void Animation::Update()
{
	if (isPlaying && currentClip != nullptr)
	{
		//process animation
		sf::Time timePassedThisFrame = aniClock.getElapsedTime();
		if (timePassedThisFrame >= timePerFrame)
		{
			aniClock.restart();

			//goto next frame of animation
			++currentFrame;
			if (currentFrame >= currentClip->textures.size())
			{
				if (currentClip->shouldLoop)
				{
					currentFrame = 0;
				}
				else
				{
					currentFrame = currentClip->textures.size() - 1;
					isPlaying = false;
				}
			}
			
			// load the new current frame into sprite
			animatedSprite->setTexture(currentClip->textures[currentFrame]);

		}
	}
}
