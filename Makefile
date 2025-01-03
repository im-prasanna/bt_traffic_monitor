default:all

CC=gcc
OUTPUT=bt_traffic_mon
OUTPUT_DIR=./build
SRC_DIR=./src
C_SOURCES=$(shell echo $(SRC_DIR)/*.c)


all:$(C_SOURCES)
	$(CC) $(C_SOURCES) -o $(OUTPUT_DIR)/$(OUTPUT)
clean:
	rm -rf $(OUTPUT_DIR)/*

