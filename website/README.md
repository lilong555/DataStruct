# 文档站点（Docusaurus）

本目录为静态文档站点工程，使用 [Docusaurus](https://docusaurus.io/) 构建。

文档源文件位于仓库根目录的 `doc/`，站点构建时会直接读取 `../doc`。

## 安装依赖

在 `website/` 目录执行：

```bash
npm ci
```

## 本地预览

```bash
npm start
```

## 构建

```bash
npm run build
```

构建产物输出到 `website/build/`。

## 自动部署（GitHub Pages）

仓库使用 GitHub Actions 自动构建并发布到 GitHub Pages，工作流文件见：`.github/workflows/deploy-pages.yml`。

如需启用 Pages，请在仓库设置中将 Pages 的 Source 选择为 “GitHub Actions”。
