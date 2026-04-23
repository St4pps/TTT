#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket failed");
        exit(1);
    }

    // server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // connect
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connect failed");
        exit(1);
    }

    printf("Connected to server.\n");

    // game loop
    while (1) {

        memset(buffer, 0, BUFFER_SIZE);

        int bytes = read(sock, buffer, BUFFER_SIZE - 1);

        if (bytes <= 0) {
            printf("Server disconnected.\n");
            break;
        }

        // IMPORTANT FIX: null terminate properly
        buffer[bytes] = '\0';

        printf("%s", buffer);

        // only send input when prompted
        if (strstr(buffer, "Enter") != NULL ||
            strstr(buffer, "Invalid") != NULL) {

            printf("Your move: ");

            memset(buffer, 0, BUFFER_SIZE);
            fgets(buffer, BUFFER_SIZE, stdin);

            send(sock, buffer, strlen(buffer), 0);
        }
    }

    close(sock);
    return 0;
}