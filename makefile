LINK_TARGET = run
OBJS = \
       w_List.o\
       w_String.o\
       wordCounter.o\

REBUILDABLES = $(OBJS) $(LINK_TARGET)
all: $(LINK_TARGET)
	@echo done

$(LINK_TARGET): $(OBJS)
	g++ -o $(LINK_TARGET) $(OBJS)

%.o : %.c
	gcc -o $@ -c $<

w_String.cpp: w_List.h

clean:
	rm -f $(REBUILDABLES)
