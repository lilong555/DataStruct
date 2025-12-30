#include <iostream>
#include <cmath>
#include <cstring>

// 常量：数组上限与“无穷大”
const int kMaxNodes = 100;
const int kMaxNameLen = 50;
const int kInfinity = 2147483647;

// 最小生成树中的边
struct Edge
{
    int u_index;
    int v_index;
    int weight;
};

class PowerGridSystem
{
public:
    PowerGridSystem();
    ~PowerGridSystem() = default;
    // 主循环
    void Run();

private:
    // 菜单对应功能
    void ShowMenu() const;
    void CreateVertices();
    void AddEdges();
    void ConstructPrimMST();
    void DisplayMST() const;

    // 工具函数
    int GetVertexIndex(const char *name) const;
    void ClearInputBuffer() const;
    void PressKeyToContinue() const;

    // Member variables
    char vertex_names_[kMaxNodes][kMaxNameLen];
    int adj_matrix_[kMaxNodes][kMaxNodes];
    int num_vertices_;

    // Storage for the calculated MST result
    Edge mst_edges_[kMaxNodes];
    int mst_edge_count_;
    bool is_mst_created_;
};

// 构造函数：初始化成员
PowerGridSystem::PowerGridSystem()
{
    num_vertices_ = 0;
    mst_edge_count_ = 0;
    is_mst_created_ = false;

    // 初始化邻接矩阵
    for (int i = 0; i < kMaxNodes; ++i)
    {
        for (int j = 0; j < kMaxNodes; ++j)
        {
            adj_matrix_[i][j] = (i == j ? 0 : kInfinity);
        }
    }
}

void PowerGridSystem::Run()
{
    char choice;
    do
    {
        ShowMenu();
        std::cout << "请选择操作: ";
        std::cin >> choice;

        // 清理输入缓冲区的残留
        ClearInputBuffer();

        switch (choice)
        {
        case 'A':
        case 'a':
            CreateVertices();
            break;
        case 'B':
        case 'b':
            AddEdges();
            break;
        case 'C':
        case 'c':
            ConstructPrimMST();
            break;
        case 'D':
        case 'd':
            DisplayMST();
            break;
        case 'E':
        case 'e':
            std::cout << "已退出程序。";
            return;
        default:
            std::cout << "无效的选择，请重试。\n";
        }

        // 非退出时暂停，便于查看输出
        if (choice != 'E' && choice != 'e')
        {
            PressKeyToContinue();
        }

    } while (choice != 'E' && choice != 'e');
}

void PowerGridSystem::ShowMenu() const
{
    std::cout << "\n**              电网造价模拟系统              **\n";
    std::cout << "================================================\n";
    std::cout << "**              A --- 创建电网顶点            **\n";
    std::cout << "**              B --- 添加电网的边            **\n";
    std::cout << "**              C --- 构造最小生成树          **\n";
    std::cout << "**              D --- 显示最小生成树          **\n";
    std::cout << "**              E --- 退出  程序              **\n";
    std::cout << "================================================\n";
}

void PowerGridSystem::CreateVertices()
{
    std::cout << "请输入顶点的个数: ";
    if (!(std::cin >> num_vertices_))
    {
        std::cout << "输入错误。\n";
        ClearInputBuffer();
        return;
    }

    if (num_vertices_ > kMaxNodes || num_vertices_ < 1)
    {
        std::cout << "顶点数量必须在 1 到 " << kMaxNodes << " 之间。\n";
        num_vertices_ = 0;
        return;
    }

    std::cout << "请依次输入各顶点的名称:\n";
    for (int i = 0; i < num_vertices_; ++i)
    {
        char vertexx[kMaxNameLen];
        std::cin >> vertexx;
        if (GetVertexIndex(vertexx) != -1)
        {
            std::cout << "顶点名称重复，请重新输入。\n";
            --i; // Decrement to re-enter this vertex
            continue;
        }
        std::strcpy(vertex_names_[i], vertexx);
    }

    // 重新创建顶点后，重置邻接矩阵
    for (int i = 0; i < kMaxNodes; ++i)
    {
        for (int j = 0; j < kMaxNodes; ++j)
        {
            adj_matrix_[i][j] = (i == j ? 0 : kInfinity);
        }
    }
    is_mst_created_ = false;
    ClearInputBuffer();
}

