# *********************************************** #
#      ____  ____ ___  ____ _____  ____ ______    #
#     / __ \/ __ `__ \/ __ `/ __ \/ __ `/ ___/    #
#    / /_/ / / / / / / /_/ / / / / /_/ / /        #
#    \____/_/ /_/ /_/\__,_/_/ /_/\__,_/_/         #
#                                                 #
#    Makefile                                     #
#    By: omanar <omanar@student.1337.ma>          #
#    Created: 2022/06/13 04:40:50 by omanar       #
#                                                 #
# *********************************************** #

NAME	=	minishell
RM		=	rm -f
CC		=	gcc -Wall -Wextra -Werror -Iincludes -I libs/libft/includes #-g -fsanitize=address
RLFLG	=	-lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
LIBFT	=	libs/libft/libft.a

SRCS	=	srcs/minishell.c $(LIBFT) \
			srcs/utils/initializer.c srcs/utils/cleaner.c srcs/utils/printer.c \
			srcs/utils/signals.c srcs/utils/error.c \
			srcs/lexer/lexer.c srcs/lexer/tokens.c srcs/lexer/utils.c \
			srcs/parser/parser.c srcs/parser/tokens_handler.c srcs/parser/tokens_utils.c \
			srcs/parser/parser_utils.c srcs/parser/parser_utils2.c srcs/parser/parser_utils3.c \
			srcs/parser/parser_utils4.c srcs/parser/parser_utils5.c srcs/parser/heredoc_handler.c  \
			srcs/builtins/builtins.c srcs/builtins/echo.c srcs/builtins/ft_unset.c  \
			srcs/builtins/ft_export.c srcs/builtins/ft_export2.c srcs/builtins/ft_export3.c \
			srcs/builtins/pwd.c srcs/builtins/env.c srcs/builtins/exit.c srcs/builtins/cd.c \
			srcs/execution/execution.c srcs/execution/execution_utils.c \
			srcs/execution/execution_utils2.c srcs/execution/execution_utils3.c \

define HEADER_M
    __  ___ ____ _   __ ____   _____  __  __ ______ __     __ 
   /  |/  //  _// | / //  _/  / ___/ / / / // ____// /    / / 
  / /|_/ / / / /  |/ / / /    \__ \ / /_/ // __/  / /    / /  
 / /  / /_/ / / /|  /_/ /    ___/ // __  // /___ / /___ / /___
/_/  /_//___//_/ |_//___/   /____//_/ /_//_____//_____//_____/
endef
export HEADER_M

define HEADER_B
    ____  ____  _   ____  _______
   / __ )/ __ \\/ | / / / / / ___/
  / __  / / / /  |/ / / / /\\__ \\ 
 / /_/ / /_/ / /|  / /_/ /___/ / 
/_____/\\____/_/ |_/\\____//____/  
endef
export HEADER_B

all: header_m $(NAME)

header_m:
	@echo "\033[0;32m$$HEADER_M\033[0m\n"

header_b:
	@echo "\033[0;32m$$HEADER_B\033[0m\n"

$(LIBFT):
	@echo "\033[0;36m</ Compiling libft >\033[0m"
	@make -C libs/libft

$(NAME): $(SRCS) $(LIBFT)
	@echo "\033[0;36m</ Compiling Minishell >\033[0m"
	@$(CC) -g $(RLFLG) $(SRCS) -o $(NAME)
	@echo "\033[1;32mMinishell has been compiled!\033[0m\n"

bonus: header_b $(NAME)

clean:
	@make clean -C libs/libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libs/libft
	@echo "\n\033[0;31m</ EVERYTHING HAS BEEN DELETED! >\033[0m\n"

re: fclean all

.PHONY: all clean fclean re header_m
