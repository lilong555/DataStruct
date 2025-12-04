/**
 * @file 10_sorting_comparison.cpp
 * @brief 8种排序算法的比较案例
 * @author 数据结构课程设计
 * @date 2025
 *
 * 本程序实现了8种经典排序算法，并对其性能进行比较分析
 * 包括时间复杂度、空间复杂度、比较次数和交换次数的统计
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

// 排序统计结构体
struct SortStatistics
{
    string algorithm_name;   // 算法名称
    long long compare_count; // 比较次数
    long long swap_count;    // 交换次数
    double time_elapsed;     // 运行时间（毫秒）

    SortStatistics(string name) : algorithm_name(name),
                                  compare_count(0),
                                  swap_count(0),
                                  time_elapsed(0.0) {}
};

// ==================== 排序算法实现 ====================

/**
 * @brief 冒泡排序
 * @param arr 待排序数组
 * @param stats 统计信息
 * 时间复杂度：O(n²)，空间复杂度：O(1)
 */
void BubbleSort(vector<int> &arr, SortStatistics &stats)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            stats.compare_count++;
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                stats.swap_count++;
                swapped = true;
            }
        }
        if (!swapped)
            break; // 优化：如果没有交换，说明已经有序
    }
}

/**
 * @brief 选择排序
 * @param arr 待排序数组
 * @param stats 统计信息
 * 时间复杂度：O(n²)，空间复杂度：O(1)
 */
void SelectionSort(vector<int> &arr, SortStatistics &stats)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            stats.compare_count++;
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            swap(arr[i], arr[min_idx]);
            stats.swap_count++;
        }
    }
}

/**
 * @brief 直接插入排序
 * @param arr 待排序数组
 * @param stats 统计信息
 * 时间复杂度：O(n²)，空间复杂度：O(1)
 */
void InsertionSort(vector<int> &arr, SortStatistics &stats)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
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
                j--;
            }
            else
            {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

/**
 * @brief 希尔排序
 * @param arr 待排序数组
 * @param stats 统计信息
 * 时间复杂度：O(n^1.3)到O(n²)，空间复杂度：O(1)
 */
void ShellSort(vector<int> &arr, SortStatistics &stats)
{
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap; j -= gap)
            {
                stats.compare_count++;
                if (arr[j - gap] > temp)
                {
                    arr[j] = arr[j - gap];
                    stats.swap_count++;
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

/**
 * @brief 快速排序的分区函数
 */
int Partition(vector<int> &arr, int low, int high, SortStatistics &stats)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        stats.compare_count++;
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
            stats.swap_count++;
        }
    }
    swap(arr[i + 1], arr[high]);
    stats.swap_count++;
    return i + 1;
}

/**
 * @brief 快速排序递归函数
 */
void QuickSortRecursive(vector<int> &arr, int low, int high, SortStatistics &stats)
{
    if (low < high)
    {
        int pi = Partition(arr, low, high, stats);
        QuickSortRecursive(arr, low, pi - 1, stats);
        QuickSortRecursive(arr, pi + 1, high, stats);
    }
}

/**
 * @brief 快速排序
 * @param arr 待排序数组
 * @param stats 统计信息
 * 时间复杂度：O(nlogn)平均，O(n²)最坏，空间复杂度：O(logn)
 */
void QuickSort(vector<int> &arr, SortStatistics &stats)
{
    if (arr.size() > 1)
    {
        QuickSortRecursive(arr, 0, arr.size() - 1, stats);
    }
}

/**
 * @brief 堆调整函数
 */
void Heapify(vector<int> &arr, int n, int i, SortStatistics &stats)
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

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        stats.swap_count++;
        Heapify(arr, n, largest, stats);
    }
}

/**
 * @brief 堆排序
 * @param arr 待排序数组
 * @param stats 统计信息
 * 时间复杂度：O(nlogn)，空间复杂度：O(1)
 */
void HeapSort(vector<int> &arr, SortStatistics &stats)
{
    int n = arr.size();

    // 建堆
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        Heapify(arr, n, i, stats);
    }

    // 排序
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        stats.swap_count++;
        Heapify(arr, i, 0, stats);
    }
}

/**
 * @brief 归并函数
 */
void Merge(vector<int> &arr, int left, int mid, int right, SortStatistics &stats)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        stats.compare_count++;
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        stats.swap_count++; // 归并过程中的移动计为交换
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        stats.swap_count++;
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        stats.swap_count++;
        j++;
        k++;
    }
}

