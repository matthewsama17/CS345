#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc <= 1)
  {
    fprintf(2, "Error: No argument provided.\n");
    exit(1);
  }

  int pause = atoi(argv[1]);

  sleep(pause);

  exit(0);
}
