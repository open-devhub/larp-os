#include <time.h> // time()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// windows doesn't have unistd.h
#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#else
#include <unistd.h> // access()
#endif

#include <vfs.h>
#include <split_string.h>


uint32_t __device_not_readable(struct VFSNode *node, void *buff, uint32_t size) {
    return -1;
}

uint32_t __device_not_writable(struct VFSNode *node, const void *buff, uint32_t size) {
    return -1;
}

// this function will be moved into a different file
uint32_t __random_read(struct VFSNode *node, void *buff, uint32_t size) {
    uint8_t *ret = malloc(size);

    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        ret[i] = (rand() % 256);
    }

    memcpy(buff, ret, size);
    free(ret);

    return size;
}

uint32_t __zero_read(struct VFSNode *node, void *buff, uint32_t size) {
    memset(buff, 0, size);
    return size;
}

uint32_t __null_write(struct VFSNode *node, const void *buff, uint32_t size) {
    return size;
}

uint32_t __file_read(struct VFSNode *node, void *buff, uint32_t size) {
    return fread(buff, size, 1, node->__data);
}

uint32_t __file_write(struct VFSNode *node, const void *buff, uint32_t size) {
    return fwrite(buff, size, 1, node->__data);
}

VFSNode *vfs_open(char *path, enum vfs_file_mode mode) {
    char tokens[16][64];
    int depth = split_string(path, '/', 16, 64, tokens);

    if (depth == 0) return NULL;
    VFSNode *node = malloc(sizeof(VFSNode));

    char full_path[VFS_MAX_PATH] = "./rootfs";
    strcat(full_path, path);

    if (access(full_path, F_OK)) {
        // entry doesnt exist
        free(node);
        return NULL;
    }

    node->path = strdup(path);
    if (!strcmp(tokens[1], "dev")) {
        node->type = VFS_CHAR_DEV;
        node->__data = NULL;
            
        if (!strcmp(tokens[2], "random")) {
            node->write = __device_not_writable;
            node->read = __random_read;
        } else if (!strcmp(tokens[2], "zero")) {
            node->write = __device_not_writable;
            node->read = __zero_read;
        } else if (!strcmp(tokens[2], "null")) {
            node->write = __null_write;
            node->read = __device_not_readable;
        }
    } else {
        // normal file

        FILE *file;
        if (mode == VFS_MODE_READ || mode == 0) {
            file = fopen(full_path, "rb");
        } else if (mode == VFS_MODE_WRITE) {
            file = fopen(full_path, "wb+");
        }

        node->__data = file;
        node->type = VFS_FILE;
        node->read = __file_read;
        node->write = __file_write;
    }


    return node;
}

void vfs_close(VFSNode *node) {
    if (node->__data != NULL) {
        fclose(node->__data);
    }

    free(node->path);
    free(node);
}

uint32_t vfs_read(struct VFSNode *node, void *buff, uint32_t size) {
    return node->read(node, buff, size);
}

uint32_t vfs_write(struct VFSNode *node, const void *buff, uint32_t size) {
    return node->write(node, buff, size);
}
