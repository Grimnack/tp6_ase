#ifndef VOL_H
#define VOL_H

#define NB_MAX_VOL 8

enum voltype_e {BASE, ANNEX, OTHER};


struct superbloc_s {
    int magic;
    unsigned int premiers_blocs_libres;
    int numero_serie;
    char nom[32];
    unsigned int racine;

};

struct blocs_libres_s {
    unsigned int taille ;
    unsigned int suivants;
};

struct vol_s {
  unsigned int first_cyl;
  unsigned int first_sec;
  unsigned int nb_blocks;
  enum voltype_e type;
  char nom[32];
};

struct mbr_s {
  struct vol_s vols[NB_MAX_VOL];
  unsigned int nb_vols;
  int magic;
};



extern struct mbr_s mbr;

extern void read_mbr();
extern void init_mbr();
extern unsigned int convert_address_sec(unsigned int nvol, unsigned int nblocks);
extern unsigned int convert_address_cyl(unsigned int nvol, unsigned int nblocks);
extern void read_block(unsigned int vol, unsigned int nblocks, unsigned char *buff);
extern void write_block(unsigned int vol, unsigned int nblocks, unsigned char *buff);
extern void format_vol(unsigned int vol);
extern void init_super(unsigned int vol);


#endif
