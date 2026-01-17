LINK_TARGET = run
OBJS = \
       String.o\
       wordCounter.o\
       List.o


REBUILDABLES = $(OBJS) $(LINK_TARGET)
all: $(LINK_TARGET)
	@echo done

$(LINK_TARGET): $(OBJS)
	g++ -o $(LINK_TARGET) $(OBJS)

%.o : %.c
	g++ -o $@ -c $<

%.c : %.h


clean:
	rm -f $(REBUILDABLES)
