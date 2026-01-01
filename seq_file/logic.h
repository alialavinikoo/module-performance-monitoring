#ifndef LOGIC_H
#define LOGIC_H

#include <linux/proc_fs.h>

/* Tell main.c that this variable exists elsewhere */
extern const struct proc_ops my_ops;

#endif