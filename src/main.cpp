/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:31:05 by injah             #+#    #+#             */
/*   Updated: 2026/04/03 19:42:24 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header.hpp"
#include "Engine.hpp"
#include "Game.hpp"

int main()
{
	try
	{
		Engine	engine;
		Game	game(engine.getRenderer(), engine.getScreenWidth(), engine.getScreenHeight());

		engine.run(game, 60);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}