#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int random_int() {
  int* ret_p = calloc(sizeof(int), 1);
  int x = open("/dev/random", O_RDONLY);
  read(x, ret_p, sizeof(int));
  close(x);
  int ret = *ret_p;
  free(ret_p);
  return ret;
}

int main() {
  int parent_id = getpid();
  int status;
  printf("PARENT FORKING\n");
  int child_0_id = fork();
  if (getpid() == parent_id) {
    int child_1_id = fork();
    if (getpid() == parent_id) {
      int exited_child = wait(&status);
      int slept_for = WEXITSTATUS(status);
      printf("CHILD %d SLEPT FOR: %d s\n", exited_child, slept_for);
      printf("PARENT IS DONE\n");
      exit(1);
    }
    else { // second child
      printf("MY PID: %d\n", getpid());
      int sleep_2 = random_int();
      sleep_2 &= 127;
      sleep_2 %= 20;
      sleep_2 += 5;
      sleep(sleep_2);
      printf("DONE SLEEPING\n");
      return sleep_2;
    }
  }
  else {
    printf("MY PID: %d\n", getpid());
    int sleep_1 = random_int();
    sleep_1 &= 127;
    sleep_1 %= 20;
    sleep_1 += 2;
    sleep(sleep_1);
    printf("DONE SLEEPING\n");
    return sleep_1;
  }
  return 0;
}
