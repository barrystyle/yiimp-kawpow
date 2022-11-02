
CC=gcc

CFLAGS= -g -O2 -I./
SQLFLAGS= `mysql_config --cflags --libs`

# Comment this line to disable address check on login,
# if you use the auto exchange feature...
CFLAGS += -DNO_EXCHANGE

#CFLAGS=-c -O2 -I /usr/include/mysql
LDFLAGS=-O2 `mysql_config --libs`

LDLIBS=iniparser/libiniparser.a -lpthread -lm -lstdc++
LDLIBS+=-lmysqlclient

SOURCES=stratum.cpp db.cpp coind.cpp coind_aux.cpp coind_template.cpp coind_submit.cpp util.cpp list.cpp \
	rpc.cpp job.cpp job_send.cpp job_core.cpp merkle.cpp share.cpp socket.cpp coinbase.cpp \
	client.cpp client_submit.cpp client_core.cpp client_difficulty.cpp remote.cpp remote_template.cpp \
	user.cpp object.cpp json.cpp base58.cpp sha256.cpp uint256.cpp utilstrencodings.cpp \
	\
	kawpow/lib/keccak/keccak.c kawpow/lib/keccak/keccakf800.c kawpow/lib/keccak/keccakf1600.c kawpow/lib/ethash/primes.c \
	kawpow/lib/ethash/ethash.cpp kawpow/lib/ethash/progpow.cpp kawpow/hash.cpp

CFLAGS += -DHAVE_CURL
SOURCES += rpc_curl.cpp
LDCURL = $(shell /usr/bin/pkg-config --static --libs libcurl)
LDFLAGS += $(LDCURL)

OBJECTS=$(SOURCES:.cpp=.o)
OUTPUT=stratum

CODEDIR0=preclean
CODEDIR1=iniparser

.PHONY: preclean iniparser

all: preclean iniparser $(SOURCES) $(OUTPUT)

preclean:
	rm -f stratum
	rm -rf *.*o
	rm -rf */*.*o
	rm -rf */*.a

iniparser:
	$(MAKE) -C $(CODEDIR1)

all: $(SOURCES) $(OUTPUT)

$(SOURCES): stratum.h util.h

$(OUTPUT): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDLIBS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(SQLFLAGS) -c $< -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:  preclean

install: clean all
	strip -s stratum
	cp stratum /usr/local/bin/
	cp stratum ../bin/

