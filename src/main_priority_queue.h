#ifndef MAIN_PRIORITY_QUEUE_H
#define MAIN_PRIORITY_QUEUE_H

void main_priority_queue_test();

/**
 * 取走最大堆的第一个数
 */
int main_max_priority_queue_take(int *ptr, int *n);

/**
 * 增大最大优先级队列的一个元素的权重值
 */
void main_max_priority_queue_increase_key(int *ptr, int n, int i, int newKey);

/**
 * 优先级队列增加一个元素
 * [ptr必须大到足够容纳增加的元素]
 */
void main_max_priority_queue_insert(int *ptr, int *n, int v);

/**
 * 获取最小优先级队列的第一个值
 */
int main_min_priority_queue_take(int *ptr, int *n);

/**
 * 减小一个最小优先级队列的元素的权值
 */
void main_min_priority_queue_decrease_key(int *ptr, int n, int i, int new_key);

void main_min_priority_queue_insert(int *ptr, int *n, int v);

#endif // MAIN_PRIORITY_QUEUE_H
