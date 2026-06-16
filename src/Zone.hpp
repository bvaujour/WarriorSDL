/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zone.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: injah <injah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 00:52:44 by injah             #+#    #+#             */
/*   Updated: 2026/04/02 01:22:36 by injah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "Header.hpp"
# include "Actor.hpp"

class Zone : public Actor
{
	protected:
	public:
								Zone();
		virtual					~Zone();
};