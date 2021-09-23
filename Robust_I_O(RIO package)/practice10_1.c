#include "csapp.h"

int main()
{
    int fd1, fd2;
    // int open(char *filename, int flags, mode_t mode);
    // open은 filename을 식별자로 변환하고 식별자 번호를 리턴함.
    // O_RDONLY: READING ONLY, O_WRONLY: WRITING ONLY, O_RDWR: READING AND WRITING
    fd1 = Open("foo.txt", O_RDONLY, 0);
    Close(fd1);
    // O_CAEAT: 파일이 존재하지 않으면 비어 있는 파일을 생성, O_TRUNC: 파일이 이미 존재하면 파일의 내용을 바꿈
    // O_APPEND: 매 쓰기 연산 전에 파일 위치를 파일의 마지막으로 설정
    fd2 = Open("baz.txt", O_RDONLY|O_CREAT, 0);
    printf("fd2 = %d\n", fd2);
    exit(0);
}
