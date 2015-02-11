#include <stdio.h>
#include <unistd.h>


#include "hydra.h"

int main(){
  hydra_init(5);
  while (1){
    sleep(1);
    printf("main\n");
  }
  return 0;
}
