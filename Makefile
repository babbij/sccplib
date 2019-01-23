ifndef ZROOT
$(error ZROOT must be set to openabe lib directory)
endif

# include ${ZROOT}/Makefile.common

.PHONY: all

LIBS := -lcrypto -lrelic -lrelic_ec -lopenabe
CXX = g++
CXXFLAGS := -fPIC -pthread -std=c++11 -Wall -g -O2 -DSSL_LIB_INIT -I${ZROOT}/deps/root/include -I${ZROOT}/root/include
LDFLAGS := -L${ZROOT}/deps/root/lib -L${ZROOT}/root/lib

OS := $(shell uname)

ifeq ($(OS),Darwin)
    DLLEXT := dylib
		DLLOPT :=  -dynamiclib
else
    DLLEXT := so
		DLLOPT :=  -shared
endif


all: lib copylib clean

lib: sccp.o
	$(CXX) -o libsccp.$(DLLEXT) $(DLLOPT) $(CXXFLAGS) $(LDFLAGS) sccp.cpp $(LIBS)

copylib:
	cp libsccp.$(DLLEXT) lib/

clean:
	rm -rf *.o *.dSYM *.dylib sccp


