IDIR =.
CC=gcc
CFLAGS=-I$(IDIR) -std=c++11 -v

ODIR=.
LDIR =.

LIBS=-lm

_DEPS = Currency.h Customer.h Account.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o Account.o Customer.o CurrencyTest.o Currency.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cpptest: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
