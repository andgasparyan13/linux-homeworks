#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>
#include <errno.h>

using namespace std;

int main(int argc,char** argv){
    
    if(argc < 2){
        cerr << "File path is not given" << endl;
        exit(1);
    }
    
    int flags = O_WRONLY | O_CREAT | O_TRUNC;
    int permisions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    
    char* path = argv[1];
    
    int fd = open(path,flags,permisions);
    if(fd < 0){
        cerr << strerror(errno) << endl;
        exit(errno);
    }
    
    int fd2;
    
    int duplicate = dup2(fd,fd2);
    if(duplicate < 0){
        cerr << strerror(errno) << endl;
        exit(errno);
    }
    
    string first = "first line\n";
    int wr1 = write(fd,first.c_str(),first.size());
    
    string second = "second line";
    int wr2 = write(fd2,second.c_str(),second.size());
    
    
    int close_file = close(fd);
    if(close_file < 0){
        cerr << strerror(errno) << endl;
        exit(errno);
    }
    
    return 0;
}

