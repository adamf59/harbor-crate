
# compiler: gcc for C, g++ for C++
CC = g++
CCFLAGS = -g -Wall -std=c++17

# build directory
BUILD_DIR = build

# source directory
SOURCE_DIR = src

# all target: just build harbor-crate
all: harbor_crate

# -------------
# Harbor Crate
# -------------

# application executable (harbor-crate)
HARBOR_CRATE_O_LINKS = $(BUILD_DIR)/pretty_print.o $(BUILD_DIR)/create_mode.o $(BUILD_DIR)/mode.o $(BUILD_DIR)/crate_factory.o
harbor_crate: pretty_print.o create_mode.o
	$(CC) $(CCFLAGS) $(SOURCE_DIR)/hbr_crate.cpp -o $(BUILD_DIR)/harbor-crate $(HARBOR_CRATE_O_LINKS)

mode.o:
	$(CC) $(CCFLAGS) -c $(SOURCE_DIR)/modes/mode.cpp -o $(BUILD_DIR)/mode.o

CREATE_MODE_O_LINKS = $(BUILD_DIR)/crate_factory.o
create_mode.o: mode.o pretty_print.o crate_factory.o
	$(CC) $(CCFLAGS) -c $(SOURCE_DIR)/modes/create_mode.cpp -o $(BUILD_DIR)/create_mode.o $(CREATE_MODE_O_LINKS)

crate_factory.o: pretty_print.o
	$(CC) $(CCFLAGS) -c $(SOURCE_DIR)/crate_factory.cpp -o $(BUILD_DIR)/crate_factory.o

# -------------
# PrettyPrint
# -------------

pretty_print.o:
	$(CC) $(CCFLAGS) -c $(SOURCE_DIR)/pretty_print/pretty_print.cpp -o $(BUILD_DIR)/pretty_print.o


# clean target (remove all build files)
.PHONY: clean
clean:
	rm $(BUILD_DIR)/*.o