NAME		=	cub3D

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror 

INCLUDES	=	includes
PARSER_H	=	parser.h
EXECUTOR_H	=	executor.h

LIBFT		=	./libft/libft.a

SRCS_DIR			=	srcs
SRCS_DIR_PARSER		=	srcs/parser
SRCS_DIR_EXECUTOR	=	srcs/executor

SRCS_LIST	=	main.c \
				shit.c \
				init.c

SRCS		=	$(addprefix $(SRCS_DIR)/,$(SRCS_LIST))

SRCS_LIST_PARSER	=

SRCS_PARSER			=	$(addprefix $(SRCS_DIR_PARSER)/,$(SRCS_LIST_PARSER))

SRCS_LIST_EXECUTOR	=

SRCS_EXECUTOR		=	$(addprefix $(SRCS_DIR_EXECUTOR)/,$(SRCS_LIST_EXECUTOR))

SRCS += $(SRCS_DIR_PARSER)
SRCS += $(SRCS_EXECUTOR)

OBJS_DIR	=	objs

OBJS		=	$(addprefix $(OBJS_DIR)/,$(SRCS_LIST:.c=.o))
OBJS		+=	$(addprefix $(OBJS_DIR)/,$(SRCS_LIST_PARSER:.c=.o))
OBJS		+=	$(addprefix $(OBJS_DIR)/,$(SRCS_LIST_EXECUTOR:.c=.o))

NORMAL		=	\033[0m
BOLD		=	\033[1m
UNDERLINE	=	\033[4m
BLACK		=	\033[1;30m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
VIOLET		=	\033[1;35m
CYAN		=	\033[1;36m
WHITE		=	\033[1;37m

all : $(OBJS_DIR) $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit $^ -o $@
	@echo "$(GREEN)Project succesfully compiled$(NORMAL)"

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c $(INCLUDES)/$(HEADER) $(INCLUDES)/$(PARSER_H) $(INCLUDES)/$(EXECUTOR_H)  Makefile
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Creating object file$(WHITE) --> $(notdir $@) --> $(GREEN)[Done]$(NORMAL)"

$(OBJS_DIR)/%.o : $(SRCS_DIR)/parser/%.c $(INCLUDES)/$(HEADER) $(INCLUDES)/$(PARSER_H) $(INCLUDES)/$(EXECUTOR_H)  Makefile
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Creating object file$(WHITE) --> $(notdir $@) --> $(GREEN)[Done]$(NORMAL)"

$(OBJS_DIR)/%.o : $(SRCS_DIR)/executor/%.c $(INCLUDES)/$(HEADER) $(INCLUDES)/$(PARSER_H) $(INCLUDES)/$(EXECUTOR_H) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BLUE)Creating object file$(WHITE) --> $(notdir $@) --> $(GREEN)[Done]$(NORMAL)"

$(OBJS_DIR) :
	@mkdir -p objs
	@echo "$(CYAN)Creating directory for objects file$(WHITE) --> $@ --> $(GREEN)[Done]$(NORMAL)"

$(LIBFT) : ./libft/Makefile ./libft/libft.h ./libft/*.c
	@make -C ./libft
	@make bonus -C ./libft
	@echo "$(CYAN)Creating library 'libft'$(WHITE) --> libft.a --> $(GREEN)[Done]$(NORMAL)"

clean :
	@make clean -C ./libft
	@rm -rf $(OBJS_DIR)
	@echo "$(VIOLET)Removing objects files$(WHITE) --> *.o --> $(GREEN)[Done]$(NORMAL)"

fclean : clean
	@make fclean -C ./libft
	@rm -rf $(NAME)
	@echo "$(VIOLET)Removing perfoming file$(WHITE) --> $(NAME) --> $(GREEN)[Done]$(NORMAL)"

re : fclean all

.PHONY : all, clean, fclean, re
