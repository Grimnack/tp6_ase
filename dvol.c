#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>

#include "hardware.h"
#include "vol.h"

/*
L'idee c est d'imprimer un seul volume ici
Avec read_bloc qui lit le volume donné et qui
sauvegarde la lecture dans un buffer.

Ensuite on imprime le tout sous la forme d'une jolie
matrice carrée de fayot
*/
void print_vol(unsigned int volume, unsigned int nbloc) {
    int i,j;

    unsigned char *buff=malloc(256); 

    read_bloc(volume,nbloc,buff);

    for(i=0;i<16;i++) {
        printf("%03x: ",i*16);
        for(j=0;j<16;j++) 
            printf("%02x ",buff[i*16+j]);
        printf("\n");
    }    
}


/*
Dans notre programme on imprime la 
*/
int main(int argc, char **argv){
    if (argc < 3) {
        printf("dvol usage: ./dvol [num vol] [nbloc]\n");
        exit(); /*Petit scarabé*/
    }
    init_driver();
    load_mbr(); // Bah oui sinon tu as pas l'air malin avec tes int
    print_vol(volume,nbloc);
    return 0; //pas 1 pas 2, 0 !!
}