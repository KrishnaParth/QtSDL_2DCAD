#pragma once
#ifndef SDLAPP_H

#include<SDL.h>
#include<qwidget.h>



class SDLApp : public QWidget {

public:
	
	SDLApp(const char* title, int x, int y, int w, int h);
	// Destructor
	~SDLApp();

	// Handle Events
	void SetEventCallback(std::function<void(void)> func);

	// Handle Render
	void SetRenderCallback(std::function<void(void)> func);

	// Loop our application
	void RunLoop();

	// Retrive the renderer
	SDL_Renderer* GetRenderer() const;

	void StopAppLoop();
	
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	bool m_gameIsRunning = true;
	std::function<void(void)> m_EventCallback;
	std::function<void(void)> m_RenderCallback;
	CartesianWindow Graph;
};

#endif // !SDLAPP_H
