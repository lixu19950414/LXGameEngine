#include "stdafx.h"
#include "Renderer.h"


static Renderer* g_pRenderer = nullptr;

Renderer * Renderer::getInstance()
{
	if (g_pRenderer == nullptr) {
		g_pRenderer = new Renderer();
	}
	return g_pRenderer;
}

Renderer::Renderer()
{
	_glStateBlocks.empty();
}


Renderer::~Renderer()
{
}

void Renderer::applyTopStateBlock()
{
	_glStateBlocks.top().apply();
}

void Renderer::pushDefault2DStateBlock()
{
	GLStateBlock stateBlock;
	stateBlock._flagScissorTest = false;
	_glStateBlocks.push(stateBlock);
}
