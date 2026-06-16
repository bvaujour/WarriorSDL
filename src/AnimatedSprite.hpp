/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnimatedSprite.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:01:06 by injah             #+#    #+#             */
/*   Updated: 2026/04/04 12:54:11 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
 #include "Sprite.hpp"

typedef struct	s_anim
{
	unsigned int	maxCol;
	unsigned int	col;
	unsigned int	playRate;
	unsigned int	lastUpdate;
}				t_anim;


class AnimatedSprite : public Sprite
{
	protected:
		std::vector<t_anim>	anims;
		unsigned int		animIndex;
		void				addAnim(int maxCol, int playRate);
		void				changeAnim(unsigned int newAnimIndex);
		void				updateAnimation(t_anim &anim);
	public:
						AnimatedSprite();
		virtual			~AnimatedSprite();
						AnimatedSprite(const AnimatedSprite &toCpy);
		AnimatedSprite	&operator=(const AnimatedSprite &toCpy);
		void			update(float deltaTime, t_ctx &ctx);
		
};
