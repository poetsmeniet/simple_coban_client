NAME = simple_coban_client

CODE_FILES = main.c config.c gpsTools.c

DOC_FILES = docs
DEBUG = YES
ifeq ($(DEBUG),YES)
	D = -g
else
	D =
endif

.PHONY: all clean docs

all: $(CODE_FILES)
	gcc -lm -Wno-parentheses -Wextra -fsanitize=undefined -Wall $D -o $(NAME) $(CODE_FILES)

#docs: Doxyfile
#	doxygen Doxyfile

#Doxyfile:
#	doxygen -g

clean:
	rm -rf $(NAME) $(DOC_FILES) *.o
