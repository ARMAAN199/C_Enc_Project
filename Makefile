# # Simple makefile for compiling a program from
# # two C source files.  

# .KEEP_STATE

# functions: structure.o
#          cc -O -o functions structure.o
# structure.o: structure.c 
#         	cc -O -c structure.c 
# clean: 
#         	rm functions structure.o

final :
	gcc structure.c -o final
	./final