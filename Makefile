
#set name of the executable file
target = test.out

#set directories
build_dir = /home/kirill/docs/projects/itmo/dev_days/REPL-for-cpp
src_dir = /home/kirill/docs/projects/itmo/dev_days/REPL-for-cpp

cc = clang
cxx = clang++
cxx_version = -std=c++20
cppflags = -Wall -Wextra -Werror -Wextra-semi \
		   -Wno-self-assign-overloaded -Wno-self-assign-overloaded -Wvla-extension \
           -g -v -O0 \
           -fsanitize=address -fno-omit-frame-pointer -fno-operator-names
sources = $(shell find $(src_dir) -name *.cpp -or -name *.c)
deps = $(shell find $(src_dir) -name *.hpp -or -name *.h)
objects := $(patsubst %c, $(src_dir)/%o, $(patsubst %pp, %, $(notdir $(sources))))
$(info $$objects are [${objects}])

executable = $(build_dir)/$(target)

all: $(executable)

$(executable): $(objects)
	$(cxx) $(cppflags) $(objects) -o $@

$(build_dir)/%.o: %.c
	$(cc) -c $< -o $@

$(build_dir)/%.o: %.cpp
	$(cxx) $(cxx_version) $(cppflags) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(build_dir)/*.o $(build_dir)/*.out