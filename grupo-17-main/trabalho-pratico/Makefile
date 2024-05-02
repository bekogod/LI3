CC          = gcc
PKG         = `pkg-config --cflags --libs glib-2.0`
BLD_DIR     = build
SRC_DIR     = src
TEST_DIR    = test
RES_DIR     = Resultados
INC_DIR     = include

SRC_FILES       = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES      = $(wildcard $(TEST_DIR)/*.c)

OBJS            = $(patsubst $(SRC_DIR)/%.c,$(BLD_DIR)/%.o,$(SRC_FILES))
TEST_OBJS       = $(patsubst $(TEST_DIR)/%.c,$(BLD_DIR)/%.o,$(TEST_FILES))

PROG            = programa-principal
PROG_TESTES     = programa-testes

vpath %.c $(SRC_DIR) $(TEST_DIR)

.DEFAULT_GOAL = build

$(BLD_DIR)/%.o: %.c
	$(CC) -g -c -I $(INC_DIR) $^ $(PKG) -o $@ #-Wall -std=c99

$(PROG): $(OBJS) $(BLD_DIR)/main.o
	$(CC) -g -I $(INC_DIR) $^ $(PKG) -o $@ -lpthread -O2 -Wall -std=c99

$(PROG_TESTES): $(filter-out $(BLD_DIR)/main.o, $(OBJS)) $(TEST_OBJS)
	$(CC) -g -I $(INC_DIR) $^ $(PKG) -o $@ -lpthread -O2 -Wall -std=c99

setup:
	@mkdir -p $(BLD_DIR)
	@mkdir -p $(SRC_DIR)
	@mkdir -p $(TEST_DIR)
	@mkdir -p $(INC_DIR)

.PHONY:b, build
b build: setup $(PROG) $(PROG_TESTES)

.PHONY:c, clean
c clean:
	@rm -r $(BLD_DIR) $(PROG) $(PROG_TESTES) $(RES_DIR)/*.csv $(RES_DIR)/*.txt
