#include <iostream>
#include <cmath>
#include <cstring>

// ==================== 考生信息结构体 ====================
struct Student
{
    int exam_id;       // 准考证号
    char name[50];     // 姓名
    char gender[10];   // 性别
    int age;           // 年龄
    char category[50]; // 报考类别
};

// A prime number for the hash table size
const int HASH_TABLE_SIZE = 997;

// ==================== 链表节点 ====================
struct Node
{
    Student data;
    Node *next;

    Node() : next(nullptr) {}
};
// ==================== 考生管理系统类 ====================
class ExamRegistrationSystem
{
public:
    ExamRegistrationSystem();
    ~ExamRegistrationSystem();

    // 初始化系统
    void Initialize();

    // 插入考生
    void Insert();

    // 删除考生
    void Delete();

    // 查找考生
    void Search();

    // 修改考生信息
    void Modify();

    // 统计考生信息
    void Statistics();

    // 运行系统
    void Run();

private:
    Node *table_[HASH_TABLE_SIZE]; // 哈希表
    int count_;                    // 考生数量

    // 哈希函数
    int Hash(int exam_id);

    // 输出所有考生信息
    void PrintAll();

    // 输出表头
    void PrintHeader();

    // 输出单个考生信息
    void PrintStudent(const Student &stu);

    // 清空链表
    void Clear();

    // 按考号查找节点
    Node *FindByExamId(int exam_id);

    // 按考号删除
    bool DeleteByExamId(int exam_id);

    // 检查考号是否存在
    bool ExamIdExists(int exam_id);

    // 输入考生信息(带合法性检查)
    bool InputStudent(Student &stu, bool check_duplicate = true);

    // 验证性别输入
    bool ValidateGender(const char *gender);

    // 验证年龄输入
    bool ValidateAge(int age);

    // 验证考号输入
    bool ValidateExamId(int exam_id);

    // 清空输入缓冲区
    void ClearInputBuffer();

    // 打印分割线
    void PrintSeparator(char ch = '=', int length = 70);

    // 打印标题
    void PrintTitle(const char *title);

    // 显示主菜单
    void ShowMenu();
};

// ==================== 构造函数和析构函数 ====================
ExamRegistrationSystem::ExamRegistrationSystem() : count_(0)
{
    for (int i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        table_[i] = nullptr;
    }
}

ExamRegistrationSystem::~ExamRegistrationSystem()
{
    Clear();
}

// ==================== 辅助函数 ====================
int ExamRegistrationSystem::Hash(int exam_id)
{
    // A is a prime number close to the golden ratio conjugate
    const unsigned long long A = 2654435769;
    unsigned long long hash = A * exam_id;
    return (hash >> 16) % HASH_TABLE_SIZE;
}

