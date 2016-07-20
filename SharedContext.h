#ifndef SHARED_CONTEXT_H
#define SHARED_CONTEXT_H

#include "RandNumberGenerator.h"
#include "Window.h"

struct SharedContext
{
	SharedContext() : m_window(nullptr), m_randNumbGen(nullptr) {}

	RandNumberGenerator* m_randNumbGen;
	Window* m_window;
};

#endif // !SHARED_CONTEXT_HG
