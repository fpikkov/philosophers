# --------	MAKE VARIABLES	--------
RED = \033[1;31m
GREEN = \033[1;32m
CYAN = \033[1;36m
CLEAR = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror
DBG_FLAGS = -fdiagnostics-color=always -g -DDEBUG=1
INC_FLAGS = -I$(INCLUDE_DIR)
P_FLAG = -pthread

BUILD_DIR = ./build
INCLUDE_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj

NAME = philo

BUILD = ${BUILD_DIR}/${NAME}
DBG_BUILD = ${BUILD_DIR}/debug

SRCS =	${SRC_DIR}/main.c \
		${SRC_DIR}/parser.c \
		${SRC_DIR}/threads.c \
		${SRC_DIR}/error.c \
		${SRC_DIR}/utils.c \
		${SRC_DIR}/logging.c \
		${SRC_DIR}/routine.c \
		${SRC_DIR}/routine_monitor.c \
		${SRC_DIR}/routine_philo.c \
		${SRC_DIR}/time.c

OBJS = ${patsubst ${SRC_DIR}/%.c,${OBJ_DIR}/%.o,${SRCS}}

# --------	MAKE TARGETS	--------
all: ${BUILD}

${BUILD}: ${OBJS}
	@echo "${GREEN}Generating build...${CLEAR}"
	@mkdir -p ${BUILD_DIR}
	${CC} ${CFLAGS} ${P_FLAG} -o $@ $^

${OBJ_DIR}/%.o : ${SRC_DIR}/%.c
	@echo "${CYAN}Generating object files...${CLEAR}"
	@mkdir -p ${OBJ_DIR}
	@$(CC) $(CFLAGS) -c $< -o $@ ${INC_FLAGS}

debug: CFLAGS = ${DBG_FLAGS}
debug: ${DBG_BUILD}

${DBG_BUILD}: ${OBJS}
	@echo "${GREEN}Generating debug build...${CLEAR}"
	@mkdir -p ${BUILD_DIR}
	@$(CC) $(DBG_FLAGS) $(P_FLAG) -o $@ $^

clean:
	@echo "${RED}Cleaning object files...${CLEAR}"
	@rm -rf ${OBJ_DIR}

fclean: clean
	@echo "${RED}Fully cleaning project...${CLEAR}"
	@rm -rf ${BUILD_DIR}

re: fclean all

.PHONY: all re clean fclean debug
