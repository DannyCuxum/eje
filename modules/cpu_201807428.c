#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>	
#include <linux/seq_file.h>
#include <linux/hugetlb.h> 
#include <linux/sched/signal.h> /* for_each_process() */


//#define modulo_cpu "cpu_201807428"
#define PROC_ENTRY_FILENAME "cpu_201807428"
/*DOCUMENTACION DEL MODULO*/
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Módulo para obtener información del CPU.");
MODULE_AUTHOR("Wilson Kevin Javier Chávez Cabrera");

struct task_struct *task, *task_child;
struct list_head *list;
int cont;
int cont2;
//para estados
long int running = 0, sleeping = 0, stopped = 0, zombie = 0;
long task_mem;

static int listar_procesos(struct seq_file *m, void *v) {
    long int running = 0, sleeping = 0, stopped = 0, zombie = 0;
    long task_mem;

    seq_printf(m, "{\"Cpu\": %d,", 100 - 50);
    seq_printf(m, "\"Tasks\": [\n");



    /*
    unsigned long long total_time=0;
    unsigned long long uptime = 0;
    unsigned long long stime = 0;*/


    for_each_process(task) {
        //unsigned lon long utime=procesos->utime;
        if(task->mm) {
            task_mem = get_mm_rss(task->mm);
        }else{
            task_mem=0;
        }
        if (cont2 == 0){
            cont2 = 1;
        }else{
            seq_printf(m, ",");
        }
        if(task->__state == 0){
            running++;
        }else if(task->__state == 1){
            sleeping++;
        }else if(task->__state == 128){
            stopped++;
        }else if(task->__state == 260){
            zombie++;
        }

        seq_printf(m, "\n{ \"Pid\" : %d, \"Name\" : \"%s\", \"State\" : %ld , \"User\" : %i, \"Mem\"  : %ld,", task->pid, task->comm, task->__state, task->cred->uid.val, task_mem);
        seq_printf(m, "\"Child\" : [");
        cont = 0;

        list_for_each(list, &(task->children)) {
             if (cont == 0){
                cont = 1;
            }else{
                seq_printf(m, ",");
            }

            task_child= list_entry(list, struct task_struct, sibling);
            seq_printf(m, "\n{ \"Pid\" : %d, \"Name\" : \"%s\", \"Ppid\" : %d}", task_child->pid, task_child->comm, task->pid);
            if(task_child->__state == 0){
                running++;
            }else if(task_child->__state == 1){
                sleeping++;
            }else if(task_child->__state == 128){
                stopped++;
            }else if(task_child->__state == 260){
                zombie++;
            }

        }

        cont = 0;
        seq_printf(m, "]\n}\n");
    }
    seq_printf(m, "\n],\n");
    //Aqui empiezan los estados

    seq_printf(m,"\"Running\": %li, \"Sleeping\": %li, \"Stopped\": %li, \"Zombie\":%li", running, sleeping, stopped, zombie);
    seq_printf(m, "}\n");


    return 0;
}

static int al_abrir(struct inode *inode, struct file *file) {
    return single_open(file,listar_procesos,NULL);
}

static struct proc_ops ops= {
    .proc_open= al_abrir,
    .proc_read= seq_read 
};

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
