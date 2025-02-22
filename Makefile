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
all: netifledwatch gpiopinctrl gpioctrl

netifledwatch: $(netifledwatch_objects)
	#$(CC) $(CXXFLAGS) $(LDFLAGS) -o netifledwatch $(netifledwatch_objects) 
	$(CC) -o netifledwatch $(netifledwatch_objects) $(CXXFLAGS) $(LDFLAGS) 

gpiopinctrl: $(gpiopinctrl_objects)
	$(CC) $(CXXFLAGS) $(LDFLAGS) -o gpiopinctrl $(gpiopinctrl_objects) 

gpioctrl: $(gpioctrl_objects)
	$(CC) $(CXXFLAGS) $(LDFLAGS) -o gpioctrl $(gpioctrl_objects) 

testmainbundle: $(testmainbundle_objects)
	$(CC) $(CXXFLAGS) $(LDFLAGS) -o testmainbundle $(testmainbundle_objects) 



clean:
	rm -f *.o
