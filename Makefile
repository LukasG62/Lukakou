
# Programs to build
PROG=lukac
# Test programs to build
TEST_PROG=
# Path to bin directory
BIN_DIR=bin
# Programs path
PROG_PATH=$(addprefix $(BIN_DIR)/, $(PROG))
# Path to source codes
SRC_DIR=src
# Path to header files
INCLUDE_DIR=include
# Path to obj files 
OBJ_DIR=obj
# Path to lib files
LIB_DIR=lib

# Compilation flags
CPFLAGS ?=-I$(INCLUDE_DIR) -Wall -g -DDEBUG
# Linker flags
LD_FLAGS ?=-L$(LIB_DIR) -lcompiler
# Compiler
CC?=gcc


# Default target
.PHONY: all clean docs

all: docs $(PROG_PATH)
	@echo "Build successful."
	@echo "Run $(PROG_PATH) to execute the program."

clean:
	@echo "Cleaning up ..."
	@rm -f $(OBJ_DIR)/*.o $(LIB_DIR)/*.a $(BIN_DIR)/*

docs:
	@echo "Generating documentation ..."
	@doxygen Doxyfile

# Rule for building libcompiler.a
$(LIB_DIR)/libcompiler.a: $(OBJ_DIR)/lexer.o $(OBJ_DIR)/parser.o $(OBJ_DIR)/ast.o
	@mkdir -p $(LIB_DIR)
	@echo "AR\t$@"
	@ar rcs $@ $^

# Rule for building compiler
$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(LIB_DIR)/libcompiler.a
	@mkdir -p $(BIN_DIR)
	@echo "LD\t$<"
	@$(CC) $(CPFLAGS) $< -o $@ $(LD_FLAGS)

$(OBJ_DIR)/lukac.o: $(SRC_DIR)/lukac.c $(INCLUDE_DIR)/common.h
	@mkdir -p $(OBJ_DIR)
	@echo "CC\t$<"
	@$(CC) $(CPFLAGS) -c $< -o $@

# Rule for building object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/%.h $(INCLUDE_DIR)/common.h
	@mkdir -p $(OBJ_DIR)
	@echo "CC\t$<"
	@$(CC) $(CPFLAGS) -c $< -o $@
