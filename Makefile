# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: injah <injah@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/27 15:30:38 by injah             #+#    #+#              #
#    Updated: 2026/04/06 09:55:13 by injah            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = game

SRC_FILES = main.cpp Engine.cpp Player.cpp utils.cpp Sprite.cpp Game.cpp Actor.cpp Level.cpp Zone.cpp NextLevelZone.cpp Slime.cpp AnimatedSpriteComp.cpp Character.cpp Enemy.cpp

SRC_DIR = src
OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.cpp=.o))
DEP = $(OBJ:.o=.d)

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -g -Iinclude

SDL_CFLAGS = $(shell sdl2-config --cflags) $(shell pkg-config --cflags SDL2_image SDL2_ttf)
SDL_LIBS   = $(shell sdl2-config --libs) $(shell pkg-config --libs SDL2_image SDL2_ttf)

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(SDL_CFLAGS) -MMD -MP -c $< -o $@


$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME) $(SDL_LIBS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re