############### COLOR ################

_END		= 	\e[0m
_BOLD		= 	\e[1m
_UNDER		= 	\e[4m
_BACK		= 	\033[2K\r

_GREY		= 	\e[30m
_RED		= 	\e[31m
_GREEN		= 	\e[32m
_YELLOW		= 	\e[33m
_BLUE		= 	\e[34m
_PURPLE		= 	\e[35m
_CYAN		= 	\e[36m
_WHITE		= 	\e[37m

_IGREY		= 	\e[40m
_IRED		= 	\e[41m
_IGREEN		= 	\e[42m
_IYELLOW	= 	\e[43m
_IBLUE		=	\e[44m
_IPURPLE	=	\e[45m
_ICYAN		=	\e[46m
_IWHITE		=	\e[47m

############# BASIC INFO ##############

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
NAME		=	libfge.a
LIBPRINTF	=	fge

FILES		= 	convert/decimal2e \
				convert/decimal2f \
				convert/f2fb \
				convert/fb2struct \
				conver/struct2decimal \
				print_including_spaces \
				print_specifier \
				printf_fge \
				set_conversion_info \
				utils

DIR_SRCS	=	srcs/
DIR_HDRS	=	includes/

SRCS		=	$(addprefix $(DIR_SRCS), $(addsuffix .c, $(FILES)))
OBJS		=	$(addprefix $(DIR_SRCS), $(addsuffix .o, $(FILES)))

############## COMMANDS ###############

all: $(NAME)

$(NAME): $(OBJS)
	@printf "Creating static library $(_GREEN)$(NAME)$(_END)\n"
	@ar rcs $(NAME) $(OBJS)
	@printf "$(_IWHITE)$(_BLUE)$(_BOLD)Created $(NAME) $(_END)\n"

%.o: %.c
	@printf "Compiling $(_GREEN)$@$(_END)\n"
	@$(CC) $(CFLAGS) -I$(DIR_HDRS) -c $< -o $@

clean:
	@printf "Removing $(_RED)object files$(_END)\n"
	@rm -f $(OBJS)
	@rm -f main.o test

fclean: clean
	@printf "Removing $(_RED)$(NAME)$(_END)\n"
	@rm -f $(NAME)

re: fclean all

test: $(NAME)
	$(CC) -I$(DIR_HDRS) -c main.c
	$(CC) main.o -L. -l$(LIBPRINTF) -o test

.PHONY: all clean fclean re