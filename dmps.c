#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "drive.h"
#include "hardware.h"

void empty_irq() {
  return;
}

int main(int args, char *argv[]) {
  unsigned char buffer[HDA_SECTORSIZE];
  int cylinder, sector;
  int i;

  if(init_hardware("./etc/hardware.ini")) {

    for ( i = 0; i < 16; i++ ) {
      IRQVECTOR[i] = empty_irq;
    }

    cylinder = atoi(argv[1]);
    sector = atoi(argv[2]);

    printf("cylinder: %d, sector: %d\n", cylinder, sector);

    read_sector(cylinder, sector, buffer);

    for(i = 0; i < HDA_SECTORSIZE; i++) {
      printf("%02X\n", buffer[i]);
    }
  }
  else {
    printf("FATAL ERROR: can't init hardware\n");
    exit(EXIT_FAILURE);
  }

  return 0;
}
