#include <fs/msdospart.h>

#include <fs/fat.h>

using namespace sinix;
using namespace sinix::common;
using namespace sinix::drivers;
using namespace sinix::fs;

void printf(char*);
void printfHex(uint8_t);

void MSDOSPartitionTable::ReadPartitions(AdvancedTechnologyAttachment *hd) {
  MBR mbr;
  hd->Read28(0, (uint8_t*)&mbr, sizeof(MBR));

  printf("MBR: ");
  /**
  for (int i = 446; i < 446 + 4*16; i++) {
    printfHex(((uint8_t*)&mbr)[i]);
    printf(" ");
  }
  printf("\n");
  */
  if (mbr.magicNumber != 0xAA55) {
    printf("illegal MBR");
    return;
  }

  for (int i = 0; i < 4; i++) {
    if (mbr.primaryPartition[i].partitionId == 0x00)
      continue;

    printf(" Partition: ");
    printfHex(i & 0xFF);

    if (mbr.primaryPartition[i].bootable == 0x80)
      printf(" bootable. Type ");
    else
      printf(" not bootable. Type ");

    printfHex(mbr.primaryPartition[i].partitionId);
  
    ReadBiosBlock(hd, mbr.primaryPartition[i].start_lba);
  }
}
