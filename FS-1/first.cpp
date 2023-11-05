#include <stdlib.h>
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

#define BUF_SIZE 10

int main(int argc, char** argv){
    if(argc < 2){
        cerr << "File path is not given"<< endl;
        exit(1);
    }
    
    char* path = argv[1];
    
    int file_d =  open(path, O_RDONLY);
    if(file_d < 0){
        cerr<< errno << strerror(errno);
        exit(errno);
    }
    
    char* buff = new char[BUF_SIZE + 1];
    while(true){
        int bytes_read = read(file_d, buff, BUF_SIZE);
            
        if(bytes_read < 0){
             cerr<< strerror(errno);
             exit(errno);
        }
            
        if(bytes_read == 0){
                break;
            }
            
       buff[bytes_read] = '\0';
       cout<< buff;
    }
    
    int close_num = close(file_d);
    if(close_num < 0) {
        cerr<< errno << strerror(errno);
        exit(errno);
    }    
    
    delete[] buff;
    return 0;
}

