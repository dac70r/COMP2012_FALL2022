CPPFLAGS = -std=c++11 -Wall
CPPFLAGS_leak = -std=c++11 -fsanitize=address,leak,undefined -g

OBJ_DIR = obj
OBJ_DIR_leak = obj_leak

SRCS	= main.cpp container.cpp button.cpp textbox.cpp object.cpp
OBJS	= $(SRCS:.cpp=.o)
DEPS	= $(OBJS:.o=.d)

OBJECTS = $(addprefix $(OBJ_DIR)/,$(OBJS))
OBJECTS_leak = $(addprefix $(OBJ_DIR_leak)/,$(OBJS))

all: create_directory lab4.out lab4_leak.out

create_directory:
	mkdir -p $(OBJ_DIR) $(OBJ_DIR_leak)

lab4.out: $(OBJECTS) 
	g++ $(CPPFLAGS) -o $@ $^

lab4_leak.out: $(OBJECTS_leak)
	g++ -o $@ $(CPPFLAGS_leak) $^

# To include the .d dependency files
-include $(DEPS)

$(OBJ_DIR)/%.o: %.cpp
	g++ $(CPPFLAGS) -MMD -MP -c $< -o $@

$(OBJ_DIR_leak)/%.o: %.cpp
	g++ $(CPPFLAGS_leak) -MMD -MP -c $< -o $@

clean:;
	# del $(OBJ_DIR)/* $(OBJ_DIR_leak)/* *.exe
	rm -rf $(OBJ_DIR)/* $(OBJ_DIR_leak)/* *.exe