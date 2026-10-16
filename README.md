# file-vault-c

A tiny C file vault: store, read and measure files under a root folder, with a CMake + CTest test suite.

**Demo target for Proof Patch: intentionally contains security bugs. Never deploy this code.**

| Area | Vulnerability | CWE |
|---|---|---|
| `vault_read` / `vault_store` | File name is not checked: `../` escapes the vault folder (path traversal) | CWE-22 |
| `vault_size` | File name is pasted into a shell command run by `popen` (command injection) | CWE-78 |
| `vault_path` | `sprintf` into a fixed 64-byte buffer: long names overflow it | CWE-120 |

Run the tests: `cmake -S . -B build && cmake --build build && ctest --test-dir build`.
