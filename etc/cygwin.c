#include <string.h>

static char rcsid[] = "$Id$";

#ifndef LCCDIR
#define LCCDIR "target/"
#endif

char *suffixes[] = { ".c", ".i", ".dasm", ".o", ".out", 0 };
char inputs[256] = "";
char *cpp[] = { LCCDIR "cpp", "-Ddcpu16", "$1", "$2", "$3", 0 };
char *include[] = { "-Iinclude/dcpu16", 0 };
char *com[] = { LCCDIR "rcc", "$1", "$2", "$3", 0 };
char *as[] = { };
//char *ld[] = { "/bin/ld", "-o", "$3", "$1", "$2", 0 };
char *ld[] = { LCCDIR "assembler", "$3", "$1" };

extern char *concat(char *, char *);

int option(char *arg)
{
    if (strncmp(arg, "-lccdir=", 8) == 0)
    {
        if (strcmp(cpp[0], LCCDIR "cpp") == 0)
            cpp[0] = concat(&arg[8], "/cpp");
        include[0] = concat("-I", concat(&arg[8], "/include"));
    }
    else
    {
        return 0;
    }
    return 1;
}
