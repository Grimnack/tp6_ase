#ifndef DRIVE_H
#define DRIVE_H

#define HDA_CMDREG 0x3F6
#define HDA_DATAREGS 0x110
#define HDA_IRQ 14
#define HDA_MAXCYLINDER 16
#define HDA_MAXSECTOR 16
#define HDA_SECTORSIZE 32

extern void read_sector(unsigned int cylinder, unsigned int sector, unsigned char* buffer);
extern void write_sector(unsigned int cylinder, unsigned int sector, unsigned char *buffer);
extern void format_sector(unsigned int cylinder, unsigned int sector, unsigned int nsector, unsigned int value);

#endif
