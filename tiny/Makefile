# tiny: tiny.o csapp.o
# 	gcc -o tiny tiny.o csapp.o
# tiny.o: tiny.c
# 	gcc -c tiny.c
# csapp.o: csapp.c
# 	gcc -c csapp.c

# clean:
# 	rm -f *.o
# 	rm -f tiny

TARGET = tiny
OBJS = 	tiny.o csapp.o
%.o: %.c
	gcc -c $<
$(TARGET) : $(OBJS)
	gcc -o $(TARGET) $(OBJS)
clean:
	rm -f *.o
	rm -f $(TARGET)