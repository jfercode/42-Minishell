# 42-Minishell

## Funciones

### 1. Manejo de entrada de usuario (<readline/readline.h>) 📚

- **`readline(const char *prompt)`**: Lee una línea desde la entrada estándar con una interfaz interactiva (permite edición de línea, historial, etc.).

```sh
#include <stdio.h>
#include <readline/readline.h>
int main() {
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

int main() {
    char *input = readline("Historial> ");
    if (input) {
        add_history(input);
        printf("Añadido al historial: %s\n", input);
        free(input);
    }
    return 0;
}
```

- **`rl_clear_history()`**: Limpia el historial de comandos almacenado en la sesión actual.

```sh
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    add_history("comando1");
    add_history("comando2");
    printf("Historial añadido.\n");

    rl_clear_history();
    printf("Historial limpiado.\n");

    return 0;
}
```

- **`rl_on_new_line()`**: Informa a readline que se ha iniciado una nueva línea.
- **`rl_replace_line(const char *text, int clear_undo)`**: Reemplaza el contenido actual de la línea por text.
- **`rl_redisplay()`**: Vuelve a mostrar la línea actual en el terminal.

```sh
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    rl_on_new_line();
    rl_replace_line("Texto reemplazado", 0);
    rl_redisplay();
    return 0;
}
```