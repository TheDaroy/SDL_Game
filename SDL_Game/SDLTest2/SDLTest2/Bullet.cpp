#include "Bullet.h"

Bullet::Bullet() {


	mTimer = Timer::Instance();

	mSpeed = 1000.0f;

	mTexture = new Texture("SpaceShipSpriteSheet.png", 6, 135, 5, 11);
	mTexture->Parent(this);
	mTexture->Pos(VEC2_ZERO);


	Reload();
}

Bullet::~Bullet() {


	mTimer = NULL;

	delete mTexture;
	mTexture = NULL;
}



void Bullet::Fire(Vector2 pos) {

	Pos(pos);
	Active(true);
};

void Bullet::Reload() {

	Active(false);
}

void Bullet::Update() {
	if (GetActive()) {

		Translate(VEC2_UP * mSpeed * mTimer->DeltaTime() *-1, local);

		Vector2 pos = GetPos();

		if (pos.y < -OFFSCREEN_BUFFER || pos.y > Graphics::Instance()->SCREEN_HEIGHT + OFFSCREEN_BUFFER) {

			Reload();
		}

	}
}

void Bullet::Render() {

	if (GetActive()) {

		mTexture->Render();
	}

}