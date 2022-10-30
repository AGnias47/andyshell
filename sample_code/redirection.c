// Not functional; taken from slides


int main()
{
    close(1);               // close the default stdout
    open(“stdout.txt”,”w”); // replace it by opening the output file
    if (fork() == 0)
    {                 // child process
        exec(“cmd1”); // writes to stdout
                      // never reach this line
    }
    else
    { // parent
        pid = wait(&status);
        printf(“Child process % d terminated \n”, pid);
        exit(0);
    }
}