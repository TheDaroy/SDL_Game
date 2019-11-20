#include "Star.h"

bool Star::sScroll = false;

void Star::Scroll(bool b) {
	sScroll = b;
}

Star::Star(int layer) : Texture("stars.png", 0, 0, 1, 1) {
	mTimer = Timer::Instance();

	int starColor = rand() % 4;

	mClippedRect.x = starColor * 4;

	Pos(Vector2(rand() % Graphics::Instance()->SCREEN_WIDTH, rand() % Graphics::Instance()->SCREEN_HEIGHT));

	mFlickerTimer = 0.0f;
	mFlickerSpeed = 0.15f + ((float)rand() / RAND_MAX) * 0.45f;

	float invLayer = 1.0f / layer;
	Scale(VEC2_ONE * invLayer);
	
	mScrollSpeed = 4.0f / layer;
}

Star::~Star() {
	mTimer = NULL;
}

void Star::ScrollStar() {
	Translate(VEC2_RIGHT * mScrollSpeed);

	Vector2 pos = GetPos(local);

	if (pos.y > Graphics::Instance()->SCREEN_HEIGHT) {
		pos.y = 0.0f;
		pos.x = rand() % Graphics::Instance()->SCREEN_WIDTH;
		Pos(pos);
	}
}

void Star::Update() {
	mFlickerTimer += mTimer->DeltaTime();
	if (mFlickerTimer >= mFlickerSpeed) {
		mVisible = !mVisible;
		mFlickerTimer = 0.0f;
	}

	if (sScroll) {
		ScrollStar();
	}
}

void Star::Render() {
	if (mVisible) {
		Texture::Render();
	}
}