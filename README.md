# 42-Minishell

## Funciones

### 1. Manejo de entrada de usuario 📚

- **`readline(const char *prompt)`**: Lee una línea desde la entrada estándar con una interfaz interactiva (permite edición de línea, historial, etc.).

```sh
#include <stdio.h>
#include <readline/readline.h>
int main() 
{
    char *input = readline("Write something to display: ");
    printf("Input: %s\n", input);
    free(input);
    return 0;
}
```

- **`add_history(const char *line)`**: Añade la línea leída al historial de comandos.

```sh
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main() 
{
    char *input = readline("History> ");
    if (input) {
        add_history(input);
        printf("Added to history: %s\n", input);
        free(input);
    }
    return 0;
}
```

- **`rl_clear_history()`**: Limpia el historial de comandos almacenado en la sesión actual.

```sh
#include <readline/readline.h>
#include <readline/history.h>

int main() 
{
    add_history("cmd1");
    add_history("cmd2");
    printf("histoy added.\n");

    rl_clear_history();
    printf("history cleaned.\n");

    return 0;
}
```

- **`rl_on_new_line()`**: Informa a readline que se ha iniciado una nueva línea.
- **`rl_replace_line(const char *text, int clear_undo)`**: Reemplaza el contenido actual de la línea por text.
- **`rl_redisplay()`**: Vuelve a mostrar la línea actual en el terminal.

```sh
#include <readline/readline.h>
#include <readline/history.h>

int main() 
{
    rl_on_new_line();
    rl_replace_line("replace text", 0);
    rl_redisplay();
    return 0;
}
```

### 2. Gestión de memoria 🗂️ 

- **`malloc(size_t size)`***: Reserva size bytes de memoria y devuelve un puntero al bloque reservado.
- **`free(void *ptr)`**: Libera el bloque de memoria reservado previamente por malloc.

```sh
#include <stdlib.h>
#include <stdio.h>

int main() 
{
    char *buffer = (char *)malloc(20);
    if (!buffer)
        free(buffer);
    return 0;
}
```

### 3. Salida Estándar 🖨️ 
- **`printf(const char *format, ...)`**: Imprime texto formateado en la salida estándar.

```sh
#include <stdio.h>

int main() 
{
    printf("Hello world with printf!\n");
    return 0;
}
```

- **`write`**(int fd, const void *buf, size_t count): Escribe count bytes desde buf hacia el descriptor de archivo fd.

```sh
#include <unistd.h>

int main() 
{
    write(1, "Hello from write!\n", 18); 
    return 0;
}

```

### 🔐 4. Manejo de Archivos
- **`access(const char *pathname, int mode)`**: Verifica permisos de acceso a un archivo (lectura, escritura, ejecución).

```sh
#include <unistd.h>
#include <stdio.h>

int main() 
{
    if (access("file.txt", F_OK) == 0)
        printf("file exist.\n");
    else
        perror("Error");
    return 0;
}
```
- **`open(const char *pathname, int flags)`**: Abre un archivo y devuelve su descriptor.
- **`read(int fd, void *buf, size_t count)`**: Lee count bytes del descriptor de archivo fd en buf.
- **`close(int fd)`**: Cierra un descriptor de archivo abierto.

```sh
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("file.txt", O_RDONLY);
    if (fd == -1) {
        perror("open error");
        return 1;
    }

    char buffer[100];
    int bytes = read(fd, buffer, 99);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        printf("Buffer: %s\n", buffer);
    }
    close(fd);
    return 0;
}
```
- **`unlink(const char *pathname)`**: Elimina un archivo del sistema de archivos.
### 5. Gestión de procesos 👥
- **`fork()`**: Crea un nuevo proceso (hijo) duplicando el proceso actual.
- **`wait(int *status)`**: Espera a que termine un proceso hijo.
- **`waitpid(pid_t pid, int *status, int options)`**: Espera de forma selectiva por un proceso hijo específico.
wait3(int *status, int options, struct rusage *rusage) / wait4(pid_t pid, int *status, int options, struct rusage *rusage): Variantes de waitpid con información de uso de recursos.
execve(const char *pathname, char *const argv[], char *const envp[]): Reemplaza el proceso actual con uno nuevo.
exit(int status): Termina el proceso actual devolviendo status al sistema operativo.
### 6. Señales 🚦
- **`signal(int signum, void (*handler)(int))`**: Establece un manejador para una señal específica.
- **`sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)`**: Configura el comportamiento detallado para señales.

```sh
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig) {
    printf("Signal %d received!\n", sig);
}

int main() {
    signal(SIGINT, handler);  // Ctrl+C para probar
    while (1) pause();
    return 0;
}
```

- **`kill(pid_t pid, int sig)`**: Envía una señal sig a un proceso pid.
```sh
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = getpid();
    printf("Sending SIGTERM to process (%d)...\n", pid);
    kill(pid, SIGTERM);
    return 0;
}
```

