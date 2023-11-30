PROJ := projection

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Werror

SRC_FILES := $(shell find ./src -name "*.cpp")
OBJ_FILES := $(SRC_FILES:./src/%.cpp=./obj/%.o)

# create the obj folder
.PHONY: create_obj_dir
create_obj_dir:
	mkdir -p obj

# compile the obj files
$(OBJ_FILES): ./obj/%.o : ./src/%.cpp | create_obj_dir
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# build the program
$(PROJ): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: all
all: $(PROJ)

.PHONY: clean
clean:
	rm -rf obj $(PROJ)

.PHONY: run
run: $(PROJ)
	./$(PROJ)






