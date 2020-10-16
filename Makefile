# This sample Makefile allows you to make a OpenGL application
#   whose source is exactly one .c file.
#
#
# To use this Makefile, you must type:
#
#        make PROG=xxxx
#                  ----
# where
#       xxxx.c is the name of the file you wish to compile, or
#       ----

CC = gcc
# added -ltiff
LDLIBS = -I/users/proj/guha/mesa/Mesa-2.3/include \
	 -L/users/proj/guha/mesa/Mesa-2.3/lib \
	 -lglut  -lMesaGLU -lMesaGL -lm -lX11 -lXext -lXmu

executable: 
	$(CC) $(PROG).c \
	    $(LDLIBS) -o $(PROG)


