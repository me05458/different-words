LINK_TARGET = run
OBJS = \
       w_List.o\
       w_String.o\
       wordCounter.o\
       test.o\

REBUILDABLES = $(OBJS) $(LINK_TARGET)
all: $(LINK_TARGET)
	@echo done

$(LINK_TARGET): $(OBJS) makefile w_List.h
	g++ -o $(LINK_TARGET) $(OBJS)

%.o : %.cpp
	g++ -o $@ -c $<

%.cpp : %.h

w_String.cpp: w_List.h
test.cpp: w_List.h w_String.h

clean:
	rm -f $(REBUILDABLES)
