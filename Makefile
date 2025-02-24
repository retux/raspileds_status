## VARS DE ENTORNO
CC = g++
CXXFLAGS := -Wall -lgpiodcxx 
#CXXFLAGS := -I/usr/include/cryptopp -I/usr/include/crypto++ -Wall
LDFLAGS := 
#LDFLAGS := -L/usr/lib -lcryptopp -lpthread
### EOF VARS ENTORNO

# OBJECT FILES DEFS.
netifledwatch_objects = netifledwatch.o 
#gpiopinctrl_objects = GPIOClass.o gpiopinctrl.o 
#gpioctrl_objects = GPIOClass.o gpioctrl.o

# TARGETS
all: netifledwatch 

netifledwatch: $(netifledwatch_objects)
	$(CC) -o netifledwatch $(netifledwatch_objects) $(CXXFLAGS) $(LDFLAGS) 

clean:
	rm -f *.o
