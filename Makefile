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
					Server/ServerUtils.cpp\
					Server/ServerDispatcher.cpp\
					Server/ServerCommands/ServerCommandNick.cpp \
					Server/ServerCommands/ServerCommandPass.cpp \
					Server/ServerCommands/ServerCommandOper.cpp \
					Server/ServerCommands/ServerCommandUser.cpp \
					Server/ServerCommands/ServerCommandPing.cpp \
					Server/ServerCommands/ServerCommandCap.cpp \
					Server/ServerCommands/ServerCommandPrivmsg.cpp \
					Server/ServerCommands/ServerCommandNotice.cpp \
					Server/ServerCommands/ServerCommandJoin.cpp \
					Server/ServerCommands/ServerCommandKill.cpp \
					Server/ServerReplies/ServerErrorReplies.cpp\
					Server/ServerReplies/ServerCommandResponses.cpp\
					Server/ServerCommands/ServerCommandMode.cpp \
					Server/ServerCommands/ServerCommandDie.cpp \
					Server/ServerCommands/ServerCommandQuit.cpp \
					Server/ServerCommands/ServerCommandRehash.cpp \
					Server/ServerCommands/ServerCommandRestart.cpp \
					Server/ServerCommands/ServerCommandPart.cpp \
					Server/ServerCommands/ServerCommandTopic.cpp \
					Server/Channel/Channel.cpp \
					Server/Config/Config.cpp

SOURCES		=		$(addprefix $(SRCS_DIR)/,$(SRCS))

#################	HEADER FILES	#################

HEADERS		=		srcs/Server/Server.hpp \
					srcs/Server/ServerSettings.hpp \
					srcs/Server/Channel/Channel.hpp \
					srcs/Server/ServerReplies/CommandResponses.hpp \
					srcs/Server/ServerReplies/ErrorReplies.hpp \
					srcs/Server/User/User.hpp \
					srcs/Utils/Utils.hpp \
					srcs/Server/Config/Config.hpp

#################	OBJECT FILES	#################

OBJS		=		$(addsuffix .o, $(basename $(SRCS)))
OBJECTS		=		$(addprefix $(OBJS_DIR)/,$(OBJS))

################	BINARIES		#################

NAME		=		ircserv

################	TARGETS			#################

all:				$(NAME)

$(NAME):			$(OBJS_DIR) $(HEADERS) $(OBJECTS)
					@echo Building...
					@$(CC) $(OBJECTS) -o $(NAME)

$(OBJS_DIR):
					mkdir -p $@/Utils
					mkdir -p $@/Server
					mkdir -p $@/Server/User
					mkdir -p $@/Server/Channel
					mkdir -p $@/Server/ServerCommands
					mkdir -p $@/Server/ServerReplies
					mkdir -p $@/Server/Config

$(OBJECTS):			$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
					@$(CC) -c $< -o $@

clean:
					@echo Cleaning objects...
					@rm -rf $(OBJS_DIR)

fclean:				clean
					@echo Cleaning binary...
					@rm -f $(NAME)

re:					fclean all

.PHONY:				all clean fclean re
