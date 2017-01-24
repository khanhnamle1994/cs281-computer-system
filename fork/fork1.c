#include "csapp.h"

int main(int argc, char ** argv) {
  int childcount = 1;
  int mypid;
  int forkreturn;

  if (argc > 1) {
    childcount = atoi(argv[1]); // asci to integer
  }
  mypid = getpid();
  printf("Before fork loop with pid=%d\n", mypid);
  Sleep(5);

  forkreturn = Fork();
  if (forkreturn == 0) {
    printf("I am the child with pid: %d\n", getpid());
  } else {
    printf("I am the parent with pid: %d\n", getpid());
  }
}
