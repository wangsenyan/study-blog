
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

void dfs(struct task_struct *task)
{
  struct task_struct *child;
  struct list_head *list;
  printk(KERN_INFO "Name: %-20s State: %ld\tProcess ID: %d\n", task->comm, task->state, task->pid);
  list_for_each(list, &task->children)
  {
    child = list_entry(list, struct task_struct, sibling);
    dfs(child);
  }
}

int entryPoint(void)
{

  printk(KERN_INFO "Started listing tasks\n");
  dfs(&init_task);
  printk(KERN_INFO "Stopped listing tasks\n");
  return 0;
}

void exitPoint(void)
{
  printk(KERN_INFO "Removing ListTasksLinear\n");
}

/* Macros for registering module entry and exit points. */
module_init(entryPoint);
module_exit(exitPoint);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LINE");
MODULE_AUTHOR("WSY");