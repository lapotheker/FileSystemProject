#include "vcb.h"
#include <stdio.h>
#include <stdint.h>

// Initializes the file system's VCB, writes it to disk, and reads it back for validation
int initFileSystem(uint64_t numberOfBlocks, uint64_t blockSize) {
    printf("Initializing Volume Control Block (VCB) for the file system...\n");

    // Initialize a new VCB
    VCB* vcb = initializeVCB(numberOfBlocks, blockSize);
    if (vcb == NULL) {
        printf("VCB initialization failed.\n");
        return -1;
    }

    // Write the VCB to disk
    if (writeVCBToDisk(vcb) != 0) {
        printf("Error: Failed to write VCB to disk\n");
        free(vcb);
        return -1;
    }
    printf("VCB successfully written to disk.\n");

    // Attempt to read the VCB back from disk to verify it was written correctly
    VCB vcbRead;
    if (readVCBFromDisk(&vcbRead) != 0) {
        printf("Error: Failed to read VCB from disk\n");
        free(vcb);
        return -1;
    }

    // Display key information to verify VCB data integrity
    printf("Verified VCB from disk:\n");
    printf("Magic Number: 0x%lX\n", vcbRead.magicNumber);
    printf("Volume Size: %lu bytes\n", vcbRead.volumeSize);
    printf("Free Space Start Block: %lu\n", vcbRead.freeSpaceStart);
    printf("Root Directory Start Block: %lu\n", vcbRead.rootDirectoryStart);
    printf("Creation Time: %s", ctime(&vcbRead.creationTime));

    // Free the allocated memory for the VCB
    free(vcb);

    printf("VCB initialization and verification completed successfully.\n");
    return 0;
}
