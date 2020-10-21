# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
CFLAGS  = -Wall -O0

# library flags
LFLAGS = -lcrypto

# build targets
FLAGVAULT = flagvault
CRYPTOHELPER = crypto_helper


all: clean $(FLAGVAULT)

$(FLAGVAULT): $(FLAGVAULT).c
	$(CC) $(CFLAGS) -o $(FLAGVAULT).clean $(CRYPTOHELPER).c $(FLAGVAULT).c $(LFLAGS)
	./injector.py
	$(CC) $(CFLAGS) -o $(FLAGVAULT) $(CRYPTOHELPER).c $(FLAGVAULT).injected.c $(LFLAGS)
	strip --strip-all $(FLAGVAULT)

clean:
	$(RM) $(FLAGVAULT) $(FLAGVAULT).clean $(FLAGVAULT).injected.c
