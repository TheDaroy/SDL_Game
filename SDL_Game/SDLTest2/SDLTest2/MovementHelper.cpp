#include "MovementHelper.h"
namespace QuickSDL
{

	Vector2 QuickSDL::MoveTowards(Vector2 currentPos, Vector2 targetPos)
	{

		Vector2 direction;
		direction = targetPos - currentPos;
		return direction.Normalized();

	}

}