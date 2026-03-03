CXX = c++

NAME = scop

SRC = srcs/main.cpp \
glad/src/glad.c \
srcs/triangle.cpp \
srcs/shader.cpp \
srcs/mesh.cpp \
srcs/texture.cpp \

OBJECT_DIR = .obj/

# OBJ = $(patsubst %.cpp,$(OBJECT_DIR)%.o,$(SRC))
# OBJ += $(patsubst %.cpp,$(OBJECT_DIR)%.o,$(SRC))
# DEP = $(OBJ:.o=.d)

OBJ = $(SRC:%=$(OBJECT_DIR)%)
OBJ := $(OBJ:.cpp=.o)
OBJ := $(OBJ:.c=.o)

CPPFLAGS = -I./include -I./glad/include/
CXXFLAGS = -MD -MP -g 
LDFLAGS = -L./lib -L./glad/src
LDLIBS = -lglfw -lm -lX11 -lpthread -lXrandr -lXi -ldl

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LDFLAGS) $(LDLIBS)

$(OBJECT_DIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJECT_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	clang $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

-include $(DEP)

clean:
	rm -rf $(OBJECT_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
