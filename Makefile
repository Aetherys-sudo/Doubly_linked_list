CFLAGS = -O2 -g -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
DLIBS = -ldl $(OPTLIBS)
PREFIX ?= /usr/local

SOURCES = $(wildcard src/**/*.c src/*.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

TEST_SRC = $(wildcard tests/*_tests.c)
TESTS = $(patsubst %.c, %, $(TEST_SRC))

TARGET = build/mylib.a
SO_TARGET = $(patsubst %.a, %.so, $(TARGET))

all: $(TARGET) $(SO_TARGET) tests

dev: CFLAGS = -g -O0 -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@
	
$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

#------------UNIT TESTS---------
.PHONY: tests
tests: LDLIBS += -ldl $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

#-----------CLEANER------------
clean:
	rm -rf build $(OBJECTS) $(TESTS) 
	rm -f tests/tests.log
	find . -name "*.gc" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

#----------INSTALLER------------
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/
	
#----------THE CHECKER-----------

check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9] (str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true

