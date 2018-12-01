cstart: scanner.o sig_h.o disp_title.o main.c stdafx.h struct.h synatt.o
	gcc -g synconn.o synatt.o scanner.o conn.o sig_h.o disp_title.o main.c stdafx.h struct.h -o cstart
	rm *.o 

scanner.o:models/scanner.h models/scanner.c connect/conn.h connect/conn.c
	gcc -c models/scanner.h models/scanner.c connect/conn.h connect/conn.c
sig_h.o:single_handle/sig_h.h single_handle/sig_h.c
	gcc -c single_handle/sig_h.h single_handle/sig_h.c
disp_title.o:display/disp_title.h display/disp_title.c
	gcc -c display/disp_title.h display/disp_title.c
synatt.o:models/synatt.h models/synatt.c connect/synconn.h connect/synconn.c
	gcc -c models/synatt.h models/synatt.c connect/synconn.h connect/synconn.c
clean:
	rm -r *.o *.gch
