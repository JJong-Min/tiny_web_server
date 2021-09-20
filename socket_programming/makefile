# echoclient만 파일명에 맞게 바꿔주면 됨.
TARGET = echoclient
OBJS = 	echoclient.o csapp.o
%.o: %.c
	gcc -c $<
$(TARGET) : $(OBJS)
	gcc -o $(TARGET) $(OBJS)
clean:
	rm -f *.o
	rm -f $(TARGET)