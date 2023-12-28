### If you wish to use extra libraries (math.h for instance),
### add their flags here (-lm in our case) in the "LIBS" variable.

LIBS = -lm

###
CFLAGS  = -std=c17
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror
CFLAGS += -Wmissing-declarations
CFLAGS += -DUNITY_SUPPORT_64 -DUNITY_OUTPUT_COLOR

ASANFLAGS  = -fsanitize=address
ASANFLAGS += -fno-common
ASANFLAGS += -fno-omit-frame-pointer

.PHONY: run
run: build
	./sesame.out somePasswordThatIsLong

.PHONY: build
build: ./src/sesame.c ./src/sesame.h
	@echo Compiling $@
	@$(CC) $(ASANFLAGS) $(CFLAGS) ./src/sesame.c ./src/main.c -o sesame.out $(LIBS)
	@echo "Build finished"

.PHONY: test
test: tests.out
	@./tests.out

.PHONY: memcheck
memcheck: ./src/sesame.c ./src/sesame.h ./test-framework/*.h
	@echo Compiling $@
	@$(CC) $(ASANFLAGS) $(CFLAGS) test-framework/unity.c ./src/sesame.c ./src/sesame_test.c -o memcheck.out $(LIBS)
	@./memcheck.out
	@echo "Memory check passed"

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM

tests.out: ./src/sesame.c ./src/sesame.h ./test-framework/*.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) test-framework/unity.c ./src/sesame.c ./src/sesame_test.c -o tests.out $(LIBS)
