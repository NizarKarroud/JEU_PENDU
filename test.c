// rainbow.c
// Compile: gcc -O2 -o rainbow rainbow.c
// On Windows (MSVC): cl /EHsc rainbow.c

#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
static void enable_virtual_terminal_processing(void) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#else
static void enable_virtual_terminal_processing(void) { /* nothing needed on POSIX */ }
#endif

int main(void) {
    enable_virtual_terminal_processing();

    // ANSI color codes (you can swap or add bright variants if you like)
    const char *colors[] = {
        "\x1b[91m", // bright red
        "\x1b[93m", // bright yellow
        "\x1b[92m", // bright green
        "\x1b[96m", // bright cyan
        "\x1b[94m", // bright blue
        "\x1b[95m"  // bright magenta
    };
    const int ncolors = sizeof(colors)/sizeof(colors[0]);
    const char *reset = "\x1b[0m";

    // Your ASCII art lines
    const char *art[] = {
"     ██╗███████╗██╗   ██╗    ██████╗ ██╗   ██╗    ██████╗ ███████╗███╗   ██╗██████╗ ██╗   ██╗",
"     ██║██╔════╝██║   ██║    ██╔══██╗██║   ██║    ██╔══██╗██╔════╝████╗  ██║██╔══██╗██║   ██║",
"     ██║█████╗  ██║   ██║    ██║  ██║██║   ██║    ██████╔╝█████╗  ██╔██╗ ██║██║  ██║██║   ██║",
"██   ██║██╔══╝  ██║   ██║    ██║  ██║██║   ██║    ██╔═══╝ ██╔══╝  ██║╚██╗██║██║  ██║██║   ██║",
"╚█████╔╝███████╗╚██████╔╝    ██████╔╝╚██████╔╝    ██║     ███████╗██║ ╚████║██████╔╝╚██████╔╝",
" ╚════╝ ╚══════╝ ╚═════╝     ╚═════╝  ╚═════╝     ╚═╝     ╚══════╝╚═╝  ╚═══╝╚═════╝  ╚═════╝ "
    };
    const int lines = sizeof(art)/sizeof(art[0]);

    for (int r = 0; r < lines; ++r) {
        const char *line = art[r];
        size_t len = strlen(line);
        for (size_t c = 0; c < len; ++c) {
            char ch = line[c];
            if (ch == ' ' || ch == '\t') {
                putchar(ch); // keep whitespace uncolored
            } else {
                // color choice: spread colors horizontally and down each line
                int color_index = (int)((c + r*3) % ncolors);
                fputs(colors[color_index], stdout);
                putchar(ch);
                fputs(reset, stdout);
            }
        }
        putchar('\n');
    }

    return 0;
}







// #include <stdio.h>

// int main(void) {
//     const char *art[] = {
// "     ▄█    ▄████████ ███    █▄       ████████▄  ███    █▄          ▄███████▄    ▄████████ ███▄▄▄▄   ████████▄  ███    █▄  ",
// "    ███   ███    ███ ███    ███      ███   ▀███ ███    ███        ███    ███   ███    ███ ███▀▀▀██▄ ███   ▀███ ███    ███ ",
// "    ███   ███    █▀  ███    ███      ███    ███ ███    ███        ███    ███   ███    █▀  ███   ███ ███    ███ ███    ███ ",
// "    ███  ▄███▄▄▄     ███    ███      ███    ███ ███    ███        ███    ███  ▄███▄▄▄     ███   ███ ███    ███ ███    ███ ",
// "    ███ ▀▀███▀▀▀     ███    ███      ███    ███ ███    ███      ▀█████████▀  ▀▀███▀▀▀     ███   ███ ███    ███ ███    ███ ",
// "    ███   ███    █▄  ███    ███      ███    ███ ███    ███        ███          ███    █▄  ███   ███ ███    ███ ███    ███ ",
// "    ███   ███    ███ ███    ███      ███   ▄███ ███    ███        ███          ███    ███ ███   ███ ███   ▄███ ███    ███ ",
// "█▄ ▄███   ██████████ ████████▀       ████████▀  ████████▀        ▄████▀        ██████████  ▀█   █▀  ████████▀  ████████▀  ",
// "▀▀▀▀▀▀                                                                                                                     "
//     };
//     int lines = sizeof(art) / sizeof(art[0]);

//     for (int i = 0; i < lines; i++) {
//         puts(art[i]);
//     }

//     return 0;
// }
