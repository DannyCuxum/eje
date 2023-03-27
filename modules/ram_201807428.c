#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/seq_file.h>
#include <linux/hugetlb.h> 

#define modulo_ram "ram_201807428"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MOdulo ram");
MODULE_AUTHOR("Wilson Cabrera");


static int escribir_archivo(struct seq_file *archivo, void *v)
{
    struct sysinfo si;
    si_meminfo(&si);
    seq_printf(archivo, "{\"Ram\":\"%d",((si.totalram-si.freeram)*100)/si.totalram);
    seq_printf(archivo, "\"}\n");
    return 0;

}
static int al_abrir(struct inode *inode, struct file *file)
{
    return single_open(file, escribir_archivo, NULL);
}
static struct proc_ops operaciones =
{
    .proc_open = al_abrir,
    .proc_read = seq_read
};

static int _insert(void)
{
    proc_create(modulo_ram, 0, NULL, &operaciones);
    printk(KERN_INFO "Wilson Kevin Javier Chávez Cabrera\n");
    return 0;
}

static void _remove(void)
{
    remove_proc_entry(modulo_ram, NULL);
    printk(KERN_INFO "Primer Semestre 2023 \n");
}

module_init(_insert);
module_exit(_remove);