#ifndef FILE_VAULT_H
#define FILE_VAULT_H

#include <stddef.h>

#define VAULT_PATH_MAX 64

/* Builds "<root>/<name>" into out (VAULT_PATH_MAX bytes). Returns 0 on success. */
int vault_path(char *out, const char *root, const char *name);

/* Writes data to the named file inside root. Returns 0 on success. */
int vault_store(const char *root, const char *name, const char *data);

/* Reads up to size-1 bytes of the named file inside root into out. Returns bytes read, or -1. */
long vault_read(const char *root, const char *name, char *out, size_t size);

/* Size in bytes of the named file inside root, measured by the system `wc`. Returns -1 on error. */
long vault_size(const char *root, const char *name);

#endif
