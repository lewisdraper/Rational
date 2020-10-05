#include <iostream>
#include "Core/RationalEngine.h"

int main(int argc, char** argv)
{
	RationalEngine::GetInstance()->Init();

	while (RationalEngine::GetInstance()->IsRunning())
	{
		RationalEngine::GetInstance()->Events();
		RationalEngine::GetInstance()->Update();
		RationalEngine::GetInstance()->Render();
	}

	RationalEngine::GetInstance()->Clean();

	return 0;
}