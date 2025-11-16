CC=gcc
TARGET=lab2.exe

SRCDIR=src
OBJDIR=build

DELCMD = del /f

SRC=lab2_6.c func.c
OBJ=$(SRC:%.c=%.o)

SRCS=$(SRC:%=$(SRCDIR)/%)
OBJS=$(OBJ:%=$(OBJDIR)/%)
DELOBJS=$(OBJ:%=$(OBJDIR)\\%)

LOG = logs.txt
LOGDIR = $(OBJDIR)
LOGS = $(LOGDIR)\$(LOG)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $^ -o $@

clean:
	$(DELCMD) $(TARGET)
	
cleanall: clean
	$(DELCMD) $(DELOBJS)
	$(DELCMD) $(LOGS)
