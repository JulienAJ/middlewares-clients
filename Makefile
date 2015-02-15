JAVAC=javac
JAVA=java
PHP=php

JAVACLASSPATH=.:/usr/share/java/Ice.jar
PHPFLAGS= -f

all: sliceToAll Client.class

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

# SLICE TO CODE

sliceToAll:sliceToJava sliceToPhp

sliceToJava: server.ice
	slice2java $<

sliceToPhp: server.ice
	slice2php $<

cleanIce: server.php
	rm -f $^
	rm -fr Player

# CLEAN

clean:
	rm -f *.class

mrproper: clean cleanIce
	rm -f CsClient.exe
