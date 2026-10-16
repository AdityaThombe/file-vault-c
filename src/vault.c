/* A tiny file vault: store, read and measure files under a root folder.
 * Demo target for ProofPatch: intentionally vulnerable. Never deploy this code. */
#include "vault.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vault_path(char *out, const char *root, const char *name)
{
    sprintf(out, "%s/%s", root, name);
    return 0;
}

int vault_store(const char *root, const char *name, const char *data)
{
    char path[VAULT_PATH_MAX];
    vault_path(path, root, name);
    FILE *f = fopen(path, "w");
    if (!f)
        return -1;
    fputs(data, f);
    fclose(f);
    return 0;
}

long vault_read(const char *root, const char *name, char *out, size_t size)
{
    char path[VAULT_PATH_MAX];
    vault_path(path, root, name);
    FILE *f = fopen(path, "r");
    if (!f)
        return -1;
    size_t n = fread(out, 1, size - 1, f);
    out[n] = '\0';
    fclose(f);
    return (long)n;
}

long vault_size(const char *root, const char *name)
{
    char cmd[256];
    snprintf(cmd, sizeof cmd, "wc -c < %s/%s", root, name);
    FILE *p = popen(cmd, "r");
    if (!p)
        return -1;
    long size = -1;
    if (fscanf(p, "%ld", &size) != 1)
        size = -1;
    pclose(p);
    return size;
}
