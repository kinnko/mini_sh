NAME =		minishell
CC =		cc
CFLAGS =	-Wall -Wextra -Werror -g3
LIB = -lreadline

SRC_DIR =	srcs/
SRC =		check_pipe_syntax.c \
			check_syntax.c \
			cmd_cd.c \
			cmd_echo.c \
			cmd_env.c \
			cmd_exit.c \
			cmd_export.c \
			cmd_pwd.c \
			cmd_unset.c \
			execute.c \
			execute_builtin.c \
			expand_var.c \
			init.c \
			libft_ex.c \
			main.c \
			pipe.c \
			redirect.c \
			redirect_add_to.c \
			redirect_from.c \
			redirect_here_docs.c \
			redirect_to.c \
			run_path_env_executable.c \
			strs.c \
			utils.c \
			utils2.c \
			signal.c \
			error_utils.c \
			envp.c \
			envp2.c \
			key_value.c \
			ft_split_ex.c \
			ft_split_utils.c \
			judge_redirects.c \
			parse_quote.c \
			check_quart_syntax.c \
			cd_absolute_path.c

OBJ_DIR =	objs/
OBJ =		$(SRC:%.c=$(OBJ_DIR)%.o) libft/libft.a

ifeq ($(shell uname), Linux)
	LIB += -lbsd
endif

ifeq ($(shell uname), Darwin)
	CFLAGS += -I $(shell brew --prefix readline)/include
	LIB += -L$(shell brew --prefix readline)/lib
endif

INCLUDE = -I includes -I libft

all: do_libft $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE)  -o $(NAME) $(OBJ) $(LIB)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

do_libft:
	make -C libft bonus

clean:
	rm -rf $(OBJ_DIR)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

nm: all
	nm -u $(NAME) | grep -v -e readline -e rl_clear_history -e rl_on_new_line, -e rl_replace_line -e rl_redisplay -e add_history -e printf -e malloc -e free -e write -e access -e open -e read -e close -e fork -e wait -e waitpid -e wait3 -e wait4 -e signal -e sigaction -e sigemptyset -e sigaddset -e kill -e exit -e getcwd -e chdir -e stat -e lstat -e fstat -e unlink -e execve -e dup -e dup2 -e pipe -e opendir -e readdir -e closedir -e strerror -e perror -e isatty -e ttyname -e ttyslot -e ioctl -e getenv -e tcsetattr -e tcgetattr -e tgetent -e tgetflag -e tgetnum -e tgetstr -e tgoto -e tputs | grep -E "^_" -v

.PHONY: all clean fclean re

input: input.c
	cc input.c -o input

norm:
	norminette srcs/*.c includes/*.h libft/*.c libft/*.h

norg:
	norminette srcs/*.c includes/*.h libft/*.c libft/*.h | grep -v OK
