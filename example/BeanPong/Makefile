#
# CoffeeBean Makefile for GNU Make
#

### Game name
GAME_NAME := BeanPong

### Compiler
CC := g++

### File Extensions
o := o

### Directories
source := src
obj := obj
thirdparty_dir := ../../thirdparty

### Detect platform

ifndef HOSTPLATFORM
	HOSTPLATFORM := UNKNOWN
	ifeq ($(findstring Windows,$(OS)),Windows)
		HOSTPLATFORM := WINDOWS
	else
		uname := $(strip $(shell uname -s))
		ifeq ($(findstring Linux,$(uname)),Linux)
			HOSTPLATFORM := LINUX
		else ifeq ($(findstring BSD,$(uname)),BSD)
			HOSTPLATFORM := BSD
		else ifeq ($(findstring MINGW,$(uname)),MINGW)
			HOSTPLATFORM := WINDOWS
		else ifeq ($(findstring MSYS,$(uname)),MSYS)
			HOSTPLATFORM := WINDOWS
		else ifeq ($(findstring Darwin,$(uname)),Darwin)
			HOSTPLATFORM := DARWIN
		else ifeq ($(findstring BeOS,$(uname)),BeOS)
			HOSTPLATFORM := BEOS
		else ifeq ($(findstring skyos,$(uname)),skyos)
			HOSTPLATFORM := SKYOS
		else ifeq ($(findstring QNX,$(uname)),QNX)
			HOSTPLATFORM := QNX
		else ifeq ($(findstring SunOS,$(uname)),SunOS)
			HOSTPLATFORM := SUNOS
		else ifeq ($(findstring syllable,$(uname)),syllable)
			HOSTPLATFORM := SYLLABLE
		endif
	endif
endif
ifndef PLATFORM
	PLATFORM := $(HOSTPLATFORM)
endif



##### External Library Definitions

### SDL2

sdl := SDL2

sdl_root := $(thirdparty_dir)/$(sdl)
sdl_inc := $(sdl_root)/include
sdl_src := $(sdl_root)/src

sdl_cflags := \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer \

### SDL2_ttf

sdl_ttf := SDL2_ttf

sdl_ttf_root := $(thirdparty_dir)/$(sdl_ttf)
sdl_ttf_inc := $(sdl_ttf_root)
sdl_ttf_src := $(sdl_ttf_root)

### Xoshiro

xoshiro := Xoshiro

xoshiro_root := $(thirdparty_dir)/$(xoshiro)
xoshiro_inc := $(xoshiro_root)

#### CoffeeBean

engine := CoffeeBean

engine_root := ../..
engine_src := $(engine_root)/src
engine_comp_src := $(engine_src)/Components
engine_type_src := $(engine_src)/Types
engine_inc := $(engine_root)/include
engine_obj := $(obj)/$(engine)
engine_src_files := $(wildcard $(engine_src)/*.cpp) 
engine_src_files += $(wildcard $(engine_comp_src)/*.cpp)
engine_obj_files := $(addprefix $(engine_obj)/, $(notdir $(engine_src_files:.cpp=.o)))

engine_cflags := \
	-I$(engine_inc) \
	-I$(xoshiro_inc) \
	-I$(engine_src) \


#### BeanPong (Test Game)

#beanpong := BeanPong

#beanpong_root := .
#beanpong_src := ./src
#beanpong_inc := $(beanpong_root)/include
#beanpong_obj := $(obj)/$(beanpong)
#beanpong_src_files := $(wildcard $(beanpong_src)/*.cpp)
#beanpong_obj_files := $(addprefix $(beanpong_obj)/, $(notdir $(beanpong_src_files:.cpp=.o)))

### Game

game_root := .
game_src := $(game_root)/src
game_inc := $(game_root)/src
game_obj := $(obj)/$(GAME_NAME)
game_src_files := $(wildcard $(game_src)/*.cpp)
game_obj_files := $(addprefix $(game_obj)/, $(notdir $(game_src_files:.cpp=.o)))

#### Final setup
	COMPILERFLAGS += \
	-w -std=c++20 -Wfatal-errors \
	$(engine_cflags) \
#	-I$(sdl_inc) \
#	-I$(sdl_ttf_inc) \
#	$(sdl_ttf_src)/*.c \

ifeq ($(PLATFORM),WINDOWS)
	COMPILERFLAGS += -lmingw32 -lSDL2main 
endif

COMPILERFLAGS += $(sdl_cflags) \

#### Targets

all: $(GAME_NAME)

#beanpong: $(engine_obj_files) $(beanpong_obj_files)
#	$(CC) \
#	$(engine_obj)/*.o \
#	$(beanpong_obj)/*.o \
#	$(COMPILERFLAGS) \
#	-o beanpong.exe \

$(GAME_NAME) : $(engine_obj_files) $(game_obj_files)
	$(CC) \
	$(engine_obj)/*.o \
	$(game_obj)/*.o \
	$(COMPILERFLAGS) \
	-o $(GAME_NAME) \

clean:
	rm -rf $(obj)/*
	rm ./$(GAME_NAME);

run:
	./$(GAME_NAME);

%.o: %.cpp
	$(CC) $(COMPILERFLAGS) -c $< -o $@

#$(obj)/%.o: $(src)/%.cpp
#	$(CC) $(COMPILERFLAGS) -c $< -o $@

$(engine_obj)/%.o: $(engine_src)/%.cpp
	mkdir -p $(engine_obj)
	$(CC) $(COMPILERFLAGS) -c $< -o $@

$(engine_obj)/%.o: $(engine_comp_src)/%.cpp
	mkdir -p $(engine_obj)
	$(CC) $(COMPILERFLAGS) -c $< -o $@

$(game_obj)/%.o: $(game_src)/%.cpp
	mkdir -p $(game_obj)
	$(CC) $(COMPILERFLAGS) -c $< -o $@
