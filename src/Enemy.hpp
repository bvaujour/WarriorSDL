/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 03:49:57 by injah             #+#    #+#             */
/*   Updated: 2026/04/06 09:41:14 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "Header.hpp"
# include "Character.hpp"

class Enemy : public Character
{
	protected:
		void	sendMessageEnemyDead();
	public:
		Enemy();
		virtual ~Enemy();
};
