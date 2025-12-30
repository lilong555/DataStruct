// @ts-check

// 注意：该配置在 Node.js 环境运行，请勿使用浏览器 API（如 window、document）。

/** @type {import('@docusaurus/plugin-content-docs').SidebarsConfig} */
const sidebars = {
  docsSidebar: [
    '主页',
    '快速开始',
    '编译与测试',
    '项目概览',
    {
      type: 'category',
      label: '项目文档',
      items: [
        '项目一-考试报名系统',
        '哈希表实现',
        '增删改查与菜单系统',
        '项目三-勇闯迷宫游戏',
        'DFS回溯算法',
        '项目五-银行业务模拟',
        '队列管理与调度',
        '项目七-修理牧场（最小花费）',
        '最小堆实现',
        '项目八-电网建设造价模拟',
        'Prim算法实现',
        '图的表示与菜单交互',
        '项目十-排序算法比较',
        '排序算法实现说明',
        '性能统计系统',
      ],
    },
    {
      type: 'category',
      label: '参考资料',
      items: ['数据结构参考', '算法参考'],
    },
    '文档索引',
  ],
};

export default sidebars;
