#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

using namespace std;

int main(int argc, char** argv){

  if(argc < 3){
    cerr << "File path is not given" << endl;
    exit(1);
  }

  char* path = argv[1];
  char* n_path = argv[2];

  int file_d = open(path,O_RDONLY);

  if(file_d < 0){
    cerr << strerror(errno) << endl;
    exit(errno);
  }

  int nfile_d = open(n_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

  if(nfile_d < 0){
    cerr << strerror(errno) << endl;
    exit(errno);
  }

  char buff[10];
  while(true){
    int read_bytes = read(file_d, buff, sizeof(buff));
    if(read_bytes < 0){
      cerr << strerror(errno) << endl;
      exit(errno);
    }else if(read_bytes == 0){
      break;
    }

    int write_bytes = write(nfile_d, buff, read_bytes);
    if(write_bytes < 0){
      cerr << strerror(errno) << endl;
      exit(errno);
    }

  }

  close(file_d);
  close(nfile_d);

  return 0;

}

