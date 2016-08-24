CC  = gcc
OUT = msp430emu
CC_OPTIONS = -Wall
SRC_DIR = src
BLD_DIR = build

$(OUT): $(BLD_DIR) $(addprefix $(BLD_DIR)/,opcodes.o mem.o) $(SRC_DIR)/main.c
	$(CC) $(CC_OPTIONS) $(BLD_DIR)/*.o $(SRC_DIR)/main.c -o $(BLD_DIR)/$@
$(BLD_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(CC) $(CC_OPTIONS) -c $(SRC_DIR)/$(notdir $<) -o $(BLD_DIR)/$(notdir $@)
$(BLD_DIR):
	mkdir $(BLD_DIR)
clean:
	rm $(BLD_DIR)/*.o $(BLD_DIR)/$(OUT)
	rm -r $(BLD_DIR)

