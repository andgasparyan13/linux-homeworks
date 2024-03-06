#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

using namespace std;

bool prime(int n) {
    if (n <= 1){
      return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0){
          return false; 
        }
    }
    return true;
}

int find_m_Prime(int n) {
    int count = 0;
    int num = 2; 
    while (count < n) {
        if (prime(num)) {
            count++; 
        }
        num++;
    }
    return num - 1;
}

int main() {
  int pipe1[2];
  int pipe2[2];
  int pipe1_result = pipe(pipe1);
  int pipe2_result = pipe(pipe2);

  if(pipe1_result < 0){
    cerr<<strerror(errno)<<endl;
    exit(errno);
  }
  
  if(pipe2_result < 0){
    cerr<<strerror(errno)<<endl;
    exit(errno);
  }

  
  int pid = fork();

  if(pid < 0){
    cerr<<strerror(errno)<<endl;
    exit(errno);
  }

  if(pid == 0){
    
    close(pipe1[1]);
    close(pipe2[0]);
    while(true){
      int m;
      
     
      int readResult = read(pipe1[0],&m,sizeof(int));
      if(readResult < 0){
        cerr<<strerror(errno)<<endl;
        exit(errno);
      }
       cout<<"[Child] Calculating 8-th prime number..."<<endl;

      cout<<"[Child] Sending calculation result of prime(8)..."<<endl;
      int m_prime = find_m_Prime(m);
      int writeResult = write(pipe2[1],&m_prime,sizeof(int));
  
      if(writeResult < 0){
        cerr<<strerror(errno)<<endl;
        exit(errno);
      }
    }
    
  }

  if(pid > 0){
    close(pipe1[0]);
    close(pipe2[1]);
    string m;
    int mToInt;
    
    while(true){
      cout<<"[Parent] Please enter the number: ";
      cin>>m;
      if(m == "exit"){
        break;
      }
      
      mToInt = stoi(m);
      
      cout<<"[Parent] Sending 8 to the child process..."<<endl;
      cout<<"[Parent] Waiting for the response from the child process..."<<endl;
      int writeResult = write(pipe1[1], &mToInt, sizeof(int));
      
      if(writeResult < 0){
        cerr<<strerror(errno)<<endl;
        exit(errno);
      }

      int m_prime = 0;
      int readResult = read(pipe2[0],&m_prime,sizeof(int));

      if(readResult < 0){
        cerr<<strerror(errno)<<endl;
        exit(errno);
      }
      cout<<"[Parent] Received calculation result of prime(8) = 19... "<<endl;
      cout<<m_prime<<endl;
    }
  }
  return 0;
  
}