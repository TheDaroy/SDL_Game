#include "GameManager.h"

int main(int argc, char* argv[])
{
	QuickSDL::GameManager* game = QuickSDL::GameManager::Instance();

	game->Run();

	QuickSDL::GameManager::Release();
	game = nullptr;
	return 0;
}