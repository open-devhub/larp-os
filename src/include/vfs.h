#pragma once

#include <stdint.h>

#define VFS_MAX_PATH    256


enum vfs_entry_type {
    VFS_FILE,
    VFS_DIR,
    VFS_CHAR_DEV
};

typedef struct VFSNode {
    char *path;
    enum vfs_entry_type type;

    /*
        If type == VFS_FILE, this will contain the FILE* object of the file
        if not, this will be NULL.
    */
    void *__data;

    uint32_t (*read)(struct VFSNode*, void*, uint32_t);
    uint32_t (*write)(struct VFSNode*, const void*, uint32_t);
} VFSNode;


VFSNode *vfs_open(char *path);
void vfs_close(VFSNode *node);

uint32_t vfs_read(struct VFSNode *node, void *buff, uint32_t size);
uint32_t vfs_write(struct VFSNode *node, const void *buff, uint32_t size);