/**
 * @brief 归并排序递归函数
 */
void MergeSortRecursive(vector<int> &arr, int left, int right, SortStatistics &stats)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        MergeSortRecursive(arr, left, mid, stats);
        MergeSortRecursive(arr, mid + 1, right, stats);
        Merge(arr, left, mid, right, stats);
    }
}

/**
 * @brief 归并排序
 * @param arr 待排序数组
 * @param stats 统计信息
 * 时间复杂度：O(nlogn)，空间复杂度：O(n)
 */
void MergeSort(vector<int> &arr, SortStatistics &stats)
{
    if (arr.size() > 1)
    {
        MergeSortRecursive(arr, 0, arr.size() - 1, stats);
    }
}

/**
 * @brief 基数排序
 * @param arr 待排序数组
 * @param stats 统计信息
 * 时间复杂度：O(d*n)，空间复杂度：O(n+k)
 */
void RadixSort(vector<int> &arr, SortStatistics &stats)
{
    if (arr.empty())
        return;

    // 找到最大值
    int max_val = *max_element(arr.begin(), arr.end());

    // 对每一位进行计数排序
    for (int exp = 1; max_val / exp > 0; exp *= 10)
    {
        vector<int> output(arr.size());
        vector<int> count(10, 0);

        // 统计每个数字出现的次数
        for (size_t i = 0; i < arr.size(); i++)
        {
            count[(arr[i] / exp) % 10]++;
            stats.compare_count++;
        }

        // 计算位置
        for (int i = 1; i < 10; i++)
        {
            count[i] += count[i - 1];
        }

        // 构建输出数组
        for (int i = arr.size() - 1; i >= 0; i--)
        {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
            stats.swap_count++;
        }

        // 复制回原数组
        for (size_t i = 0; i < arr.size(); i++)
        {
            arr[i] = output[i];
        }
    }
}

// ==================== 测试和工具函数 ====================

/**
 * @brief 生成随机数数组
 */
vector<int> GenerateRandomArray(int size)
{
    vector<int> arr(size);
    srand(time(nullptr));
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100000; // 生成0-99999之间的随机数
    }
    return arr;
}

/**
 * @brief 验证数组是否已排序
 */
