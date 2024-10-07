#include <linux/sched.h>

struct realtime_thread_info_ll {
	uint32_t tid;
	uint32_t pid;
	uint32_t rt_priority;
	char *name;
	struct realtime_thread_info_ll *next;
};

size_t do_rt_threads_info(struct realtime_thread_info_ll *out) {
	struct realtime_thread_info_ll *tmp;
	struct task_struct_task task;
	for_each_process(task) {
		if(task->rt_priority > 0) {
			tmp = kmalloc(sizeof(realtime_thread_info_ll));
			tmp->next = out;
			tmp->tid = task->tgid;
			tmp->pid = task->pid;
			tmp->rt_priority = task->rt_priority;
			task->name = task->comm;
			out = tmp;
		}
	}

}

void do_free_rt_thread_info_struct(struct realtime_thread_info_ll *to_free) {
	struct realtime_thread_info_ll *cur, *old;

	old = to_free;
	cur = to_free;

	while(cur) {
		cur = old->next;
		kfree(old);
		old = cur;
	}

}

size_t do_count_rt_threads() {
	struct task_struct_task task;
	size_t rt_thread_count = 0;

	for_each_process(task) {
		if(task->rt_priority > 0) {
			rt_thread_count++;
		}
	}

	return rt_thread_count;
}
