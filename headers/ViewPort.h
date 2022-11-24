#pragma once
#ifndef VIEWPORT_H

#include"Vector2D.h"
#include"Point.h"
#include<SDL.h>

class View {

public:
	inline static View* getInstance() { return instance; }

	SDL_Rect get_View_Box() { return m_viewBox; }
	Vector2D get_Position() { return m_position; }
	void set_target(Point* target) { m_target = target; }
	void Update(float dt);
private:
	View() { m_viewBox = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT } };

	Point* m_target;
	Vector2D m_position;

	SDL_Rect m_viewBox;
	static View* instance;


};

#endif // !VIEWPORT_H
