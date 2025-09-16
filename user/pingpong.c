#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p1[2];
  int p2[2];

  pipe(p1);
  pipe(p2);

  int pid = fork();
  if(pid == 0)
  {
    char buf;
    read(p1[0], &buf, 1);
    fprintf(1, "%d: received ping\n", getpid());

    write(p2[1], &buf, 1);
  }
  else
  {
    char buf = 'Y';
    write(p1[1], &buf, 1);

    read(p2[0], &buf, 1);
    fprintf(1, "%d: received pong\n", getpid());
  }


  exit(0);
}
