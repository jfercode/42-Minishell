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
- **`rl_replace_line(const char *text, int clear_undo)`**: Reemplaza el contenido actual de la línea por `text`.
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

- **`malloc(size_t size)`***: Reserva `size` bytes de memoria y devuelve un puntero al bloque reservado.
- **`free(void *ptr)`**: Libera el bloque de memoria reservado previamente por `malloc`.

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

- **`write`**(int fd, const void *buf, size_t count): Escribe `count` bytes desde `buf` hacia el descriptor de archivo `fd`.

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
- **`read(int fd, void *buf, size_t count)`**: Lee `count` bytes del descriptor de archivo `fd` en `buf`.
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
- **`fork()`**: Crea un nuevo proceso `(hijo)` duplicando el proceso actual.
```sh
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();

    if (pid == 0)
        printf("Children process (PID: %d)\n", getpid());
    else
        printf("Parent process(PID: %d)\n", getpid());

    return 0;
}
```

- **`wait(int *status)`**: Espera a que termine un proceso hijo.
- **`waitpid(pid_t pid, int *status, int options)`**: Espera de forma selectiva por un proceso hijo específico.
- **`wait3(int *status, int options, struct rusage *rusage) / wait4(pid_t pid, int *status, int options, struct rusage *rusage)`**: Variantes de waitpid con información de uso de recursos.
```sh
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    if (fork() == 0) {
        printf("Executing children process...\n");
    } else {
        wait(NULL);
        printf("Children process finished.\n");
    }
    return 0;
}
```
- **`execve(const char *pathname, char *const argv[], char *const envp[])`**: Reemplaza el proceso actual con uno nuevo.
```sh
#include <unistd.h>
#include <stdio.h>

int main() {
    char *args[] = {"/bin/ls", "-l", NULL};
    execve("/bin/ls", args, NULL);
    perror("execve failed");
    return 1;
}
```
- **`exit(int status)`**: Termina el proceso actual devolviendo status al sistema operativo.


### 6. Señales 🚦
- **`signal(int signum, void (*handler)(int))`**: Establece un manejador para una señal específica.
- **`sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)`**: Configura el comportamiento detallado para señales.

```sh
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig) 
{
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

int main() 
{
    pid_t pid = getpid();
    printf("Sending SIGTERM to process (%d)...\n", pid);
    kill(pid, SIGTERM);
    return 0;
}
```
### 7. Directorios 📁
- **`getcwd(char *buf, size_t size)`**: Obtiene el directorio de trabajo actual.

```c
#include <unistd.h>
#include <stdio.h>

int main() 
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)))
        printf("Actual directory: %s\n", cwd);
    return 0;
}
```
- **`chdir(const char *path)`**: Cambia el directorio de trabajo actual.
opendir(const char *name): Abre un directorio y devuelve un puntero al mismo.
- **`readdir(DIR *dirp)`**: Lee la siguiente entrada de un directorio abierto.
- **`closedir(DIR *dirp)`**: Cierra un directorio abierto.
```c
#include <unistd.h>
#include <stdio.h>

int main() 
{
    chdir("..");
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("New actual directory: %s\n", cwd);
    return 0;
}
```

### 8. Información de Archivos 🗃️
- **`stat(const char *path, struct stat *buf)`**: Obtiene información del archivo.
- **`lstat(const char *path, struct stat *buf)`**: Igual que `stat`, pero sigue enlaces simbólicos.
- **`fstat(int fd, struct stat *buf)`**: Obtiene información del archivo usando su descriptor de archivo.
```c
#include <sys/stat.h>
#include <stdio.h>

int main() 
{
    struct stat info;
    if (stat("File.txt", &info) == 0)
        printf("Size: %ld bytes\n", info.st_size);
    else
        perror("stat");
    return 0;
}
```

### 9. Manejo de Errores ⚠️
- **`strerror(int errnum)`**: Devuelve una cadena descriptiva del error asociado con `errnum`.
- **`perror(const char *s)`**: Imprime un mensaje de error en la salida estándar de errores.

```c
#include <stdio.h>

int main() {
    FILE *f = open("not_found.txt", R_ONLY);
    if (!f)
        perror("Error: Cannot open file");
    return 0;
}
```

### 10. Duplicación de Descriptores de Archivo 🔗
- **`dup(int oldfd)`**: Duplica un descriptor de archivo.
- **`dup2(int oldfd, int newfd)`**: Duplica `oldfd` en `newfd`, cerrando `newfd` si está abierto.
```c
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() 
{
    int fd = open("out.txt", O_WRONLY | O_CREAT, 0644);
    dup2(fd, STDOUT_FILENO);
    printf("Text redirected to 'out.txt'\n");
    close(fd);
    return 0;
}
```

### 11. Terminal y TTY 📞
- **`isatty(int fd)`**: Verifica si un descriptor de archivo es un terminal.
- **`ttyname(int fd)`**: Devuelve el nombre del terminal asociado al descriptor `fd`.
- **`ttyslot()`**: Devuelve el número de terminal de la sesión actual.
ioctl(int fd, unsigned long request, ...): Controla dispositivos I/O.
### 12. Variables de Entorno 🌍
- **`getenv(const char *name)`**: Obtiene el valor de una variable de entorno.
### 13. Configuración de la Terminal (termcap/terminfo) 🎛️
- **`tcsetattr(int fd, int optional_actions, const struct termios *termios_p)`**: Configura los atributos de la terminal.
- **`tcgetattr(int fd, struct termios *termios_p)`**: Obtiene los atributos de la terminal.
- **`tgetent(char *bp, const char *name)`**: Inicializa la base de datos de capacidades de la terminal.
- **`tgetflag(char *id)`**, **`tgetnum(char *id)`**, **`tgetstr(char *id, char **area)`**: Obtienen diferentes tipos de capacidades de la terminal.
- **`tgoto(const char *cap, int col, int row)`**: Calcula la secuencia de control para moverse en la terminal.
- **`tputs(const char *str, int affcnt, int (*putc)(int))`**: Imprime cadenas de control en la terminal.