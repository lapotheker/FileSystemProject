#ifndef VCB_H
#define VCB_H

#include <stdint.h>
#include <time.h>

// Magic number for verifying our file system
#define MAGIC_NUMBER 0x444F5348  // "HSOS" in hexadecimal

typedef struct {
    uint64_t magicNumber;          // Identifier for our file system
    uint64_t volumeSize;           // Total size of volume in bytes
    uint64_t blockSize;            // Size of each block in bytes
    uint64_t freeSpaceStart;       // Starting block number of free space bitmap
    uint64_t rootDirectoryStart;   // Starting block number of root directory
    uint64_t totalBlocks;          // Total number of blocks in volume
    time_t creationTime;           // Volume creation timestamp
} VCB;

// Declaring functions to manage the VCB
VCB* initializeVCB(uint64_t numberOfBlocks, uint64_t blockSize);
int writeVCBToDisk(VCB* vcb);
int readVCBFromDisk(VCB* vcb);
