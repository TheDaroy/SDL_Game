#pragma once
#include "Texture.h"
#include "Timer.h"
namespace QuickSDL {
	class AnimatedTexture : public Texture {

	public:

		enum WRAP_MODE { once = 0, loop = 1 };
		enum ANIM_DIR { horizontal = 0, vertical = 1 };


		AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animSpeed, ANIM_DIR animDir);
		~AnimatedTexture();

		void WrapMode(WRAP_MODE mode);
		void Update();
		void ResetAnimation();

		bool IsAnimating();

	private:

		Timer* mTimer;

		int mStartX;
		int mStartY;

		float mAnimationTimer;
		float mAnimationSpeed;
		float mTimePerFrame;

		int mFrameCount;

		WRAP_MODE mWrapMode;
		ANIM_DIR mAnimDir;

		bool mAnimDone;



	};
}