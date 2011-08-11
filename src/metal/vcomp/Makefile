CXX=g++
CXXFLAGS=
OBJS = 	bootstrap.o \
	compiler_file.o \
	compiler.o \
	compiler_prog.o \
	compiler_term.o \
	compiler_type.o \
	compiler_var.o \
	file.o \
	interpreter.o \
	memory.o \
	parser.o \
	parser_xml.o \
	prodbuffer.o \
	stdlib_core.o \
	terminal.o \
	util.o

all: clean libvcomp.a

libvcomp.a : $(OBJS)
	ar rcs $@ $(OBJS)
	ranlib $@

%.o : %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

clean :
	rm -f $(OBJS) libvcomp.a
