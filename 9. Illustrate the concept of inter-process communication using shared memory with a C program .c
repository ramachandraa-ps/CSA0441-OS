#include <windows.h>
#include <stdio.h>
#include <string.h>

#define SHM_SIZE 1024  // Size of the shared memory segment

int main() {
    // Create a named shared memory segment
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // Use system paging file
        NULL,                    // Default security attributes
        PAGE_READWRITE,          // Read/write access
        0,                       // Maximum object size (high-order DWORD)
        SHM_SIZE,                // Maximum object size (low-order DWORD)
        "MySharedMemory");       // Name of the shared memory segment

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%d).\n", GetLastError());
        return 1;
    }

    // Map the shared memory into the process's address space
    char *shm_ptr = (char *)MapViewOfFile(
        hMapFile,            // Handle to the file mapping object
        FILE_MAP_ALL_ACCESS, // Read/write access
        0,                   // File offset (high-order DWORD)
        0,                   // File offset (low-order DWORD)
        SHM_SIZE);           // Number of bytes to map

    if (shm_ptr == NULL) {
        printf("Could not map view of file (%d).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Write data to the shared memory
    strcpy(shm_ptr, "Hello, shared memory!");
    printf("Data written to shared memory: %s\n", shm_ptr);

    // Unmap the shared memory
    if (!UnmapViewOfFile(shm_ptr)) {
        printf("Could not unmap view of file (%d).\n", GetLastError());
    }

    // Close the handle to the file mapping object
    CloseHandle(hMapFile);

    return 0;
}
