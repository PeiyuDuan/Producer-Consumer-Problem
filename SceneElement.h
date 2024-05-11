/*
*  本文件完成 SceneElement 的书写
*    
*    SceneElement 所有元素的抽象，是虚基类，不可被实例化
*   
*    包含大小、位置元素，有虚函数 Draw() 将元素画在屏幕上
*
*/

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