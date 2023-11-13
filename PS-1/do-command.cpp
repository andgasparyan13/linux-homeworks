#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctime>

using namespace std;

void do_command(char** argv) {
    
    clock_t start,end;
    start = clock();
    
    pid_t pid;
    int status;
    
    pid = fork();

    if (pid < 0) {
        cerr << "Fork error";
    } else if (pid == 0) {
        if (execvp(*argv, argv) < 0) {
            cerr << "Execvp error";
        }
    } else{
        waitpid(pid, &status, 0);
    	end = clock();
    	
    	double time_taken = double(end - start) / CLOCKS_PER_SEC;

    	cout << "Command completed with " << WEXITSTATUS(status) 
              << " exit code and took " << time_taken << " seconds.";
    }
    
}

int main(int argc, char** argv) {

    if (argc < 2) {
        cerr << strerror(errno) << endl;
        return 1;
    }

    do_command(argv + 1);

    return 0;
    
}

