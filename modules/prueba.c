#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>	
#include <linux/seq_file.h>
#include <linux/hugetlb.h>
#include <linux/sched/signal.h> 

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Módulo para obtener información del CPU.");
MODULE_AUTHOR("Wilson Kevin Javier Chávez Cabrera");

#define PROC_ENTRY_FILENAME "cpu_201807428"
#define FILENAME "/proc/stat"

static int write_file(struct seq_file *archivo, void *v)
{
    struct task_struct *task, *task_child;
    struct list_head *list;
    long int running = 0, sleeping = 0, stopped = 0, zombie = 0;
    long task_mem;
    bool first = true, first_child = true;
    struct file *file;
    char buffer[256];
    int len, idle_percentage;
    long user, nice, system, idle, iowait, irq, softirq;
    struct sysinfo sys_info;

    // Obtener la memoria RAM total
    si_meminfo(&sys_info);

    // Obtener datos del CPU
    file = filp_open(FILENAME, O_RDONLY, 0);
    if (IS_ERR(file))
    {
        printk(KERN_ERR "Error al abrir el archivo: %s", FILENAME);
    }

    len = kernel_read(file, buffer, sizeof(buffer), 0);
    if (len < 0)
    {
        printk(KERN_ERR "Error al leer el archivo: %s", FILENAME);
    }

    filp_close(file, NULL);
    sscanf(buffer, "cpu %ld %ld %ld %ld %ld %ld %ld", &user, &nice, &system, &idle, &iowait, &irq, &softirq);

    // Calcular el porcentaje de tiempo de inactividad del CPU
    idle_percentage = 100 * idle / (user + nice + system + idle + iowait + irq + softirq);

    // Iniciar JSON de la CPU
    seq_printf(archivo, "{\"Cpu\": %d,", 100 - idle_percentage);
    seq_printf(archivo, "\"Tasks\": [");

    for_each_process(task)
    {
        // Si no es el primer proceso, agregar coma
        (first) ? first = false : seq_printf(archivo, ",");

        // Capturar el estado del proceso
        if (task->__state == 0)
            running++;
        else if (task->__state == 1)
            sleeping++;
        else if (task->__state == 128)
            stopped++;
        else if (task->__state == 260)
            zombie++;

        // Capturar la memoria del proceso
        task_mem = (task->mm) ? get_mm_rss(task->mm) : 0;

        // Iniciar JSON del proceso
        seq_printf(archivo, "{\"Pid\": %d,", task->pid);
        seq_printf(archivo, "\"Name\": \"%s\",", task->comm);
        seq_printf(archivo, "\"State\": %u,", task->__state);
        seq_printf(archivo, "\"User\": %i,", task->cred->uid.val);
        seq_printf(archivo, "\"Mem\": %ld,", (task_mem * 100) / sys_info.totalram);
        seq_printf(archivo, "\"Child\": [");

        // Recorrer los hijos del proceso
        list_for_each(list, &(task->children))
        {
            // Si no es el primer hijo, agregar coma
            (first_child) ? first_child = false : seq_printf(archivo, ",");

            // Obtener el hijo
            task_child = list_entry(list, struct task_struct, sibling);

            // Capturar el estado del hijo
            if (task_child->__state == 0)
                running++;
            else if (task_child->__state == 1)
                sleeping++;
            else if (task_child->__state == 128)
                stopped++;
            else if (task_child->__state == 260)
                zombie++;

            // Capturar la memoria del hijo
            task_mem = (task_child->mm) ? get_mm_rss(task->mm) : 0;

            // JSON del hijo
            seq_printf(archivo, "{\"Pid\": %d,", task_child->pid);
            seq_printf(archivo, "\"Name\": \"%s\",", task_child->comm);
            seq_printf(archivo, "\"Ppid\": %i}", task->pid);
        }

        // Reiniciar el primer hijo
        first_child = true;

        // Cerar JSON del proceso
        seq_printf(archivo, "]}");
    }

    // JSON de los estados
    seq_printf(archivo, "],\"Running\": %ld,", running);
    seq_printf(archivo, "\"Sleeping\": %ld,", sleeping);
    seq_printf(archivo, "\"Stopped\": %ld,", stopped);
    seq_printf(archivo, "\"Zombie\": %ld,", zombie);
    seq_printf(archivo, "\"Total\": %ld}", running + sleeping + stopped + zombie);

    return 0;
}

static int open_file(struct inode *inode, struct file *file)
{
    return single_open(file, write_file, NULL);
}

static struct proc_ops ops = {
    .proc_open = open_file,
    .proc_read = seq_read};

static int __init _insert(void)
{
    printk(KERN_INFO "NOMBRE: Wilson Kevin Javier Chavez Cabrera\n");
    proc_create(PROC_ENTRY_FILENAME, 0, NULL, &ops);
    return 0;
}

static void __exit _remove(void)
{
    printk(KERN_INFO "MENSAJE: Primer Semestre 2023\n");
    remove_proc_entry(PROC_ENTRY_FILENAME, NULL);
}

module_init(_insert);
module_exit(_remove);