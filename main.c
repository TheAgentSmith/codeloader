#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "dumpcode.h"

int main(int argc, char **argv) {

    void (*rawcode)() = 0x00000000;
    
    if (argc != 2) {
        printf("Usage: %s [raw binary file]\n", argv[0]);
    }

    int fd = 0;

    fd = open(argv[1], O_RDONLY);

    if(fd == -1) {
        printf("Error! Cannot open file %s!\n", argv[0]);
        _exit(1);
    }

    struct stat stat_bin;

    if(fstat(fd, &stat_bin) == -1) {
        printf("Error! fstat() failed!\n");
        _exit(2);
    }

    rawcode = mmap(0, stat_bin.st_size, PROT_EXEC | PROT_READ, MAP_PRIVATE, fd, 0);
/*
    if(read(fd, rawcode, stat_bin.st_size) == -1) {
        printf("Error! read() failed!\n");
        _exit(3);
    }
*/
    /*
     * OK. We have raw opcode in *rawcode.
     * Before we dive into it, We have to make it executable.
     */

    dumpcode(rawcode, stat_bin.st_size);
    /*printf("MPROTECT\n");
    if(mprotect(rawcode, sizeof(rawcode), PROT_READ | PROT_EXEC) == 1) {
        printf("Error! mprotect() failed!\n");
        _exit(4);
    }*/

    printf("TEST");
  //  ((char*)rawcode)[0] = 1;

    //Dive now. There is no way to go back!
    printf("Goodbye!\n");
    rawcode();
}
