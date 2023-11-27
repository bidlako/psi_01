# Makefile for psi_01 project

CC=gcc
CFLAGS=-std=c89
DEPS=tcp_server.h
OBJ=main.o tcp_server.o
OUTDIR=build
PORT=

$(OUTDIR)/%.o: %.c $(DEPS) | $(OUTDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTDIR)/psi_01: $(addprefix $(OUTDIR)/,$(OBJ)) | $(OUTDIR)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: all clean run

all: $(OUTDIR)/psi_01

clean:
	rm -rf $(OUTDIR)

run: $(OUTDIR)/psi_01
	./$(OUTDIR)/psi_01 $(PORT)

$(OUTDIR):
	mkdir -p $(OUTDIR)
