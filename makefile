### If you wish to use extra libraries (math.h for instance),
### On mac install curl and openssl with homebrew. 
### On Linux use: -lm -lcurl -lssl -lcrypto.

LIBS = -lm -lcurl -lssl -lcrypto -I/opt/homebrew/Cellar/openssl@3/3.2.0_1/include -L/opt/homebrew/Cellar/openssl@3/3.2.0_1/lib

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

VENDOR = vendor/log.c/src/log.c
VENDOR += vendor/ht/src/ht.c

.PHONY: run
run: build
	./sesame.out somePasswordThatIsLong

.PHONY: build
build: ./src/sesame.c ./src/sesame.h
	@echo Compiling $@
	@$(CC) $(ASANFLAGS) $(CFLAGS) $(VENDOR) ./src/sesame.c ./src/main.c -o sesame.out $(LIBS)
	@echo "Build finished"

.PHONY: release
release:
	@echo Compiling $@
	@$(CC) $(ASANFLAGS) $(CFLAGS) $(VENDOR) ./src/sesame.c ./src/main.c -o sesame $(LIBS)
	@echo "Build finished"

.PHONY: test
test: tests.out
	@./tests.out

.PHONY: memcheck
memcheck:
	@echo Compiling $@
	@$(CC) $(ASANFLAGS) $(CFLAGS) test-framework/unity.c $(VENDOR) ./src/sesame.c ./src/sesame_test.c -o memcheck.out $(LIBS)
	@./memcheck.out
	@echo "Memory check passed"

.PHONY: clean
clean:
	rm -rf *.o *.out *.out.dSYM

tests.out: ./src/sesame.c ./src/sesame.h ./test-framework/*.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) test-framework/unity.c $(VANDOR) ./src/sesame.c ./src/sesame_test.c -o tests.out $(LIBS)
