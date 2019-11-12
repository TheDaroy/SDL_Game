#pragma once
#include "MathHelper.h"
class GameEntity {

public:
	enum SPACE {local = 0, world = 1};

#pragma region Functions
	GameEntity(float x = 0, float y = 0);
	~GameEntity();

	void Pos(Vector2 pos);
	Vector2 GetPos(SPACE space = world);

	void Rotation(float rotation);
	float GetRotation(SPACE space = world);

	void Scale(Vector2 scale);
	Vector2 GetScale(SPACE space = world);

	void Active(bool active);
	bool GetActive();

	void Parent(GameEntity* parent);
	GameEntity* Parent();
	void Translate(Vector2 vec);
	void Rotate(float amount);

	virtual void Update();
	virtual void Render();
#pragma endregion
private:
	Vector2 mPos;
	float mRotation;
	Vector2 mScale;
	bool mActive;
	GameEntity* mParent;

};