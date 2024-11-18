#include <windows.h>
#include <stdio.h>
#include <string.h>

#define PIPE_NAME "\\\\.\\pipe\\MessageQueuePipe"
#define BUFFER_SIZE 1024

int main() {
    // Create a named pipe
    HANDLE hPipe = CreateNamedPipe(
        PIPE_NAME,              // Name of the pipe
        PIPE_ACCESS_DUPLEX,     // Read/write access
        PIPE_TYPE_MESSAGE |     // Message type pipe
        PIPE_READMODE_MESSAGE | // Message-read mode
        PIPE_WAIT,              // Blocking mode
        1,                      // Max. instances
        BUFFER_SIZE,            // Output buffer size
        BUFFER_SIZE,            // Input buffer size
        0,                      // Default timeout
        NULL                    // Default security attributes
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Failed to create named pipe. Error: %ld\n", GetLastError());
        return 1;
    }

    printf("Waiting for client connection...\n");

    // Wait for a client to connect
    BOOL isConnected = ConnectNamedPipe(hPipe, NULL) ?
                       TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

    if (!isConnected) {
        printf("Failed to connect to the client. Error: %ld\n", GetLastError());
        CloseHandle(hPipe);
        return 1;
    }

    printf("Client connected.\n");

    // Producer: Write a message to the named pipe
    const char* message = "Hello, message queue!";
    DWORD bytesWritten;

    BOOL isWritten = WriteFile(
        hPipe,          // Handle to the pipe
        message,        // Message to be written
        strlen(message) + 1, // Message length (+1 for null terminator)
        &bytesWritten,  // Bytes written
        NULL            // No overlapping
    );

    if (!isWritten) {
        printf("Failed to write to the pipe. Error: %ld\n", GetLastError());
        CloseHandle(hPipe);
        return 1;
    }

    printf("Producer: Data sent to named pipe: %s\n", message);

    // Consumer: Read the message from the named pipe
    char buffer[BUFFER_SIZE] = {0};
    DWORD bytesRead;

    BOOL isRead = ReadFile(
        hPipe,          // Handle to the pipe
        buffer,         // Buffer to receive data
        BUFFER_SIZE,    // Size of buffer
        &bytesRead,     // Bytes read
        NULL            // No overlapping
    );

    if (!isRead) {
        printf("Failed to read from the pipe. Error: %ld\n", GetLastError());
        CloseHandle(hPipe);
        return 1;
    }

    printf("Consumer: Data received from named pipe: %s\n", buffer);

    // Close the named pipe
    CloseHandle(hPipe);
    return 0;
}
