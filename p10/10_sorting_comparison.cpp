#include <iostream>
#include <cmath>
#include <cstring>

// 题目十：8 种排序算法的比较案例
// 功能：生成随机数组，对不同排序算法进行排序，并统计耗时、比较次数与交换次数。

typedef long clock_t;
extern "C" clock_t clock(void);
static const clock_t kClocksPerSec = 1000000; // Linux/WSL2 常见取值

struct SortStatistics
{
    char algorithm_name[32];
    long long compare_count;
    long long swap_count;
    double time_elapsed_ms;

    SortStatistics()
    {
        algorithm_name[0] = '\0';
        compare_count = 0;
        swap_count = 0;
        time_elapsed_ms = 0.0;
    }
};

static void CopyString(char *dst, const char *src, int dst_size)
{
    if (dst_size <= 0)
    {
        return;
    }
    std::strncpy(dst, src, dst_size - 1);
    dst[dst_size - 1] = '\0';
}

static void ClearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

static void SwapInt(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

static unsigned int NextRand(unsigned int &seed)
{
    seed = seed * 1103515245u + 12345u;
    return (seed / 65536u) % 32768u;
}

static int *GenerateRandomArray(int n)
{
    if (n <= 0)
    {
        return nullptr;
    }

    int *arr = new int[n];
    unsigned int seed = 123456789u;
    for (int i = 0; i < n; ++i)
    {
        unsigned int r1 = NextRand(seed);
        unsigned int r2 = NextRand(seed);
        unsigned int val = (r1 << 15) ^ r2;
        arr[i] = (int)(val % 1000000u);
    }
    return arr;
}

// ==================== 排序算法实现 ====================

static void BubbleSort(int *arr, int n, SortStatistics &stats)
{
    for (int i = 0; i < n - 1; ++i)
    {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j)
        {
            stats.compare_count++;
            if (arr[j] > arr[j + 1])
            {
                SwapInt(arr[j], arr[j + 1]);
                stats.swap_count++;
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

static void SelectionSort(int *arr, int n, SortStatistics &stats)
{
    for (int i = 0; i < n - 1; ++i)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j)
        {
            stats.compare_count++;
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            SwapInt(arr[i], arr[min_idx]);
            stats.swap_count++;
        }
    }
}

static void InsertionSort(int *arr, int n, SortStatistics &stats)
{
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0)
        {
            stats.compare_count++;
            if (arr[j] > key)
            {
                arr[j + 1] = arr[j];
                stats.swap_count++;
                --j;
            }
            else
            {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

static void ShellSort(int *arr, int n, SortStatistics &stats)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; ++i)
        {
            int temp = arr[i];
            int j = i;
            while (j >= gap)
            {
                stats.compare_count++;
                if (arr[j - gap] > temp)
                {
                    arr[j] = arr[j - gap];
                    stats.swap_count++;
                    j -= gap;
                }
                else
                {
                    break;
                }
            }
            arr[j] = temp;
        }
    }
}

static int Partition(int *arr, int low, int high, SortStatistics &stats)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j)
    {
        stats.compare_count++;
        if (arr[j] < pivot)
        {
            ++i;
            if (i != j)
            {
                SwapInt(arr[i], arr[j]);
                stats.swap_count++;
            }
        }
    }
    if (i + 1 != high)
    {
        SwapInt(arr[i + 1], arr[high]);
        stats.swap_count++;
    }
    return i + 1;
}

static void QuickSortRecursive(int *arr, int low, int high, SortStatistics &stats)
{
    if (low < high)
    {
        int p = Partition(arr, low, high, stats);
        QuickSortRecursive(arr, low, p - 1, stats);
        QuickSortRecursive(arr, p + 1, high, stats);
    }
}

static void QuickSort(int *arr, int n, SortStatistics &stats)
{
    if (n > 1)
    {
        QuickSortRecursive(arr, 0, n - 1, stats);
    }
}

static void Heapify(int *arr, int n, int i, SortStatistics &stats)
{
    while (true)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n)
        {
            stats.compare_count++;
            if (arr[left] > arr[largest])
            {
                largest = left;
            }
        }
        if (right < n)
        {
            stats.compare_count++;
            if (arr[right] > arr[largest])
            {
                largest = right;
            }
        }

        if (largest == i)
        {
            return;
        }

        SwapInt(arr[i], arr[largest]);
        stats.swap_count++;
        i = largest;
    }
}

