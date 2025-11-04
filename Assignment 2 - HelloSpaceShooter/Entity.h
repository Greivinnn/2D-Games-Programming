#pragma once
#include <XEngine.h>

class Entity
{
public:
	Entity() {}
	virtual ~Entity() {}

	// abstract
	virtual void Load() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Unload() = 0;
};

