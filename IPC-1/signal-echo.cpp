#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <pwd.h>
#include <ucontext.h>

using namespace std;

void handle_sigusr1(int sig, siginfo_t* info, void* context) {
    ucontext_t* sig_context = (ucontext_t*)context;
    pid_t sender_pid = info->si_pid;
    uid_t sender_uid = getuid();
    struct passwd *sender_pw = getpwuid(sender_uid);

    cout << "Received a SIGUSR1 signal from process " << sender_pid
         << " executed by " << sender_uid << " (" << sender_pw->pw_name << ").\n"
         << "State of the context:\n"
         << "  EIP = " << hex << sig_context->uc_mcontext.gregs[REG_RIP]
         << "  EAX = " << hex << sig_context->uc_mcontext.gregs[REG_RAX]
         << "  EBX = " << hex << sig_context->uc_mcontext.gregs[REG_RBX];
}

int main() {
    pid_t pid = getpid();
    cout << "My PID: " << pid << endl;

    struct sigaction act;
    act.sa_sigaction = handle_sigusr1;
    sigaction(SIGUSR1, &act, NULL);

    while (true) {
        sleep(10);
    }

    return 0;
}