static void HeapSort(int *arr, int n, SortStatistics &stats)
{
    for (int i = n / 2 - 1; i >= 0; --i)
    {
        Heapify(arr, n, i, stats);
    }
    for (int i = n - 1; i > 0; --i)
    {
        SwapInt(arr[0], arr[i]);
        stats.swap_count++;
        Heapify(arr, i, 0, stats);
    }
}

static void Merge(int *arr, int *tmp, int left, int mid, int right, SortStatistics &stats)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        stats.compare_count++;
        if (arr[i] <= arr[j])
        {
            tmp[k++] = arr[i++];
        }
        else
        {
            tmp[k++] = arr[j++];
        }
        stats.swap_count++;
    }
    while (i <= mid)
    {
        tmp[k++] = arr[i++];
        stats.swap_count++;
    }
    while (j <= right)
    {
        tmp[k++] = arr[j++];
        stats.swap_count++;
    }
    for (int t = left; t <= right; ++t)
    {
        arr[t] = tmp[t];
    }
}

static void MergeSortRecursive(int *arr, int *tmp, int left, int right, SortStatistics &stats)
{
    if (left >= right)
    {
        return;
    }
    int mid = left + (right - left) / 2;
    MergeSortRecursive(arr, tmp, left, mid, stats);
    MergeSortRecursive(arr, tmp, mid + 1, right, stats);
    Merge(arr, tmp, left, mid, right, stats);
}

static void MergeSort(int *arr, int n, SortStatistics &stats)
{
    if (n <= 1)
    {
        return;
    }
    int *tmp = new int[n];
    MergeSortRecursive(arr, tmp, 0, n - 1, stats);
    delete[] tmp;
}

