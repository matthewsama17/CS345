#include "kernel/types.h"
#include "user/user.h"

int
readline(int fd, char *buf)
{
  int tot_read = 0;

  do
  {
    int num_read = read(fd, buf + tot_read, 1);
    tot_read += num_read;

    if(num_read == 0)
    {
      return tot_read;
    }
  } while(buf[tot_read-1] != '\n');

  tot_read--;
  buf[tot_read] = '\0';

  return tot_read;
}

int
main(int argc, char *argv[])
{

  if(argc <= 1)
  {
    fprintf(2, "Error: No argument provided.\n");
    exit(1);
  }

  char buf[256];
  for(int i = 1; i < argc; i++)
  {
    argv[i-1] = argv[i];
  }

  argv[argc-1] = buf;

  for(int line_len = readline(0, buf);
      line_len != 0;
      line_len = readline(0, buf))
  {
    int pid = fork();
    if(pid == 0)
    {
      exec(argv[0], argv);
    }
    else
    {
      int wstatus;
      wait(&wstatus);
    }
  }

  exit(0);
}
