#ifndef GDBSTUB_H
#define GDBSTUB_H

#include <stdbool.h>
#include <stddef.h>

#define TARGET_RV32 "riscv:rv32"
#define TARGET_RV64 "riscv:rv64"

typedef enum {
    EVENT_NONE,
    EVENT_CONT,
    EVENT_DETACH,
    EVENT_STEP,
} gdb_event_t;

typedef enum {
    ACT_NONE,
    ACT_RESUME,
    ACT_SHUTDOWN,
} gdb_action_t;

typedef enum {
    BP_SOFTWARE = 0,
    BP_HARDWARE_EXEC = 1,
    BP_HARDWARE_WRITE = 2,
    BP_HARDWARE_READ = 3,
    BP_HARDWARE_READ_WRITE = 4,
} bp_type_t;

struct target_ops {
    gdb_action_t (*cont)(void *args);
    gdb_action_t (*stepi)(void *args);
    int (*read_reg)(void *args, int regno, size_t *value);
    int (*write_reg)(void *args, int regno, size_t value);
    int (*read_mem)(void *args, size_t addr, size_t len, void *val);
    int (*write_mem)(void *args, size_t addr, size_t len, void *val);
    bool (*set_bp)(void *args, size_t addr, bp_type_t type, size_t size);
    bool (*del_bp)(void *args, size_t addr, bp_type_t type, size_t size);
    void (*on_interrupt)(void *args);
};

typedef struct gdbstub_private gdbstub_private_t;

typedef struct {
    char *target_desc;
    int reg_num;
    size_t reg_byte;
} arch_info_t;

typedef struct {
    struct target_ops *ops;
    arch_info_t arch;
    gdbstub_private_t *priv;
} gdbstub_t;

bool gdbstub_init(gdbstub_t *gdbstub,
                  struct target_ops *ops,
                  arch_info_t arch,
                  char *s);
bool gdbstub_run(gdbstub_t *gdbstub, void *args);
void gdbstub_close(gdbstub_t *gdbstub);

#endif
