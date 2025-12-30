// @ts-check
// `@type` JSDoc 注解用于编辑器类型提示与校验（配合 `@ts-check`）。

import {themes as prismThemes} from 'prism-react-renderer';

// 注意：该配置在 Node.js 环境运行，请勿使用浏览器 API（如 window、document）。

/** @type {import('@docusaurus/types').Config} */
const config = {
  title: 'DataStruct 文档',
  tagline: '数据结构课程设计项目文档站',
  favicon: 'img/favicon.ico',

  future: {
    v4: true,
  },

  // GitHub Pages（项目站点）默认访问地址形如：https://<user>.github.io/<repo>/
  url: 'https://lilong555.github.io',
  baseUrl: '/DataStruct/',

  // GitHub Pages 部署配置
  organizationName: 'lilong555',
  projectName: 'DataStruct',

  onBrokenLinks: 'throw',

  i18n: {
    defaultLocale: 'zh-Hans',
    locales: ['zh-Hans'],
  },

  markdown: {
    mermaid: true,
  },

  themes: ['@docusaurus/theme-mermaid'],

  presets: [
    [
      'classic',
      /** @type {import('@docusaurus/preset-classic').Options} */
      ({
        docs: {
          // 直接使用仓库根目录的 `doc/` 作为文档源
          path: '../doc',
          routeBasePath: '/',
          sidebarPath: './sidebars.js',
          editUrl: 'https://github.com/lilong555/DataStruct/tree/main/',
        },
        blog: false,
        theme: {
          customCss: './src/css/custom.css',
        },
      }),
    ],
  ],

  themeConfig:
    /** @type {import('@docusaurus/preset-classic').ThemeConfig} */
    ({
      colorMode: {
        respectPrefersColorScheme: true,
      },
      navbar: {
        title: 'DataStruct',
        logo: {
          alt: 'DataStruct Logo',
          src: 'img/logo.svg',
        },
        items: [
          {
            type: 'docSidebar',
            sidebarId: 'docsSidebar',
            position: 'left',
            label: '文档',
          },
          {
            href: 'https://github.com/lilong555/DataStruct',
            label: 'GitHub',
            position: 'right',
          },
        ],
      },
      footer: {
        style: 'dark',
        links: [
          {
            title: '链接',
            items: [
              {label: '仓库', href: 'https://github.com/lilong555/DataStruct'},
            ],
          },
        ],
        copyright: `© ${new Date().getFullYear()} lilong555 · 使用 Docusaurus 构建`,
      },
      prism: {
        theme: prismThemes.github,
        darkTheme: prismThemes.dracula,
      },
      mermaid: {
        theme: {light: 'neutral', dark: 'dark'},
      },
    }),
};

export default config;
