#include <unistd.h>

int main(int ac, char **av){
  int arr[256];

  if(ac == 3){
    for(int i=0; i<256; ++i)
      arr[i] = 0;
    while(*av[1]){
      if(!arr[*av[1]]){
        arr[*av[1]] = 1;
        write(1, av[1], 1);
      }
      ++av[1];
    }
    while(*av[2]){
      if(!arr[*av[2]]){
        arr[*av[2]] = 1;
        write(1, av[2], 1);
      }
      ++av[2];
    }
  }
  write(1, "\n", 1);
  return 0;
}
