#include <assert.h>
#include <string.h>

#include "drive.h"
#include "vol.h"

struct mbr_s mbr;
struct superbloc_s sb;
unsigned int volume_courant;

void read_mbr() {
  unsigned char buff[HDA_SECTORSIZE];

  read_sector(0, 0, buff);
  memcpy(&mbr, buff, sizeof(struct mbr_s));

  if(mbr.magic != 0xB16B00B5) {
    init_mbr();
  }
}

void init_mbr() {
  unsigned char buff[HDA_SECTORSIZE];

  mbr.nb_vols = 0;
  mbr.magic = 0xB16B00B5;

  assert(mbr.magic == 0xB16B00B5);

  memset(buff, HDA_SECTORSIZE, sizeof(struct mbr_s));
  memcpy(buff, &mbr, sizeof(struct mbr_s));

  write_sector(0,0,buff);
}

unsigned int convert_address_sec(unsigned int nvol, unsigned int nblocks) {

  assert(mbr.vols[nvol].nb_blocks > nblocks);
  assert(mbr.vols[nvol].nb_blocks > nblocks);

  return ((mbr.vols[nvol].first_sec + nblocks) % HDA_MAXSECTOR);
}

unsigned int convert_address_cyl(unsigned int nvol, unsigned int nblocks) {

  assert(nvol < mbr.nb_vols);
  assert(mbr.vols[nvol].nb_blocks > nblocks);

  return ((mbr.vols[nvol].first_cyl + nblocks) / HDA_MAXCYLINDER);
}

void read_block(unsigned int vol, unsigned int nblocks, unsigned char *buff) {
  unsigned int sector, cylinder;

  sector = convert_address_sec(vol, nblocks);
  cylinder = convert_address_cyl(vol, nblocks);

  read_sector(cylinder, sector, buff);
}

void write_block(unsigned int vol, unsigned int nblocks, unsigned char *buff) {
  unsigned int sector, cylinder;

  sector = convert_address_sec(vol, nblocks);
  cylinder = convert_address_cyl(vol, nblocks);

  write_sector(cylinder, sector, buff);
}

void format_vol(unsigned int vol) {
  struct vol_s volume;
  unsigned int sector, cylinder;
  int i;

  volume = mbr.vols[vol];

  for(i = 0; i < volume.nb_blocks; i++) {
    sector = convert_address_sec(vol, i);
    cylinder = convert_address_cyl(vol, i);

    format_sector(cylinder, sector, 1, 0);
  }


}


int load_super(unsigned int vol){

}

/*
sauvegarde la variable globale superbloc 
*/
void save_super(){

}

/*
initialiser le superbloc au début du volume donné,
et initialiser les blocs libres qui suivent derriere.
*/
void init_super(unsigned int vol){

}

/*
occupe le premier bloc libre
modifie la structure pour faire comme si on a alloué un bloc 
retourne le bloc qui a été alloué

Si plus de bloc libre on renvoie 0
*/
unsigned int new_bloc(){
  unsigned int alloue = sb.premiers_blocs_libres;
  if (sb.premiers_blocs_libres == 0) 
    return 0;
  /*On charge blocs_libre_s et on le copie dans bl*/ 
  if(bl.taille > 1) {
    bl.taille -= 1 ;
    sb.premiers_blocs_libres += 1 ;
    //on fait un write_block de alloue
  }
  return alloue
}


/*
libere l'espace memoire du bloc donné en param
*/
void free_bloc(unsigned int bloc){
  struct blocs_libres_s bl;
  unsigned char buff[HDA_SECTORSIZE];
  bl.taille = 1;
  bl.suivants = sb.premiers_blocs_libres;
  sb.premiers_blocs_libres = bloc;
  *((struct blocs_libres_s *) buff) = bl ;
  write_block(volume_courant, bloc, buff) ;  
}



