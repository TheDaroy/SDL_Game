#include "AnimatedTexture.h"
namespace QuickSDL {
	AnimatedTexture::AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animSpeed, ANIM_DIR animDir)
		: Texture(filename, x, y, w, h)
	{
		mTimer = Timer::Instance();

		mStartX = x;
		mStartY = y;

		mFrameCount = frameCount;
		mAnimationSpeed = animSpeed;
		mTimePerFrame = mAnimationSpeed / frameCount;
		mAnimationTimer = 0;

		mAnimDir = animDir;
		mAnimDone = false;
		mWrapMode = loop;
	}

	AnimatedTexture::~AnimatedTexture()
	{
	}

	void AnimatedTexture::WrapMode(WRAP_MODE mode)
	{
		mWrapMode = mode;
	}
	void AnimatedTexture::ResetAnimation()
	{
		mAnimationTimer = 0.0f;
		mAnimDone = false;
	}

	bool AnimatedTexture::IsAnimating()
	{
		return !mAnimDone;
	}
	void AnimatedTexture::Update()
	{
		if (!mAnimDone)
		{
			mAnimationTimer += mTimer->DeltaTime();
		}

		if (mAnimationTimer >= mAnimationSpeed)
		{
			if (mWrapMode == loop)
			{
				mAnimationTimer -= mAnimationSpeed;
			}
			else
			{
				mAnimDone = true;
				mAnimationTimer = mAnimationSpeed - mTimePerFrame;
			}
		}

		if (mAnimDir == horizontal)
		{
			mClippedRect.x = mStartX + (int)(mAnimationTimer / mTimePerFrame) * mWidth;
		}
		else
		{
			mClippedRect.y = mStartY + (int)(mAnimationTimer / mTimePerFrame) * mHeight;
		}
	}
}