void ExamRegistrationSystem::Clear()
{
    for (int i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        Node *current = table_[i];
        while (current != nullptr)
        {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
        table_[i] = nullptr;
    }
    count_ = 0;
}

void ExamRegistrationSystem::ClearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

void ExamRegistrationSystem::PrintSeparator(char ch, int length)
{
    for (int i = 0; i < length; ++i)
    {
        std::cout << ch;
    }
    std::cout << std::endl;
}

void ExamRegistrationSystem::PrintTitle(const char *title)
{
    PrintSeparator('=');
    int title_len = std::strlen(title);
    int padding = (70 - title_len) / 2;
    for (int i = 0; i < padding; ++i)
    {
        std::cout << " ";
    }
    std::cout << title << std::endl;
    PrintSeparator('=');
}

void ExamRegistrationSystem::ShowMenu()
{
    std::cout << std::endl;
    PrintSeparator('-');
    std::cout << "  [1] 插入考生信息" << std::endl;
    std::cout << "  [2] 删除考生信息" << std::endl;
    std::cout << "  [3] 查找考生信息" << std::endl;
    std::cout << "  [4] 修改考生信息" << std::endl;
    std::cout << "  [5] 统计考生信息" << std::endl;
    std::cout << "  [0] 退出系统   " << std::endl;
    PrintSeparator('-');
}

void ExamRegistrationSystem::PrintHeader()
{
    PrintSeparator('-');
    std::cout << "考号\t姓名\t\t性别\t年龄\t报考类别" << std::endl;
    PrintSeparator('-');
}

void ExamRegistrationSystem::PrintStudent(const Student &stu)
{
    std::cout << stu.exam_id << "\t";

    // 姓名对齐处理
    int name_len = std::strlen(stu.name);
    std::cout << stu.name;
    if (name_len < 8)
    {
        std::cout << "\t";
    }
    std::cout << "\t";

    std::cout << stu.gender << "\t"
              << stu.age << "\t"
              << stu.category << std::endl;
}

void ExamRegistrationSystem::PrintAll()
{
    if (count_ == 0)
    {
        std::cout << "\n*** 当前系统中暂无考生信息! ***\n"
                  << std::endl;
        return;
    }

    std::cout << std::endl;
    PrintHeader();
    for (int i = 0; i < HASH_TABLE_SIZE; ++i)
    {
        Node *current = table_[i];
        while (current != nullptr)
        {
            PrintStudent(current->data);
            current = current->next;
        }
    }
    PrintSeparator('-');
    std::cout << "总计: " << count_ << " 名考生" << std::endl;
}

// ==================== 验证函数 ====================
bool ExamRegistrationSystem::ValidateGender(const char *gender)
{
    return (std::strcmp(gender, "男") == 0 || std::strcmp(gender, "女") == 0);
}

bool ExamRegistrationSystem::ValidateAge(int age)
{
    return (age >= 10 && age <= 100);
}

bool ExamRegistrationSystem::ValidateExamId(int exam_id)
{
    return (exam_id > 0 && exam_id < 1000000);
}

bool ExamRegistrationSystem::ExamIdExists(int exam_id)
{
    return FindByExamId(exam_id) != nullptr;
}

bool ExamRegistrationSystem::InputStudent(Student &stu, bool check_duplicate)
{
    // 输入考号
    while (true)
    {
        std::cout << "考号: ";
        if (!(std::cin >> stu.exam_id))
        {
            std::cout << "*** 错误: 考号必须是数字! 请重新输入。***" << std::endl;
            ClearInputBuffer();
            continue;
        }

        if (!ValidateExamId(stu.exam_id))
        {
            std::cout << "*** 错误: 考号必须在 1-999999 之间! ***" << std::endl;
            continue;
        }

        if (check_duplicate && ExamIdExists(stu.exam_id))
        {
            std::cout << "*** 错误: 考号 " << stu.exam_id << " 已存在! 请使用其他考号。***" << std::endl;
            continue;
        }

        break;
    }

    // 输入姓名
    while (true)
    {
        std::cout << "姓名: ";
        std::cin >> stu.name;

        int name_len = std::strlen(stu.name);
        if (name_len == 0 || name_len >= 50)
        {
            std::cout << "*** 错误: 姓名长度必须在 1-49 个字符之间! ***" << std::endl;
            continue;
        }

        break;
    }

    // 输入性别
    while (true)
    {
        std::cout << "性别(男/女): ";
        std::cin >> stu.gender;

        if (!ValidateGender(stu.gender))
        {
            std::cout << "*** 错误: 性别只能输入'男'或'女'! ***" << std::endl;
            continue;
        }

        break;
    }

    // 输入年龄
    while (true)
    {
        std::cout << "年龄: ";
        if (!(std::cin >> stu.age))
        {
            std::cout << "*** 错误: 年龄必须是数字! 请重新输入。***" << std::endl;
            ClearInputBuffer();
            continue;
        }

        if (!ValidateAge(stu.age))
        {
            std::cout << "*** 错误: 年龄必须在 10-100 之间! ***" << std::endl;
            continue;
        }

        break;
    }

    // 输入报考类别
    while (true)
    {
        std::cout << "报考类别: ";
        std::cin >> stu.category;

        int category_len = std::strlen(stu.category);
        if (category_len == 0 || category_len >= 50)
        {
            std::cout << "*** 错误: 报考类别长度必须在 1-49 个字符之间! ***" << std::endl;
            continue;
        }

        break;
    }

    return true;
}

// ==================== 核心功能函数 ====================
void ExamRegistrationSystem::Initialize()
{
    PrintTitle("考 生 报 名 系 统");
    std::cout << "\n欢迎使用考生报名系统!" << std::endl;
    std::cout << "首先请建立考生信息数据库。\n"
              << std::endl;

    int num;
    while (true)
    {
        std::cout << "请输入考生人数: ";
        if (!(std::cin >> num))
        {
            std::cout << "*** 错误: 请输入有效的数字! ***" << std::endl;
            ClearInputBuffer();
            continue;
        }

        if (num <= 0)
        {
            std::cout << "*** 错误: 考生人数必须大于 0! ***" << std::endl;
            continue;
        }

        if (num > 10000)
        {
            std::cout << "*** 错误: 考生人数过多! 建议不超过 10000 人。***" << std::endl;
            continue;
        }

        break;
    }

    std::cout << "\n请依次输入每位考生的信息:" << std::endl;
    PrintSeparator('-');

    for (int i = 0; i < num; ++i)
    {
        std::cout << "\n第 " << (i + 1) << " 位考生:" << std::endl;
        Student stu;

        if (!InputStudent(stu, true))
        {
            std::cout << "*** 输入失败! ***" << std::endl;
            --i;
            continue;
        }

        // 哈希表头插法
        Node *new_node = new Node();
        new_node->data = stu;

        int index = Hash(stu.exam_id);
        new_node->next = table_[index];
        table_[index] = new_node;

        count_++;

        std::cout << ">>> 第 " << (i + 1) << " 位考生信息录入成功! <<<" << std::endl;
    }

    std::cout << "\n*** 考生信息初始化完成! ***" << std::endl;
    PrintAll();
}

void ExamRegistrationSystem::Insert()
{
    PrintTitle("插入考生信息");

    std::cout << "\n请输入要插入的考生信息:" << std::endl;
    Student stu;

    if (InputStudent(stu, true))
    {
        // 哈希表头插法
        Node *new_node = new Node();
        new_node->data = stu;

        int index = Hash(stu.exam_id);
        new_node->next = table_[index];
        table_[index] = new_node;

        count_++;
        std::cout << "\n>>> 考生信息插入成功! <<<" << std::endl;
        PrintAll();
    }
}

Node *ExamRegistrationSystem::FindByExamId(int exam_id)
{
    int index = Hash(exam_id);
    Node *current = table_[index];
    while (current != nullptr)
    {
        if (current->data.exam_id == exam_id)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

bool ExamRegistrationSystem::DeleteByExamId(int exam_id)
{
    int index = Hash(exam_id);
    Node *current = table_[index];
    Node *prev = nullptr;

    while (current != nullptr)
    {
        if (current->data.exam_id == exam_id)
        {
            if (prev == nullptr)
            {
                table_[index] = current->next;
            }
            else
            {
                prev->next = current->next;
            }

            std::cout << "\n你删除的考生信息是:" << std::endl;
            PrintHeader();
            PrintStudent(current->data);
            PrintSeparator('-');

            delete current;
            count_--;
            return true;
        }
        prev = current;
        current = current->next;
    }

    return false;
}

void ExamRegistrationSystem::Delete()
{
    PrintTitle("删除考生信息");

    if (count_ == 0)
    {
        std::cout << "\n*** 当前系统中暂无考生信息! ***\n"
                  << std::endl;
        return;
    }

    int exam_id;
    while (true)
    {
        std::cout << "请输入要删除的考生考号: ";
        if (!(std::cin >> exam_id))
        {
            std::cout << "*** 错误: 考号必须是数字! ***" << std::endl;
            ClearInputBuffer();
            continue;
        }
        break;
    }

    if (DeleteByExamId(exam_id))
    {
        std::cout << ">>> 考生信息删除成功! <<<" << std::endl;
        PrintAll();
    }
    else
    {
        std::cout << "\n*** 错误: 未找到考号为 " << exam_id << " 的考生! ***\n"
                  << std::endl;
    }
}

void ExamRegistrationSystem::Search()
{
    PrintTitle("查找考生信息");

    int exam_id;
    while (true)
    {
        std::cout << "请输入要查找的考生考号: ";
        if (!(std::cin >> exam_id))
        {
            std::cout << "*** 错误: 考号必须是数字! ***" << std::endl;
            ClearInputBuffer();
            continue;
        }
        break;
    }

    Node *node = FindByExamId(exam_id);
    if (node != nullptr)
    {
        std::cout << "\n查找结果:" << std::endl;
        PrintHeader();
        PrintStudent(node->data);
        PrintSeparator('-');
    }
    else
    {
        std::cout << "\n*** 错误: 未找到考号为 " << exam_id << " 的考生! ***\n"
                  << std::endl;
    }
}

void ExamRegistrationSystem::Modify()
{
    PrintTitle("修改考生信息");

    int exam_id;
    while (true)
    {
        std::cout << "请输入要修改的考生考号: ";
        if (!(std::cin >> exam_id))
        {
            std::cout << "*** 错误: 考号必须是数字! ***" << std::endl;
            ClearInputBuffer();
            continue;
        }
        break;
    }

    Node *node = FindByExamId(exam_id);
    if (node != nullptr)
    {
        std::cout << "\n当前考生信息:" << std::endl;
        PrintHeader();
        PrintStudent(node->data);
        PrintSeparator('-');

        std::cout << "\n请输入修改后的信息 (考号不可修改):" << std::endl;

        Student temp_stu;
        temp_stu.exam_id = node->data.exam_id; // 保持考号不变

        // 输入姓名
        while (true)
        {
            std::cout << "姓名: ";
            std::cin >> temp_stu.name;

            int name_len = std::strlen(temp_stu.name);
            if (name_len == 0 || name_len >= 50)
            {
                std::cout << "*** 错误: 姓名长度必须在 1-49 个字符之间! ***" << std::endl;
                continue;
            }
            break;
        }

        // 输入性别
        while (true)
        {
            std::cout << "性别(男/女): ";
            std::cin >> temp_stu.gender;

            if (!ValidateGender(temp_stu.gender))
            {
                std::cout << "*** 错误: 性别只能输入'男'或'女'! ***" << std::endl;
                continue;
            }
            break;
        }

        // 输入年龄
        while (true)
        {
            std::cout << "年龄: ";
            if (!(std::cin >> temp_stu.age))
            {
                std::cout << "*** 错误: 年龄必须是数字! ***" << std::endl;
                ClearInputBuffer();
                continue;
            }

            if (!ValidateAge(temp_stu.age))
            {
                std::cout << "*** 错误: 年龄必须在 10-100 之间! ***" << std::endl;
                continue;
            }
            break;
        }

        // 输入报考类别
        while (true)
        {
            std::cout << "报考类别: ";
            std::cin >> temp_stu.category;

            int category_len = std::strlen(temp_stu.category);
            if (category_len == 0 || category_len >= 50)
            {
                std::cout << "*** 错误: 报考类别长度必须在 1-49 个字符之间! ***" << std::endl;
                continue;
            }
            break;
        }

        // 更新信息
        node->data = temp_stu;

        std::cout << "\n>>> 考生信息修改成功! <<<" << std::endl;
        PrintAll();
    }
    else
    {
        std::cout << "\n*** 错误: 未找到考号为 " << exam_id << " 的考生! ***\n"
                  << std::endl;
    }
}

void ExamRegistrationSystem::Statistics()
{
    PrintTitle("统计考生信息");
    PrintAll();
}

void ExamRegistrationSystem::Run()
{
    Initialize();

    char choice;
    while (true)
    {
        ShowMenu();
        std::cout << "请选择操作 [0-5]: ";
        std::cin >> choice;

        switch (choice)
        {
        case '1':
            Insert();
            break;
        case '2':
            Delete();
            break;
        case '3':
            Search();
            break;
        case '4':
            Modify();
            break;
        case '5':
            Statistics();
            break;
        case '0':
            PrintSeparator('=');
            std::cout << "\n感谢使用考生报名系统! 再见!\n"
                      << std::endl;
            PrintSeparator('=');
            return;
        default:
            std::cout << "\n*** 错误: 无效的操作! 请输入 0-5 之间的数字。***\n"
                      << std::endl;
            ClearInputBuffer();
            break;
        }
    }
}
// ==================== 主函数 ====================
int main()
{
    ExamRegistrationSystem system;
    system.Run();
    return 0;
}
