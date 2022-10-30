
CC=gcc

CFLAGS= -g -O2
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
	user.cpp object.cpp json.cpp base58.cpp sha256.cpp

CFLAGS += -DHAVE_CURL
SOURCES += rpc_curl.cpp
LDCURL = $(shell /usr/bin/pkg-config --static --libs libcurl)
LDFLAGS += $(LDCURL)

OBJECTS=$(SOURCES:.cpp=.o)
OUTPUT=stratum

CODEDIR1=iniparser

.PHONY: iniparser

all: iniparser  $(SOURCES) $(OUTPUT)

iniparser:
	$(MAKE) -C $(CODEDIR1)

all: $(SOURCES) $(OUTPUT)

$(SOURCES): stratum.h util.h

$(OUTPUT): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDLIBS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(SQLFLAGS) -c $<

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o

install: clean all
	strip -s stratum
	cp stratum /usr/local/bin/
	cp stratum ../bin/

