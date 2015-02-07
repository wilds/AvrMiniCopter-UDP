CXX=g++
CXX_OPTS= -Wall -g -O2 -DDEBUG1
CXXFLAGS=$(CXX_OPTS)

CC=cc
CFLAGS=
CC_OPTS=-lstdc++ -lm
LDFLAGS=-lrt

INSTALL=install

OBJ_UDPCONTROLLER=udpcontroller.o routines.o udpconfig.o

%.o: %.c                                                                         
	$(CXX) -c $(CXXFLAGS) $(CXX_OPTS) $< -o $@ 

all: udpcontroller 

udpcontroller: $(OBJ_UDPCONTROLLER)
	$(CC) $(CFLAGS) $(OBJ_UDPCONTROLLER) -o udpcontroller $(LDFLAGS) $(CC_OPTS) 

install:
	$(INSTALL) -m 0755 -d $(DESTDIR)/var/www/addons
	$(INSTALL) -m 755 utils/www/* $(DESTDIR)/var/www/addons/
	$(INSTALL) -m 0755 -d $(DESTDIR)/usr/local/bin
	$(INSTALL) -m 755 udpcontroller $(DESTDIR)/usr/local/bin/
	$(INSTALL) -m 755 utils/udpcontroller.sh $(DESTDIR)/usr/local/bin/
	$(INSTALL) -m 755 utils/camera.sh $(DESTDIR)/usr/local/bin/
	$(INSTALL) -m 755 utils/camera_streamer.sh $(DESTDIR)/usr/local/bin/
	$(INSTALL) -m 755 utils/S99udpcontroller $(DESTDIR)/etc/init.d/
	$(INSTALL) -m 755 utils/udp.config $(DESTDIR)/etc/avrminicopter/


clean:
	rm -rf udpcontroller 
	rm -rf *.o *~ *.mod

