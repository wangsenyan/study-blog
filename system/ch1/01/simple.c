#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
int simple_init(void)
{
  struct task_struct *task;
  for_each_process(task)
      printf("I found task:%d\n", task->pid);

  printk(KERN_INFO "loding Module\n");
  return 0;
}
void simple_exit(void)
{
  printk(KERN_INFO "Removing Module\n");
}
module_init(simple_init);
module_exit(simple_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("simple module");
MODULE_AUTHOR("SGG");