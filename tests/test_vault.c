#include "vault.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int check(int ok, const char *what)
{
    if (!ok)
        fprintf(stderr, "FAILED: %s\n", what);
    return ok ? 0 : 1;
}

/* A fresh, short temporary folder for each test. */
static char *temp_root(void)
{
    static char root[] = "/tmp/vaultXXXXXX";
    return mkdtemp(root);
}

int main(int argc, char **argv)
{
    const char *which = argc > 1 ? argv[1] : "";
    if (strcmp(which, "roundtrip") == 0) {
        char *root = temp_root();
        char out[64];
        if (!root || vault_store(root, "note.txt", "hello vault") != 0)
            return check(0, "store");
        return check(vault_read(root, "note.txt", out, sizeof out) == 11 && strcmp(out, "hello vault") == 0,
                     "stored file reads back");
    }
    if (strcmp(which, "missing") == 0) {
        char *root = temp_root();
        char out[16];
        return check(root && vault_read(root, "nope.txt", out, sizeof out) == -1, "missing file is an error");
    }
    if (strcmp(which, "path") == 0) {
        char out[VAULT_PATH_MAX];
        return check(vault_path(out, "/data", "a.txt") == 0 && strcmp(out, "/data/a.txt") == 0, "path joined");
    }
    if (strcmp(which, "size") == 0) {
        char *root = temp_root();
        if (!root || vault_store(root, "five.txt", "12345") != 0)
            return check(0, "store");
        return check(vault_size(root, "five.txt") == 5, "size measured");
    }
    fprintf(stderr, "unknown test %s\n", which);
    return 2;
}
