#include <iostream>

/**
 * 题目七：修理牧场（最小花费锯木头）
 *
 * 思路：每次取出当前最短的两段合并，合并代价为两段之和，并把新段放回。
 * 该问题等价于“最优合并/哈夫曼合并”，使用小根堆可在 O(N log N) 内求最小总花费。
 */
namespace
{
void SiftUp(long long *heap, int index)
{
    while (index > 1)
    {
        int parent = index / 2;
        if (heap[parent] <= heap[index])
        {
            break;
        }
        long long tmp = heap[parent];
        heap[parent] = heap[index];
        heap[index] = tmp;
        index = parent;
    }
}

void SiftDown(long long *heap, int heap_size, int index)
{
    while (true)
    {
        int left = index * 2;
        int right = left + 1;
        int smallest = index;

        if (left <= heap_size && heap[left] < heap[smallest])
        {
            smallest = left;
        }
        if (right <= heap_size && heap[right] < heap[smallest])
        {
            smallest = right;
        }

        if (smallest == index)
        {
            break;
        }

        long long tmp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = tmp;
        index = smallest;
    }
}

void HeapPush(long long *heap, int &heap_size, long long value)
{
    heap[++heap_size] = value;
    SiftUp(heap, heap_size);
}

long long HeapPop(long long *heap, int &heap_size)
{
    long long top = heap[1];
    heap[1] = heap[heap_size--];
    if (heap_size > 0)
    {
        SiftDown(heap, heap_size, 1);
    }
    return top;
}
} // namespace

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    if (!(std::cin >> n))
    {
        return 0;
    }

    // 1-indexed 小根堆，最大元素个数不超过 n
    long long *heap = new long long[(n > 0 ? n : 1) + 5];
    int heap_size = 0;

    for (int i = 0; i < n; ++i)
    {
        long long length = 0;
        std::cin >> length;
        HeapPush(heap, heap_size, length);
    }

    // N<=1 时无需合并/锯木，花费为 0
    long long total_cost = 0;
    while (heap_size > 1)
    {
        long long a = HeapPop(heap, heap_size);
        long long b = HeapPop(heap, heap_size);

        long long merged = a + b;
        total_cost += merged;
        HeapPush(heap, heap_size, merged);
    }

    std::cout << total_cost << "\n";
    delete[] heap;
    return 0;
}
