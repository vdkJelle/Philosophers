# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jelvan-d <jelvan-d@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/31 09:58:25 by jelvan-d      #+#    #+#                  #
#    Updated: 2021/11/26 16:52:04 by jelvan-d      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	philosophers
SRCS		=	initialisation\
				main\
				philosophers\
				philosopher_actions\
				utils
CFILES		=	$(SRCS:%=src/%.c)
OFILES		=	$(SRCS:%=obj/%.o)
INCLUDES	=	./includes/.
FLAGS		=	-Wall -Werror -Wextra
ifdef DEBUG
FLAGS += -g -fsanitize=address
endif

all:	$(NAME)

$(NAME):	$(OFILES)
	@gcc -o $(NAME) $(FLAGS) -I $(INCLUDES) $(OFILES) -lpthread
	@echo "Executable created..."

obj/%.o:	src/%.c
	@mkdir -p $(@D)	
	@echo "Compiling... $^"
	@gcc -o $@ $(FLAGS) -I $(INCLUDES) -c $^

clean:
	@echo "Cleaning..."
	@rm -f $(OFILES)

fclean:		clean
	@echo "Extra cleaning..."
	@rm -f $(NAME)

re:			fclean all
