#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

int main(){
  int READ = 0;
  int WRITE = 1;
  int fds1[2];
  int fds2[2];
  pipe(fds1);
  pipe(fds2);
  int f;
  f = fork();
  if(f){
    close(fds1[READ]);
    close(fds2[WRITE]);
    srand(time(NULL));
    int y = rand();
    write(fds1[WRITE], &y, sizeof(int));
    printf("Parent here. I'm sending %d to child\n", y);
  }
  if(!f){
    close(fds1[WRITE]);
    close(fds2[READ]);
    int x;
    read(fds1[READ], &x, sizeof(x));
    printf("Child received %d. Performing arithmatic, mod 17\n", x);
    x = x % 17;
    write(fds2[WRITE], &x, sizeof(int));
  }
  if(f){
    int z;
    read(fds2[READ], &z, sizeof(int));
    printf("Parent received %d\n", z);
  }
  return 0;
}

    
