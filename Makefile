# ══════════════════════════════════ Config Makefile ═══════════════════════════════════
# ───────────────────────────────────── Variables ──────────────────────────────────────

NAME			= cub3D
CC				= cc
CFLAGS			= -Wall -Wextra -Werror $(GLFW_INC)
MLX42_PATH		= minilibx
LIBFT_PATH		= libft
MLX42			= $(MLX42_PATH)/build/libmlx42.a
LIBFT			= $(LIBFT_PATH)/libft.a
RM				= rm -f
CLONE 			= git submodule init && git submodule update

# ────────────────────────────────────── Couleurs ──────────────────────────────────────

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
NC = \033[0m

# ──────────────────────────────────── Detection Os ────────────────────────────────────

UNAME := $(shell uname)
ARCH := $(shell uname -m)

# Configuration pour MacOS
ifeq ($(UNAME), Darwin)
	ifeq ($(ARCH), arm64)
		GLFW_FLAGS = -lglfw -L"/opt/homebrew/lib/"
		GLFW_INC = -I"/opt/homebrew/include"
		OS_MSG = "MacOS ARM"
	else
		GLFW_FLAGS = -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
		GLFW_INC = -I"/Users/$(USER)/.brew/opt/glfw/include"
		OS_MSG = "MacOS Intel"
	endif
	FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit
else
	GLFW_FLAGS = -ldl -lglfw -pthread -lm
	GLFW_INC =
	FRAMEWORK =
	OS_MSG = "Linux"
endif

# ────────────────────────────────────── Sources ───────────────────────────────────────

SRCS = 	src/main.c \
		src/errors/errors.c \
		src/parsing/map_parser.c \
		src/parsing/read_map.c \
		src/parsing/parser_utils.c \
		src/render/utils/cleanup.c \
		src/render/utils/utils.c \

OBJS = $(SRCS:.c=.o)

# ──────────────────────────────────── Progress Bar ────────────────────────────────────

TOTAL_FILES := $(words $(SRCS))
CURRENT_FILE := 0
PROGRESS_WIDTH := 40

define update_progress
	$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	$(eval PERCENTAGE=$(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))))
	$(eval PROGRESS=$(shell echo $$(($(CURRENT_FILE) * $(PROGRESS_WIDTH) / $(TOTAL_FILES)))))
	printf "\r$(BLUE)[%3d%%] $(GREEN)Building %-50s$(NC)" $(PERCENTAGE) "$1"
endef

# ─────────────────────────────────────── Phony ────────────────────────────────────────

.PHONY:		all clean fclean re


# ═════════════════════════════════ Regles Principales ═════════════════════════════════

all:			$(LIBFT) $(MLX42) $(NAME)

$(LIBFT):
			@printf "$(BLUE)[  0%%] $(GREEN)Building libft...$(NC)\n"
			@make -C $(LIBFT_PATH)
			@printf "$(BLUE)[100%%] $(GREEN)Libft built successfully$(NC)\n"

$(MLX42):
			@echo "$(YELLOW)Cloning MLX42 submodule...$(NC)"
			$(CLONE)
			@printf "$(BLUE)[  0%%] $(GREEN)Building MLX42...$(NC)\n"
			@cmake $(MLX42_PATH) -B $(MLX42_PATH)/build
			@make -C $(MLX42_PATH)/build
			@printf "$(BLUE)[100%%] $(GREEN)MLX42 built successfully$(NC)\n"

$(NAME): $(OBJS)
			$(CC) $(OBJS) $(MLX42) -L$(LIBFT_PATH) -lft $(GLFW_FLAGS) $(FRAMEWORK) -o $(NAME)
			@printf "$(BLUE)[100%%] $(GREEN)$(NAME) is compiled !! $(NC)\n"
			@echo $(HEADER)

%.o: %.c
			@$(call update_progress,$<)
			@$(CC) $(CFLAGS) -I$(MLX42_PATH)/include -I$(LIBFT_PATH) -c $< -o $@
			@printf "\n"

# ─────────────────────────────────────── Clean ────────────────────────────────────────

clean:
			@echo "$(YELLOW)Cleaning object files...$(NC)"
			@make -C $(LIBFT_PATH) clean
			@rm -rf $(MLX42_PATH)/build
			@rm -f $(OBJS)
			@echo "$(GREEN)Object files cleaned!$(NC)"

fclean:		clean
			@echo "$(YELLOW)Cleaning all files...$(NC)"
			@make -C $(LIBFT_PATH) fclean
			@rm -f $(NAME)
			@echo "$(GREEN)All files cleaned!$(NC)"

# ────────────────────────────────────── Rebuild ───────────────────────────────────────

re:			fclean all
			@echo "$(GREEN)>>> Cleaned and rebuilt everything! <<<$(DEF_COLOR)"

# ───────────────────────────────────── Norminette ─────────────────────────────────────

norminette:
	@norminette | grep -Ev '^Notice:|OK!$$'					\
	&& $(ECHO) -e "$(COL_RED)Norminette KO !$(COL_RESET)"	\
	|| $(ECHO) -e "$(COL_GREEN)Norminette OK !$(COL_RESET)"