static void RadixSort(int *arr, int n, SortStatistics &stats)
{
    if (n <= 1)
    {
        return;
    }

    int max_val = arr[0];
    for (int i = 1; i < n; ++i)
    {
        if (arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }

    int *output = new int[n];
    int count[10];

    for (int exp = 1; max_val / exp > 0; exp *= 10)
    {
        for (int i = 0; i < 10; ++i)
        {
            count[i] = 0;
        }
        for (int i = 0; i < n; ++i)
        {
            int digit = (arr[i] / exp) % 10;
            count[digit]++;
        }
        for (int i = 1; i < 10; ++i)
        {
            count[i] += count[i - 1];
        }
        for (int i = n - 1; i >= 0; --i)
        {
            int digit = (arr[i] / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
            stats.swap_count++;
        }
        for (int i = 0; i < n; ++i)
        {
            arr[i] = output[i];
        }
    }

    delete[] output;
}

// ==================== 驱动与展示 ====================

typedef void (*SortFunc)(int *, int, SortStatistics &);

struct AlgorithmEntry
{
    const char *name;
    SortFunc func;
};

static void ExecuteSort(const int *original, int n, const AlgorithmEntry &algo)
{
    int *data = new int[n];
    for (int i = 0; i < n; ++i)
    {
        data[i] = original[i];
    }

    SortStatistics stats;
    CopyString(stats.algorithm_name, algo.name, (int)sizeof(stats.algorithm_name));

    clock_t start = clock();
    algo.func(data, n, stats);
    clock_t end = clock();

    stats.time_elapsed_ms = (double)(end - start) * 1000.0 / (double)kClocksPerSec;

    std::cout.setf(std::ios::fixed);
    std::cout.precision(3);
    std::cout << stats.algorithm_name << "\t"
              << stats.time_elapsed_ms << " ms\t"
              << stats.compare_count << "\t"
              << stats.swap_count << "\n";

    delete[] data;
}

static void RunPerformanceTest(int n)
{
    if (n <= 0)
    {
        std::cout << "数据规模无效。\n";
        return;
    }

    int *original = GenerateRandomArray(n);
    if (!original)
    {
        std::cout << "生成数据失败。\n";
        return;
    }

    AlgorithmEntry algorithms[] = {
        {"冒泡排序", BubbleSort},
        {"选择排序", SelectionSort},
        {"直接插入排序", InsertionSort},
        {"希尔排序", ShellSort},
        {"快速排序", QuickSort},
        {"堆排序", HeapSort},
        {"归并排序", MergeSort},
        {"基数排序", RadixSort}};

    std::cout << "\n============================================================\n";
    std::cout << "数据规模: " << n << "\n";
    std::cout << "排序算法\t时间\t\t比较次数\t交换次数\n";
    std::cout << "------------------------------------------------------------\n";

    for (int i = 0; i < 8; ++i)
    {
        ExecuteSort(original, n, algorithms[i]);
    }

    std::cout << "============================================================\n";

    delete[] original;
}

static void ShowMenu()
{
    std::cout << "\n**************************************************\n";
    std::cout << "**              排序算法比较                    **\n";
    std::cout << "==================================================\n";
    std::cout << "** 1 ---- 冒泡排序                              **\n";
    std::cout << "** 2 ---- 选择排序                              **\n";
    std::cout << "** 3 ---- 直接插入排序                          **\n";
    std::cout << "** 4 ---- 希尔排序                              **\n";
    std::cout << "** 5 ---- 快速排序                              **\n";
    std::cout << "** 6 ---- 堆排序                                **\n";
    std::cout << "** 7 ---- 归并排序                              **\n";
    std::cout << "** 8 ---- 基数排序                              **\n";
    std::cout << "** 9 ---- 退出程序                              **\n";
    std::cout << "==================================================\n";
}

static void TestSingleAlgorithm(int choice, int n)
{
    if (n <= 0)
    {
        std::cout << "数据规模无效。\n";
        return;
    }

    int *data = GenerateRandomArray(n);
    if (!data)
    {
        std::cout << "生成数据失败。\n";
        return;
    }

    AlgorithmEntry algorithms[] = {
        {"冒泡排序", BubbleSort},
        {"选择排序", SelectionSort},
        {"直接插入排序", InsertionSort},
        {"希尔排序", ShellSort},
        {"快速排序", QuickSort},
        {"堆排序", HeapSort},
        {"归并排序", MergeSort},
        {"基数排序", RadixSort}};

    if (choice < 1 || choice > 8)
    {
        std::cout << "无效的选择。\n";
        delete[] data;
        return;
    }

    SortStatistics stats;
    CopyString(stats.algorithm_name, algorithms[choice - 1].name, (int)sizeof(stats.algorithm_name));

    clock_t start = clock();
    algorithms[choice - 1].func(data, n, stats);
    clock_t end = clock();
    stats.time_elapsed_ms = (double)(end - start) * 1000.0 / (double)kClocksPerSec;

    std::cout.setf(std::ios::fixed);
    std::cout.precision(3);
    std::cout << "\n算法: " << stats.algorithm_name << "\n";
    std::cout << "数据规模: " << n << "\n";
    std::cout << "执行时间: " << stats.time_elapsed_ms << " ms\n";
    std::cout << "比较次数: " << stats.compare_count << "\n";
    std::cout << "交换次数: " << stats.swap_count << "\n";

    delete[] data;
}

int main()
{
    std::cout << "欢迎使用排序算法比较系统！\n";

    while (true)
    {
        ShowMenu();

        int choice = 0;
        std::cout << "\n请选择排序算法：";
        if (!(std::cin >> choice))
        {
            std::cout << "输入错误，请重新输入！\n";
            ClearInputBuffer();
            continue;
        }

        if (choice == 9)
        {
            std::cout << "感谢使用，再见！\n";
            break;
        }
        if (choice < 1 || choice > 9)
        {
            std::cout << "无效的选择，请重新输入！\n";
            continue;
        }

        int n = 0;
        std::cout << "请输入要产生的随机数个数：";
        if (!(std::cin >> n))
        {
            std::cout << "输入错误，请重新输入！\n";
            ClearInputBuffer();
            continue;
        }
        if (n <= 0 || n > 1000000)
        {
            std::cout << "数据规模无效！请输入 1-1000000 之间的数字。\n";
            continue;
        }

        TestSingleAlgorithm(choice, n);

        char perform_full_test = 'n';
        std::cout << "\n是否对所有算法进行性能比较测试？(y/n): ";
        std::cin >> perform_full_test;

        if (perform_full_test == 'y' || perform_full_test == 'Y')
        {
            RunPerformanceTest(100);
            RunPerformanceTest(1000);
            RunPerformanceTest(10000);
            RunPerformanceTest(100000);

            if (n != 100 && n != 1000 && n != 10000 && n != 100000)
            {
                RunPerformanceTest(n);
            }
        }
    }

    return 0;
}

