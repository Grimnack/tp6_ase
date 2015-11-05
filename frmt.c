#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "drive.h"
#include "hardware.h"

void empty_irq() {
  return;
}

int main(int argc, char *argv[]) {
  int i, j;

  printf("debut formatage\n");

  if(init_hardware("./etc/hardware.ini")) {

    for ( i = 0; i < 16; i++ ) {
      IRQVECTOR[i] = empty_irq;
    }

    _mask(1);

    for ( i = 0; i < HDA_MAXCYLINDER; i++ ) {
      for ( j = 0; j < HDA_MAXSECTOR; j++ ) {
        format_sector( i, j, 1, 0);
      }
    }
  }
  else {
    printf("FATAL ERROR: can't init hardware\n");
    exit(EXIT_FAILURE);
  }

  printf("finish");

  return 0;
}
