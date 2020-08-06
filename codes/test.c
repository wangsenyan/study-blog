#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef struct
{
  uint32_t Addr;
  uint32_t Size;
} Partition;

static Partition const BootPartition = {
    .Addr = 0,
    .Size = 14 * 1024};

static Partition const FlagPartition = {
    .Addr = 0, //BootPartition.Addr + BootPartition.Size,
    .Size = 2 * 1024};
