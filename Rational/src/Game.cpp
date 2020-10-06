#include <iostream>
#include "Core/RationalEngine.h"
#include "Timer/Timer.h"

int main(int argc, char** argv)
{
	RationalEngine::GetInstance()->Init();

	while (RationalEngine::GetInstance()->IsRunning())
	{
		RationalEngine::GetInstance()->Events();
		RationalEngine::GetInstance()->Update();
		RationalEngine::GetInstance()->Render();
		Timer::GetInstance()->Tick();
	}

	RationalEngine::GetInstance()->Clean();

	return 0;
}