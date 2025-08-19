CC = gcc
CFLAGS = -g

main: main.o initialisation.o enregistrement.o listeDisciplines.o relations.o algorithmique.o
	$(CC) $(CFLAGS) $^ -o $@

initialisation.o: initialisation.c initialisation.h
	$(CC) $(CFLAGS) -c $<

enregistrement.o: enregistrement.c enregistrement.h initialisation.h listeDisciplines.h
	$(CC) $(CFLAGS) -c $<

listeDisciplines.o: listeDisciplines.c listeDisciplines.h initialisation.h
	$(CC) $(CFLAGS) -c $<

relations.o: relations.c relations.h initialisation.h listeDisciplines.h enregistrement.h
	$(CC) $(CFLAGS) -c $<

algorithmique.o: algorithmique.c algorithmique.h initialisation.h listeDisciplines.h enregistrement.h relations.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c initialisation.h enregistrement.h listeDisciplines.h relations.h algorithmique.h
	$(CC) $(CFLAGS) -c $<

