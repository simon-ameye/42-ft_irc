################	COMPILER		#################

CC			=		c++ -g -Wall -Wextra -Werror -std=c++98 #-fsanitize=address

################	DIRECTORIES		#################

SRCS_DIR	=		srcs

OBJS_DIR	=		obj

#################	SOURCE FILES	#################

SRCS		=		main.cpp \
					Server/Server.cpp \
					Server/User/User.cpp \
					Utils/Utils.cpp \
					Server/Commands/Nick.cpp \
					Server/Commands/ACommand.cpp

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
					@$(CC) $(OBJECTS) -o $(NAME)

$(OBJS_DIR):
					mkdir -p $@/Utils
					mkdir -p $@/Server
					mkdir -p $@/Server/Commands
					mkdir -p $@/Server/User

$(OBJECTS):			$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
					@$(CC) -c $< -o $@

clean:
					@echo Cleaning objects...
					@rm -rf $(OBJECTS)

fclean:				clean
					@echo Cleaning binary...
					@rm -f $(NAME)

re:					fclean all

.PHONY:				all clean fclean re
