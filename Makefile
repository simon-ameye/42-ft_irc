################	COMPILER		#################

CC			=		c++ -Wall -Wextra -Werror -std=c++98 #-fsanitize=address

################	DIRECTORIES		#################

SRCS_DIR	=		srcs

OBJS_DIR	=		obj

#################	HEADER FILES	#################

INCLUDE		=		-I srcs\

#################	SOURCE FILES	#################

SRCS		=		main.cpp \
					Server.cpp

SOURCES		=		$(addprefix $(SRCS_DIR)/,$(SRCS))

#################	OBJECT FILES	#################

OBJS		=		$(addsuffix .o, $(basename $(SRCS)))
OBJECTS		=		$(addprefix $(OBJS_DIR)/,$(OBJS))

################	BINARIES		#################

NAME		=		ircserv

################	TARGETS			#################

all:				$(NAME)

$(NAME):			$(OBJS_DIR) $(OBJECTS)
					@echo Building...
					@$(CC) -DNAMESPACE=$(NAME) $(INCLUDE) $(OBJECTS) -o $(NAME)

$(OBJS_DIR):
					mkdir -p $@

$(OBJECTS):			$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
					@$(CC) -DNAMESPACE=$(NAME) $(INCLUDE) -c $< -o $@

clean:
					@echo Cleaning objects...
					@rm -f $(OBJECTS)

fclean:				clean
					@echo Cleaning binary...

re:					fclean all

.PHONY:				all clean fclean re