void PowerGridSystem::AddEdges()
{
    if (num_vertices_ == 0)
    {
        std::cout << "请先创建顶点 (选项 A)。\n";
        return;
    }

    char u_name[kMaxNameLen];
    char v_name[kMaxNameLen];
    int weight;

    while (true)
    {
        std::cout << "请输入两个顶点及边: ";
        std::cin >> u_name >> v_name >> weight;
        if (std::cin.fail())
        {
            std::cout << "无效的输入，请重新输入。\n";
            std::cin.clear(); // Clear error flags
            ClearInputBuffer();
            continue;
        }

        // 结束输入：? ? 0
        if (strcmp(u_name, "?") == 0 && strcmp(v_name, "?") == 0 && weight == 0)
        {
            break;
        }
        int u_idx = GetVertexIndex(u_name);
        int v_idx = GetVertexIndex(v_name);

        if (u_idx == -1 || v_idx == -1)
        {
            std::cout << "顶点不存在，请重新输入。\n";
            continue;
        }

        if (u_idx == v_idx)
        {
            std::cout << "不允许自环边，请重新输入。\n";
            continue;
        }

        if (weight <= 0)
        {
            std::cout << "边权必须为正整数，请重新输入。\n";
            continue;
        }

        // Undirected graph: set weight for both directions
        adj_matrix_[u_idx][v_idx] = weight;
        adj_matrix_[v_idx][u_idx] = weight;
    }
    is_mst_created_ = false; // Graph changed, MST needs update
    ClearInputBuffer();
}

void PowerGridSystem::ConstructPrimMST()
{
    if (num_vertices_ == 0)
    {
        std::cout << "没有顶点数据。\n";
        return;
    }

    char start_node_name[kMaxNameLen];
    std::cout << "请输入起始顶点: ";
    std::cin >> start_node_name;
    ClearInputBuffer();

    int start_node = GetVertexIndex(start_node_name);
    if (start_node == -1)
    {
        std::cout << "起始顶点不存在。\n";
        return;
    }

    // Prim's Algorithm Arrays
    // lowcost[i]: shortest distance from the MST set to node i
    // closest[i]: the node in the MST set that is closest to i
    int lowcost[kMaxNodes];
    int closest[kMaxNodes];
    bool visited[kMaxNodes];

    // Initialization
    for (int i = 0; i < num_vertices_; ++i)
    {
        lowcost[i] = adj_matrix_[start_node][i];
        closest[i] = start_node;
        visited[i] = false;
    }

    visited[start_node] = true;
    mst_edge_count_ = 0;

    std::cout << "生成Prim最小生成树!\n";

    // Loop n-1 times to find n-1 edges
    for (int i = 1; i < num_vertices_; ++i)
    {
        int min_weight = kInfinity;
        int k = -1;

        // Find the closest unvisited node
        for (int j = 0; j < num_vertices_; ++j)
        {
            if (!visited[j] && lowcost[j] < min_weight)
            {
                min_weight = lowcost[j];
                k = j;
            }
        }

        // If no node can be reached (disconnected graph)
        if (k == -1)
        {
            std::cout << "无法构建连通图（图不连通）。\n";
            is_mst_created_ = false;
            return;
        }

        // Add edge to MST results
        mst_edges_[mst_edge_count_].u_index = closest[k];
        mst_edges_[mst_edge_count_].v_index = k;
        mst_edges_[mst_edge_count_].weight = min_weight;
        mst_edge_count_++;

        visited[k] = true;

        // Update lowcost array for the new node k
        for (int j = 0; j < num_vertices_; ++j)
        {
            if (!visited[j] && adj_matrix_[k][j] < lowcost[j])
            {
                lowcost[j] = adj_matrix_[k][j];
                closest[j] = k;
            }
        }
    }

    is_mst_created_ = true;
}

void PowerGridSystem::DisplayMST() const
{
    if (!is_mst_created_)
    {
        std::cout << "请先生成最小生成树 (选项 C)。\n";
        return;
    }

    std::cout << "最小生成树的边如下:\n";
    int total_cost = 0;
    for (int i = 0; i < mst_edge_count_; ++i)
    {
        int u = mst_edges_[i].u_index;
        int v = mst_edges_[i].v_index;
        int w = mst_edges_[i].weight;
        total_cost += w;

        std::cout << vertex_names_[u] << "-(" << w << ")-" << vertex_names_[v] << "\n";
    }
    std::cout << "总造价: " << total_cost << "\n";
}

int PowerGridSystem::GetVertexIndex(const char *name) const
{
    for (int i = 0; i < num_vertices_; ++i)
    {
        if (strcmp(vertex_names_[i], name) == 0)
        {
            return i;
        }
    }
    return -1;
}

void PowerGridSystem::ClearInputBuffer() const
{
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

void PowerGridSystem::PressKeyToContinue() const
{
    std::cout << "按回车键继续...";
    std::cin.get();
}

int main()
{
    PowerGridSystem system;
    system.Run();
    return 0;
}
