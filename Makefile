## VARS DE ENTORNO
CC = g++
CXXFLAGS := -Wall
#CXXFLAGS := -I/usr/include/cryptopp -I/usr/include/crypto++ -Wall
LDFLAGS :=
#LDFLAGS := -L/usr/lib -lcryptopp -lpthread
### EOF VARS ENTORNO

# OBJECT FILES DEFS.
netifledwatch_objects = GPIOClass.o netifledwatch.o 
testmainbundle_objects = GPIOClass.o testmainbundle.o 
gpiopinctrl_objects = GPIOClass.o gpiopinctrl.o 
gpioctrl_objects = GPIOClass.o gpioctrl.o

# TARGETS
all: netifledwatch gpiopinctrl gpioctrl

netifledwatch: $(netifledwatch_objects)
	$(CC) $(CXXFLAGS) $(LDFLAGS) -o netifledwatch $(netifledwatch_objects) 

gpiopinctrl: $(gpiopinctrl_objects)
	$(CC) $(CXXFLAGS) $(LDFLAGS) -o gpiopinctrl $(gpiopinctrl_objects) 

gpioctrl: $(gpioctrl_objects)
	$(CC) $(CXXFLAGS) $(LDFLAGS) -o gpioctrl $(gpioctrl_objects) 

testmainbundle: $(testmainbundle_objects)
	$(CC) $(CXXFLAGS) $(LDFLAGS) -o testmainbundle $(testmainbundle_objects) 



clean:
	rm -f *.o
