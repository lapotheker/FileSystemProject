#include "vcb.h"
#include "fsLow.h"  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Initialize the VCB with required metadata
VCB* initializeVCB(uint64_t numberOfBlocks, uint64_t blockSize) {
    VCB* vcb = (VCB*)malloc(blockSize);
    if (vcb == NULL) {
        printf("Error: Could not allocate memory for VCB\n");
        return NULL;
    }

    vcb->magicNumber = MAGIC_NUMBER;
    vcb->volumeSize = numberOfBlocks * blockSize;
    vcb->blockSize = blockSize;
    vcb->totalBlocks = numberOfBlocks;
    vcb->freeSpaceStart = 1;       // Placeholder for the start of free space management
    vcb->rootDirectoryStart = 6;   // Placeholder for the root directory start block
    vcb->creationTime = time(NULL);  // Creation time is set to the current time

    return vcb;
}

// Write the VCB to disk at block 0
int writeVCBToDisk(VCB* vcb) {
    if (LBAwrite(vcb, 1, 0) != 1) {
        printf("Error: Could not write VCB to disk\n");
        return -1;
    }
    return 0;
}

// Read the VCB from disk to verify or retrieve volume information
int readVCBFromDisk(VCB* vcb) {
    if (LBAread(vcb, 1, 0) != 1) {
        printf("Error: Could not read VCB from disk\n");
        return -1;
    }

    // Check the magic number to confirm this is our file system
    if (vcb->magicNumber != MAGIC_NUMBER) {
        printf("Error: Invalid file system detected.\n");
        return -1;
    }
    return 0;
}




