#pragma once
#include <XEngine.h>

class Entity
{
public:
	Entity() {};
	virtual ~Entity() {};

	// abstract functions
	virtual void Load() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Unload() = 0;
private:

};
