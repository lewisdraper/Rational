#pragma once

class Layer {

public:
	virtual void Render(float scale=1) = 0;
	virtual void Update() = 0;

};
