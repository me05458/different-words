LINK_TARGET = run
OBJS = \
       List.o\
       String.o\
       wordCounter.o\

REBUILDABLES = $(OBJS) $(LINK_TARGET)
all: $(LINK_TARGET)
	@echo done

$(LINK_TARGET): $(OBJS)
	#g++ -o $(LINK_TARGET) $(OBJS)
	g++ -o run List.cpp String.cpp wordCounter.cpp


String.cpp: List.h

clean:
	rm -f $(REBUILDABLES)
