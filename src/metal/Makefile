# Makefile pour le compilateur de mtl.
COMMON_OBJS=properties.o log.o

COMP_OBJS=main_compiler.o

SIMU_SRC=main_simu.c linux_simu.c linux_simuaudio.c linux_simunet.c linux_simuled.c vmem.c vloader.c vlog.c vinterp.c vaudio.c vnet.c
SIMU_OBJS=$(SIMU_SRC:.c=.o)

CXXFLAGS=-g
CFLAGS=-g 

CC=gcc
CXX=g++

all : mtl_simu mtl_comp

.PHONY : vcomp/libvcomp.a

vcomp/libvcomp.a :
	cd vcomp && $(MAKE)

mtl_comp : vcomp/libvcomp.a $(COMMON_OBJS) $(COMP_OBJS)
	$(CXX)  $^ -o $@ vcomp/libvcomp.a

mtl_simu : vcomp/libvcomp.a $(COMMON_OBJS) $(SIMU_OBJS)
	$(CXX)  $^ -o $@ vcomp/libvcomp.a -lncurses

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean :
	cd vcomp && $(MAKE) $@
	rm -f $(COMMON_OBJS) $(COMP_OBJS) $(SIMU_OBJS)
	rm -f foo.bin mtl_simu mtl_comp 
