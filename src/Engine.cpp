/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:52:53 by injah             #+#    #+#             */
/*   Updated: 2026/04/02 17:53:48 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Engine.hpp"

Engine::Engine()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		throw("SDL_Init Error");
	if ((IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)) != (IMG_INIT_PNG | IMG_INIT_JPG))
		throw("IMG_Init Error");
	if (TTF_Init() != 0)
		throw("TTF_Init Error");
	this->screenWidth = 1500;
	this->screenHeight = 900;
	this->window = SDL_CreateWindow("Default", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->screenWidth, this->screenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (this->window == NULL)
	{
		std::cerr << SDL_GetError() << std::endl;
		throw("Window Init Error");
	}
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	if (this->renderer == NULL)
	{
		std::cerr << SDL_GetError() << std::endl;
		throw("Renderer Init Error");
	}
	this->setFps(60);
	std::cout << "Engine Default constructor fps set to " << this->fps << std::endl;
}

Engine::~Engine()
{
	if (this->renderer)
		SDL_DestroyRenderer(this->renderer);
	if (this->window)
		SDL_DestroyWindow(this->window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	std::cout << "Engine Destructor" << std::endl;
}

Engine::Engine(Engine &toCpy)
{
	std::cout << "Engine copy constructor" << std::endl;
	*this = toCpy;
}

Engine &Engine::operator=(const Engine &toCpy)
{
	std::cout << "Engine Overloaded operator = used on " << this << " from " << &toCpy << std::endl;
	if (this != &toCpy)
	{
		
	}
	return (*this);
	
}

void	Engine::setFps(int fps)
{
	this->fps = fps;
	this->targetFrameDuration = 1000.0f / fps;
}






void Engine::run(IProg &prog, int targetFps)
{
	Uint32		last_frame;
	Uint32		frameStart;
	float		deltaTime;
	SDL_Event	event;

	this->isRunning = true;
	this->setFps(targetFps);
	last_frame = SDL_GetTicks();
	while (this->isRunning)
	{
		frameStart = SDL_GetTicks();
		deltaTime = (frameStart - last_frame) / 1000.0f;
		deltaTime = std::min(deltaTime, 0.05f);
		last_frame = frameStart;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				this->isRunning = false;
			prog.handleEvent(event);
		}
		
		prog.update(deltaTime);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		prog.render(this->renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer, screenWidth / 2, 0, screenWidth / 2, screenHeight);
		SDL_RenderPresent(renderer);


		Uint32 frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < this->targetFrameDuration)
			SDL_Delay(this->targetFrameDuration - frameTime);
	}
}

SDL_Renderer	*Engine::getRenderer() const
{
	return (this->renderer);
}

int	Engine::getScreenWidth() const
{
	return (this->screenWidth);
}

int	Engine::getScreenHeight() const
{
	return (this->screenHeight);
}