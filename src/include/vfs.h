#pragma once

#include <stdint.h>


enum vfs_entry_type {
    VFS_FILE,
    VFS_DIR,
    VFS_CHAR_DEV
};

typedef struct VFSNode {
    char *name;
    enum vfs_entry_type type;

    uint32_t (*read)(struct VFSNode*, void*, uint32_t);
    uint32_t (*write)(struct VFSNode*, const void*, uint32_t);
} VFSNode;


VFSNode *vfs_open(const char *path);