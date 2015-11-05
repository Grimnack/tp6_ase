#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>

#include "hardware.h"
#include "vol.h"

void empty_irq() {
  return;
}

int main(int argc, char* argv[]) {
  int flags, opt;
  int length, tfnd;
  int i;

  length = 0;
  tfnd = 0;
  flags = 0;
  while ((opt = getopt(argc, argv, "ns:")) != -1) {
    switch (opt) {
      case 'n':
      flags = 1;
      break;
      case 's':
      length = atoi(optarg);
      tfnd = 1;
      break;
      default: /* '?' */
      fprintf(stderr, "Usage: %s [-s length] [-n] name\n",
      argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  printf("flags=%d; tfnd=%d; optind=%d\n", flags, tfnd, optind);

  if (optind >= argc) {
    fprintf(stderr, "Expected argument after options\n");
    exit(EXIT_FAILURE);
  }

  printf("name argument = %s\n", argv[optind]);

  if(init_hardware("./etc/hardware.ini")) {

    for ( i = 0; i < 16; i++ ) {
      IRQVECTOR[i] = empty_irq;
    }

    /*read_mbr();*/

  }
  else {
    printf("FATAL ERROR: can't init hardware\n");
    exit(EXIT_FAILURE);
  }

  printf("%d\n", length);

  return 0;
}
