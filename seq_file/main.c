#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include "logic.h" /* Use quotes for local header */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aligator");
MODULE_DESCRIPTION("fruit_basket");

static int __init fruit_init(void)
{
    struct proc_dir_entry *entry;

    /* We use &my_ops from logic.c */
    entry = proc_create("fruit", 0, NULL, &my_ops);

    if (entry == NULL) {
        return -ENOMEM;
    }

    pr_info("Fruit Module Loaded.\n");
    return 0;
}

static void __exit fruit_exit(void)
{
    remove_proc_entry("fruit", NULL);
    pr_info("Fruit Module Unloaded.\n");
}

module_init(fruit_init);
module_exit(fruit_exit);