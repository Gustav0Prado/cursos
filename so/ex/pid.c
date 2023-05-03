#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  pid_t pid[10];
  int i;

  int N = atoi(argv[argc-2]);
  printf("%d\n", N);

  for (i=0; i<N; i++)
    pid[i] = fork();
  if (pid[0] != 0 && pid[N-1] != 0)
    pid[N] = fork();
  printf("X");
  return 0;
}

