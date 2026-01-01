#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include "logic.h" 

static char *fruit_basket[] = {
    "Apple",
    "Banana",
    "Orange",
    "Grapes",
    "Mango",
};

static int fruit_count = 5;    

/* 1. START */
/* Changed return type to void* to match kernel signature */
static void *fruit_start(struct seq_file *s, loff_t *pos) {
    int *index = kmalloc(sizeof(int), GFP_KERNEL);

    if (!index) return NULL; /* Safety check */

    *index = (int)(*pos);

    /* If we start past the end, clean up immediately */
    if (*index >= fruit_count) {
        kfree(index);
        return NULL;
    }   
    return index;
}

/* 2. NEXT */
static void *fruit_next(struct seq_file *s, void *v, loff_t *pos) {
    int *index = (int *)v;
    
    (*pos)++;   // Update Kernel Cursor
    (*index)++; // Update Our Tracker

    /* FIX: Do NOT kfree here. Just return NULL. Stop() handles the free. */
    if (*index >= fruit_count) {
        return NULL;
    }
    return index;
}

/* 3. SHOW */
static int fruit_show(struct seq_file *s, void *v) {
    int *index = (int *)v;
    /* Added \n so it prints cleanly */
    seq_printf(s, "%d: %s\n", *index, fruit_basket[*index]);
    return 0;
}

/* 4. STOP */
static void fruit_stop(struct seq_file *s, void *v) {
    if (v) {
        kfree(v); /* The only place we free! */
    }
}

/* Menu for seq_file */
/* FIX: Correct struct name is seq_operations */
static const struct seq_operations fruit_seq = {
    .start = fruit_start,
    .stop  = fruit_stop,
    .next  = fruit_next,
    .show  = fruit_show,
};

/* Open wrapper */
static int my_open(struct inode *inode, struct file *file) {
    return seq_open(file, &fruit_seq);
}

/* FIX: Removed 'static' so main.c can see this */
/* FIX: Added const */
const struct proc_ops my_ops = {
    .proc_open    = my_open,
    .proc_read    = seq_read,
    .proc_lseek   = seq_lseek,
    .proc_release = seq_release,
};