bool IsSorted(const vector<int> &arr)
{
    for (size_t i = 1; i < arr.size(); i++)
    {
        if (arr[i] < arr[i - 1])
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief 执行排序并统计
 */
void ExecuteSort(vector<int> arr, void (*sortFunc)(vector<int> &, SortStatistics &),
                 SortStatistics &stats)
{
    auto start = high_resolution_clock::now();
    sortFunc(arr, stats);
    auto end = high_resolution_clock::now();

    stats.time_elapsed = duration_cast<microseconds>(end - start).count() / 1000.0;

    if (!IsSorted(arr))
    {
        cout << "警告：" << stats.algorithm_name << " 排序结果不正确！" << endl;
    }
}

/**
 * @brief 打印统计结果
 */
void PrintStatistics(const SortStatistics &stats)
{
    cout << left << setw(15) << stats.algorithm_name
         << "  时间: " << setw(12) << fixed << setprecision(3) << stats.time_elapsed << " ms"
         << "  比较: " << setw(12) << stats.compare_count
         << "  交换: " << setw(12) << stats.swap_count << endl;
}

/**
 * @brief 运行所有排序算法的性能测试
 */
void RunPerformanceTest(int data_size)
{
    cout << "\n"
         << string(80, '=') << endl;
    cout << "数据规模: " << data_size << " 个随机数" << endl;
    cout << string(80, '=') << endl;

    // 生成原始数据
    vector<int> original_data = GenerateRandomArray(data_size);

    // 定义排序算法
    vector<pair<string, void (*)(vector<int> &, SortStatistics &)>> algorithms = {
        {"冒泡排序", BubbleSort},
        {"选择排序", SelectionSort},
        {"直接插入排序", InsertionSort},
        {"希尔排序", ShellSort},
        {"快速排序", QuickSort},
        {"堆排序", HeapSort},
        {"归并排序", MergeSort},
        {"基数排序", RadixSort}};

    cout << left << setw(15) << "排序算法"
         << "  " << setw(20) << "执行时间"
         << "  " << setw(15) << "比较次数"
         << "  " << setw(15) << "交换次数" << endl;
    cout << string(80, '-') << endl;

    // 对每种算法执行测试
    for (auto &algo : algorithms)
    {
        SortStatistics stats(algo.first);
        vector<int> test_data = original_data; // 复制数据
        ExecuteSort(test_data, algo.second, stats);
        PrintStatistics(stats);
    }

    cout << string(80, '=') << endl;
}

/**
 * @brief 显示菜单
 */
void ShowMenu()
{
    cout << "\n"
         << string(50, '*') << endl;
    cout << "**" << setw(48) << "排序算法比较" << "**" << endl;
    cout << string(50, '=') << endl;
    cout << "**" << setw(25) << "1 ---- 冒泡排序" << setw(23) << "**" << endl;
    cout << "**" << setw(25) << "2 ---- 选择排序" << setw(23) << "**" << endl;
    cout << "**" << setw(28) << "3 ---- 直接插入排序" << setw(20) << "**" << endl;
    cout << "**" << setw(25) << "4 ---- 希尔排序" << setw(23) << "**" << endl;
    cout << "**" << setw(25) << "5 ---- 快速排序" << setw(23) << "**" << endl;
    cout << "**" << setw(24) << "6 ---- 堆排序" << setw(24) << "**" << endl;
    cout << "**" << setw(25) << "7 ---- 归并排序" << setw(23) << "**" << endl;
    cout << "**" << setw(25) << "8 ---- 基数排序" << setw(23) << "**" << endl;
    cout << "**" << setw(25) << "9 ---- 退出程序" << setw(23) << "**" << endl;
    cout << string(50, '=') << endl;
}

/**
 * @brief 单个算法测试
 */
void TestSingleAlgorithm(int choice, int data_size)
{
    vector<int> test_data = GenerateRandomArray(data_size);
    SortStatistics stats("");

    switch (choice)
    {
    case 1:
        stats.algorithm_name = "冒泡排序";
        ExecuteSort(test_data, BubbleSort, stats);
        break;
    case 2:
        stats.algorithm_name = "选择排序";
        ExecuteSort(test_data, SelectionSort, stats);
        break;
    case 3:
        stats.algorithm_name = "直接插入排序";
        ExecuteSort(test_data, InsertionSort, stats);
        break;
    case 4:
        stats.algorithm_name = "希尔排序";
        ExecuteSort(test_data, ShellSort, stats);
        break;
    case 5:
        stats.algorithm_name = "快速排序";
        ExecuteSort(test_data, QuickSort, stats);
        break;
    case 6:
        stats.algorithm_name = "堆排序";
        ExecuteSort(test_data, HeapSort, stats);
        break;
    case 7:
        stats.algorithm_name = "归并排序";
        ExecuteSort(test_data, MergeSort, stats);
        break;
    case 8:
        stats.algorithm_name = "基数排序";
        ExecuteSort(test_data, RadixSort, stats);
        break;
    default:
        cout << "无效的选择！" << endl;
        return;
    }

    cout << "\n算法: " << stats.algorithm_name << endl;
    cout << "数据规模: " << data_size << endl;
    cout << "执行时间: " << fixed << setprecision(3) << stats.time_elapsed << " ms" << endl;
    cout << "比较次数: " << stats.compare_count << endl;
    cout << "交换次数: " << stats.swap_count << endl;
}

/**
 * @brief 主函数
 */
int main()
{
    cout << "欢迎使用排序算法比较系统！" << endl;

    while (true)
    {
        ShowMenu();

        int choice;
        cout << "\n请选择排序算法：";
        cin >> choice;

        if (choice == 9)
        {
            cout << "感谢使用，再见！" << endl;
            break;
        }

        if (choice < 1 || choice > 9)
        {
            cout << "无效的选择，请重新输入！" << endl;
            continue;
        }

        int data_size;
        cout << "请输入要产生的随机数个数：";
        cin >> data_size;

        if (data_size <= 0 || data_size > 1000000)
        {
            cout << "数据规模无效！请输入1-1000000之间的数字。" << endl;
            continue;
        }

        // 单个算法测试
        TestSingleAlgorithm(choice, data_size);

        // 询问是否进行完整性能测试
        char perform_full_test;
        cout << "\n是否对所有算法进行性能比较测试？(y/n): ";
        cin >> perform_full_test;

        if (perform_full_test == 'y' || perform_full_test == 'Y')
        {
            // 对不同数据规模进行测试
            vector<int> test_sizes = {100, 1000, 10000};
            if (data_size <= 100000)
            {
                test_sizes.push_back(data_size);
            }

            for (int size : test_sizes)
            {
                RunPerformanceTest(size);
            }
        }
    }

    return 0;
}
