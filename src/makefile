disp_efile=display/disperror.c display/disperror.h
conn_file=connect/conn.h connect/conn.c
scanner_file=models/scanner.h models/scanner.c
sig_hfile=single_handle/sig_h.h single_handle/sig_h.c
disp_tfile=display/disp_title.h display/disp_title.c
synco_file=connect/synconn.h connect/synconn.c
synatt_file=models/synatt.h models/synatt.c
bulid:scanner.o synconn.o conn.o sig_h.o disp_title.o main.c stdafx.h struct.h synatt.o disperror.o
	gcc  synconn.o synatt.o scanner.o conn.o sig_h.o disp_title.o disperror.o main.c stdafx.h struct.h -o cstart -std=gnu11
	rm *.o 
conn.o:$(conn_file)
	gcc -c $(conn_file)
scanner.o:$(scanner_file)
	gcc -c $(scanner_file)
sig_h.o:$(sig_hfile)
	gcc -c $(sig_hfile)
disp_title.o:$(disp_tfile)  
	gcc -c $(disp_tfile)
disperror.o:$(disp_efile) 
	gcc -c $(disp_efile)
synatt.o:$(synatt_file) 
	gcc -c $(synatt_file)
synconn.o:$(synco_file)
	gcc -c $(synco_file)
clean:
	rm -r *.o *.gch
install:
	echo "install succeed"
