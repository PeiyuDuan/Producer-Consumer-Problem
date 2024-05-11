#pragma once
#ifndef __SCENE_ELEMENT_H__
#define __SCENE_ELEMENT_H__

class SceneElement {
protected:
	int x_, y_;
	int width_, height_;
public:
	virtual void Draw() const = 0;

protected:
	SceneElement(int x, int y, int width, int height)
		:x_(x), y_(y), width_(width), height_(height) {}

	virtual ~SceneElement() {}
};

#endif