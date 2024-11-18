#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main() {
    // Open the file foo.txt in read-only mode. If it does not exist, create it.
    int fd = open("foo.txt", O_RDONLY | O_CREAT, 0644);

    // Print the file descriptor
    printf("fd = %d\n", fd);

    // Check if the file descriptor is invalid
    if (fd == -1) {
        // Print the error number and error message
        printf("Error Number: %d\n", errno);
        perror("Program");
        return 1; // Exit with an error code
    }

    // File opened successfully, perform actions here if needed

    // Close the file descriptor
    close(fd);

    return 0; // Successful execution
}
