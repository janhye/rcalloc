LIBNAME = librcalloc.a
OBJS    = rcalloc.o

$(LIBNAME): $(OBJS)
	ar rcs $(LIBNAME) $(OBJS)

rcalloc.o: rcalloc.h

.PHONY: clean
clean:
	rm -f $(LIBNAME) $(OBJS)
