#include <stdio.h>
#include <stdint.h>
#include "vcb.h"

// Define default values for volume initialization
#define DEFAULT_BLOCK_SIZE 4096
#define DEFAULT_NUM_BLOCKS 19531

int main() {
    const char* volumeName = "MyVolume";
    uint64_t numberOfBlocks = DEFAULT_NUM_BLOCKS;
    uint64_t blockSize = DEFAULT_BLOCK_SIZE;

    // Initialize a new VCB
    printf("Initializing Volume Control Block (VCB)...\n");
    VCB* vcb = initializeVCB(numberOfBlocks, blockSize);
    if (!vcb) {
        printf("VCB initialization failed.\n");
        return -1;
    }

    // Set volume name and display initialization information
    printf("VCB initialized with volume name: %s\n", volumeName);
    printf("Total Blocks: %lu, Block Size: %lu\n", vcb->totalBlocks, vcb->blockSize);

    // Write the VCB to disk
    if (writeVCBToDisk(vcb) != 0) {
        printf("Failed to write VCB to disk.\n");
        free(vcb);
        return -1;
    }
    printf("VCB successfully written to disk.\n");

    // Attempt to read the VCB back from disk for verification
    VCB vcbRead;
    if (readVCBFromDisk(&vcbRead) != 0) {
        printf("Failed to read VCB from disk.\n");
        free(vcb);
        return -1;
    }

    // Verify by printing some fields from the read VCB
    printf("Read VCB from disk:\n");
    printf("Magic Number: 0x%lX\n", vcbRead.magicNumber);
    printf("Volume Size: %lu bytes\n", vcbRead.volumeSize);
    printf("Free Space Start Block: %lu\n", vcbRead.freeSpaceStart);
    printf("Root Directory Start Block: %lu\n", vcbRead.rootDirectoryStart);
    printf("Creation Time: %s", ctime(&vcbRead.creationTime));

    // Free allocated memory for the VCB
    free(vcb);

    printf("VCB test completed successfully.\n");
    return 0;
}
