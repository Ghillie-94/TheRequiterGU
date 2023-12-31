#include "Animation.h"
#include "AssetManager.h"



Animation::Animation(std::string newBaseFilePath, float framesPerSecond, std::string newFileType)
	: SpriteObject()
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

void Animation::AddClip(std::string clipName, int numFrames, bool shouldLoop)
{
	Clip newClip;

	for (int i = 0; i < numFrames; ++i)
	{
		newClip.textures.push_back(&AssetManager::RequestTexture(baseFilePath  + clipName  + std::to_string(i + 1) + "." + fileType));
		
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

void Animation::Update(sf::Time frameTime)
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
			sprite.setTexture(*(currentClip->textures[currentFrame]));

		}
	}
}
