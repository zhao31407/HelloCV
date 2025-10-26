

<h2 id="sxJEj">1. **创建 GitHub 仓库**</h2>
<h3 id="B8mQ3">步骤：</h3>
1. **登录 GitHub**
    - 访问 [github.com](https://github.com)
    - 登录您的账户
2. **创建新仓库**
    - 点击右上角 "+" 图标
    - 选择 "New repository"
3. **填写仓库信息**

public——add a readme

4. **点击 "Create repository"**

---

<h2 id="VQXKA">2. **本地开发环境设置**</h2>
<h3 id="F0NwW">克隆仓库到本地：</h3>
```bash
# 克隆仓库
git clone https://github.com/your-username/your-project-name.git
cd your-project-name

# 配置用户信息（如果首次使用）
git config --global user.name "Your Name"
git config --global user.email "your-email@example.com"
```

---

<h2 id="lqLDC">3. **README.md 文件详细结构**</h2>
创建一个完整的 `README.md` 文件：![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1760281396267-5826d94e-3eb3-442c-ab1a-fbe6dea8605b.png)

1.ros2下载和ros链接版对应ros2安装

2.git（1）和git链接版对应的是配置git（包括ssh，邮箱）

3.vscode.md和vscode链接版对应的是vscode的下载与配置

4.OpenCV4.5.5链接版和OpenCV4.5.x.md是OpenCV4.5.5安装和环境配置

5.Linux笔记版是对Linux内容的学习笔记和实践记录

```plain
project-name/
├── src/                    # 源代码目录
│   ├── components/         # 组件文件
│   ├── utils/              # 工具函数
│   └── main.py             # 主程序文件
├── docs/                   # 文档目录
├── tests/                  # 测试文件
├── config/                 # 配置文件
├── requirements.txt        # Python 依赖
├── package.json           # Node.js 依赖
└── README.md              # 项目说明
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1760281231893-803d3059-6e8e-472a-a891-6ac860215aff.png)setting![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1760281280389-d751d8ce-a000-44e5-870c-2b62bfbd9d50.png)

ssh设置

---

<h2 id="C132U">4. **提交到 GitHub 的完整流程**</h2>
<h3 id="Ho7Bw">首次提交：</h3>
```bash
# 添加所有文件到暂存区
git add .

# 提交更改
git commit -m "初始提交：添加项目基础结构和详细README"

# 推送到 GitHub
git push origin main
```

<h3 id="QoEDc">更新 README.md：</h3>
```bash
# 编辑 README.md 文件后
git add README.md
git commit -m "docs: 更新项目文档和安装说明"
git push origin main
```

---

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1760281396267-5826d94e-3eb3-442c-ab1a-fbe6dea8605b.png)或者直接点击图中add file选择方式进行添加（推荐这个，可视化）

提交完点确认就行

<h2 id="w0yXH">第二周任务</h2>
1.代码部分

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1760841950703-03c96157-de7b-4e37-afe7-7a888c67f235.png)有这些，Github上同名

2.CMakeList.txt

确保项目可以通过cmake构建

3.docker

是docker学习版笔记

4.编码问题：加密解密

是对应内容的整合和结构的梳理，以及错误的分析

<h1 id="CVuku">第三周</h1>
1.红绿灯文件夹包括2篇语雀

标记出红色绿色并显示颜色

在原照片上添加RED和GREEN

2.opencv

指示opencv的学习内容包括图像读取，视频读取，图像处理滤波的使用等

3.TrafficLight是程序
