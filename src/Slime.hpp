/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Slime.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 12:34:49 by injah             #+#    #+#             */
/*   Updated: 2026/04/06 09:50:48 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "Enemy.hpp"
# include "AnimatedSpriteComp.hpp"


typedef	enum	e_slimeAnim
{
	SLIMEIDLE,
	SLIMERUN,
	SLIMEATTACK,
	SLIMEDEATH,
}				e_slimeAnim;

class Slime : public Enemy
{
	private:
		AnimatedSpriteComp	body;
	public:
		~Slime();
		Slime(int posX, int posY, SDL_Texture *texture);

		void	update(float deltaTime, t_ctx &ctx);
		void	render(SDL_Renderer *renderer, SDL_Point camera);

};