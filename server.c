#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // Linka a biblioteca do Windows

#define PORT 4444  // Porta usada para comunicação

int main() {
    WSADATA wsa;
    SOCKET server, client;
    struct sockaddr_in serverAddr, clientAddr;
    int addrLen = sizeof(clientAddr);
    char buffer[1024];

    WSAStartup(MAKEWORD(2, 2), &wsa); // Inicializa a Winsock
    server = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // Aceita conexões de qualquer IP
    serverAddr.sin_port = htons(PORT);

    bind(server, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(server, 5); // Aguarda conexões

    printf("[+] Aguardando conexões na porta %d...\n", PORT);
    client = accept(server, (struct sockaddr*)&clientAddr, &addrLen);

    printf("[+] Conexão estabelecida!\n");

    FILE *logFile = fopen("log_remoto.txt", "a+");

    while (1) {
        int bytesReceived = recv(client, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived <= 0) break; // Encerra ao receber erro ou desconexão

        buffer[bytesReceived] = '\0'; // Garante que o buffer seja tratado como string
        printf("%s", buffer); // Mostra os logs recebidos
        fprintf(logFile, "%s", buffer);
        fflush(logFile);
    }

    fclose(logFile);
    closesocket(client);
    closesocket(server);
    WSACleanup();

    return 0;
}
