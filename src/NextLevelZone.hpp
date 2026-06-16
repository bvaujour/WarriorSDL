/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NextLevelZone.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 01:37:58 by injah             #+#    #+#             */
/*   Updated: 2026/04/02 18:53:03 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "Zone.hpp"


class NextLevelZone : public Zone
{
	private:
		std::string	nextLevel;
		std::string	nextPlayerStart;
	public:
				NextLevelZone();
				NextLevelZone(SDL_Rect rect, const std::string &nextLevel, const std::string &nextPlayerStart);
				~NextLevelZone();
		void	update(float deltaTime, t_ctx &ctx);
		void	render(SDL_Renderer *renderer, SDL_Point camera);
};

