#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

const int kMaxCustomers = 1000;

// 顾客结构体
struct Customer
{
  int id;          // 顾客编号
  int finish_time; // 完成服务时间
  char window;     // 窗口类型 'A' 或 'B'
};

// 将顾客分配到窗口队列
void AssignCustomers(int customers[], int n,
                     int queue_a[], int &size_a,
                     int queue_b[], int &size_b)
{
  size_a = 0;
  size_b = 0;

  for (int i = 0; i < n; i++)
  {
    if (customers[i] % 2 == 1)
    { // 奇数去A窗口
      queue_a[size_a++] = customers[i];
    }
    else
    { // 偶数去B窗口
      queue_b[size_b++] = customers[i];
    }
  }
}

// 模拟银行服务过程并输出结果
void SimulateBankService(int queue_a[], int size_a,
                         int queue_b[], int size_b)
{
  int index_a = 0; // A窗口当前处理的顾客索引
  int index_b = 0; // B窗口当前处理的顾客索引
  int time_a = 0;  // A窗口当前顾客完成时间
  int time_b = 0;  // B窗口当前顾客完成时间

  bool first = true; // 控制输出格式

  while (index_a < size_a || index_b < size_b)
  {
    // 计算下一个完成时间
    if (index_a < size_a && index_b < size_b)
    {
      // 两个窗口都有顾客
      if (time_a == 0)
      {             // A窗口需要开始新顾客
        time_a = 1; // A窗口处理时间为1
      }
      if (time_b == 0)
      {             // B窗口需要开始新顾客
        time_b = 2; // B窗口处理时间为2
      }

      // 比较哪个窗口先完成
      if (time_a < time_b)
      {
        // A窗口先完成
        if (!first)
          cout << " ";
        cout << queue_a[index_a];
        first = false;
        index_a++;
        time_b -= time_a; // B窗口剩余时间
        time_a = 0;
      }
      else if (time_a > time_b)
      {
        // B窗口先完成
        if (!first)
          cout << " ";
        cout << queue_b[index_b];
        first = false;
        index_b++;
        time_a -= time_b; // A窗口剩余时间
        time_b = 0;
      }
      else
      {
        // 同时完成，A窗口优先输出
        if (!first)
          cout << " ";
        cout << queue_a[index_a];
        first = false;
        index_a++;

        cout << " " << queue_b[index_b];
        index_b++;

        time_a = 0;
        time_b = 0;
      }
    }
    else if (index_a < size_a)
    {
      // 只有A窗口有顾客
      if (!first)
        cout << " ";
      cout << queue_a[index_a];
      first = false;
      index_a++;
    }
    else
    {
      // 只有B窗口有顾客
      if (!first)
        cout << " ";
      cout << queue_b[index_b];
      first = false;
      index_b++;
    }
  }

  cout << endl;
}

int main()
{
  int n;
  cin >> n;

  // 读入顾客编号
  int customers[kMaxCustomers];
  for (int i = 0; i < n; i++)
  {
    cin >> customers[i];
  }

  // 分配到不同窗口
  int queue_a[kMaxCustomers];
  int queue_b[kMaxCustomers];
  int size_a, size_b;

  AssignCustomers(customers, n, queue_a, size_a, queue_b, size_b);

  // 模拟服务过程并输出
  SimulateBankService(queue_a, size_a, queue_b, size_b);

  return 0;
}
