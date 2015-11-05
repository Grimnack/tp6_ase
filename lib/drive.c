#include <string.h>
#include <stdio.h>

#include "drive.h"
#include "hardware.h"

void read_sector(unsigned int cylinder, unsigned int sector, unsigned char* buffer) {

  /* ecriture sur les ports de données */
  /* on est obligé d'éclater l'information du cylindre en 2 octets car int = 16 bits = 2 o*/

  /* ici on écrit le poid fort, on decale donc de 8 bits et on cast grâce au masque
  pour remplir avec des 0 les bits non complété */
  _out(HDA_DATAREGS+0, (cylinder>>8)&0xff);

  /* ici on écrit le poid faible, on prends donc la variable et on lui applique le masque */
  _out(HDA_DATAREGS+1, cylinder&0xff);

  /* on fait la même opération pour le secteur */
  _out(HDA_DATAREGS+2, (sector>>8)&0xff);
  _out(HDA_DATAREGS+3, sector&0xff);

  /* on place la tête de lecture en lançant la commande SEEK */
  _out(HDA_CMDREG, CMD_SEEK);

  /* on attends la fin du SEEK, on attends donc l'interruption renvoyé par le HDD */
  _sleep(HDA_IRQ);

  /* on lit les données provenant du secteur */

  /* ecriture du nombre de secteur sur les ports de données */
  /* On utilise le même principe que precedement, on divise en 2 octets */

  _out(HDA_DATAREGS+0, 0);
  _out(HDA_DATAREGS+1, 1);

  /* on lit les informations en lançant la commande READ */
  _out(HDA_CMDREG, CMD_READ);

  /* on attends la fin du READ */
  _sleep(HDA_IRQ);

  /* on place les données lu dans le buffer */
  memcpy(buffer, MASTERBUFFER, HDA_SECTORSIZE);
}

void write_sector(unsigned int cylinder, unsigned int sector, unsigned char *buffer) {

  int nbsector;

  nbsector = 1;

  memcpy(buffer, MASTERBUFFER, HDA_SECTORSIZE);
  /* ecriture sur les ports de données */
  /* on est obligé d'éclater l'information du cylindre en 2 octets car int = 16 bits = 2 o*/

  /* ici on écrit le poid fort, on decale donc de 8 bits et on cast grâce au masque
  pour remplir avec des 0 les bits non complété */
  _out(HDA_DATAREGS+0, (cylinder>>8)&0xff);

  /* ici on écrit le poid faible, on prends donc la variable et on lui applique le masque */
  _out(HDA_DATAREGS+1, cylinder&0xff);

  /* on fait la même opération pour le secteur */
  _out(HDA_DATAREGS+2, (sector>>8)&0xff);
  _out(HDA_DATAREGS+3, sector&0xff);

  /* on place la tête de lecture en lançant la commande SEEK */
  _out(HDA_CMDREG, CMD_SEEK);

  /* on attends la fin du SEEK, on attends donc l'interruption renvoyé par le HDD */
  _sleep(HDA_IRQ);

  /* on ecrit les données provenant du secteur */

  /* ecriture du nombre de secteur sur les ports de données */
  /* On utilise le même principe que precedement, on divise en 2 octets */

  _out(HDA_DATAREGS+0, (nbsector>>8)&0xff);
  _out(HDA_DATAREGS+1, nbsector&0xff);

  /* on lit les informations en lançant la commande READ */
  _out(HDA_CMDREG, CMD_WRITE);

  /* on attends la fin du WRITE */
  _sleep(HDA_IRQ);
}

void format_sector(unsigned int cylinder, unsigned int sector, unsigned int nsector, unsigned int value) {

  /* ecriture sur les ports de données */
  /* on est obligé d'éclater l'information du cylindre en 2 octets car int = 16 bits = 2 o*/

  /* ici on écrit le poid fort, on decale donc de 8 bits et on cast grâce au masque
  pour remplir avec des 0 les bits non complété */
  _out(HDA_DATAREGS+0, (cylinder>>8)&0xff);

  /* ici on écrit le poid faible, on prends donc la variable et on lui applique le masque */
  _out(HDA_DATAREGS+1, cylinder&0xff);


  /* on fait la même opération pour le secteur */
  _out(HDA_DATAREGS+2, (sector>>8)&0xff);
  _out(HDA_DATAREGS+3, sector&0xff);


  /* on place la tête de lecture en lançant la commande SEEK */
  _out(HDA_CMDREG, CMD_SEEK);

  /* on attends la fin du SEEK, on attends donc l'interruption renvoyé par le HDD */
  _sleep(HDA_IRQ);


  /* on ecrit le nombre de secteur sur les ports */
  _out(HDA_DATAREGS+0, (nsector>>8)&0xff);
  _out(HDA_DATAREGS+1, nsector&0xff);

  /* ensuite on ecrit la valeur sur les ports, celle ci est sur 32 bits il faut donc la diviser en 4 */
  _out(HDA_DATAREGS+2, (value>>24)&0xff);
  _out(HDA_DATAREGS+3, (value>>16)&0xff);
  _out(HDA_DATAREGS+4, (value>>8)&0xff);
  _out(HDA_DATAREGS+5, value&0xff);

  /* on lance la commande pour formater le secteur */
  _out(HDA_CMDREG, CMD_FORMAT);

  /* on attends la fin du formatage */
  _sleep(HDA_IRQ);
}
