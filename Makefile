CPP=g++
JAVAC=javac
JAVA=java
CS=gmcs
EXCS=mono
PHP=php

CPPFLAGS= -I. -lIce -lIceUtil -pthread
JAVACLASSPATH=.:/usr/share/java/Ice.jar
PHPFLAGS= -f
CSREQUIRED=/usr/lib/mono/Ice/Ice.dll

all: sliceToAll Client.class Server CsClient.exe

# JAVA CLIENT

Client.class: Client.java
	$(JAVAC) -classpath $(JAVACLASSPATH) $^ Player/*.java

runClient:
	$(JAVA) -classpath $(JAVACLASSPATH) Client

# PHP CLIENT

runPhpClient:
	 $(PHP) $(PHPFLAGS) client.php

# CS CLIENT

CsClient.exe: client.cs
	$(CS) -r:$(CSREQUIRED) $^ server.cs -out:$@

runCsClient:
	$(EXCS) CsClient.exe

# SERVER

Server: main.o server.o songDB.o
	$(CPP) $^ -o $@ $(CPPFLAGS)

main.o: main.cpp
	$(CPP) -c $< -o $@ $(CPPFLAGS)

server.o: server.cpp server.h
	$(CPP) -c $< -o $@ $(CPPFLAGS)

songDB.o: songDB.cpp songDB.hpp
	$(CPP) -c $< -o $@ $(CPPFLAGS)

runServer:
	./Server

# SLICE TO CODE

sliceToAll: sliceToCpp sliceToCs sliceToJava sliceToPhp

sliceToCpp: server.ice
	slice2cpp $<

sliceToCs: server.ice
	slice2cs $<

sliceToJava: server.ice
	slice2java $<

sliceToPhp: server.ice
	slice2php $<

cleanIce: server.h server.cpp server.cs server.php
	rm -f $^
	rm -fr Player

# CLEAN

clean:
	rm -f *.o

mrproper: clean cleanIce
	rm -f Server Client.class CsClient.exe
