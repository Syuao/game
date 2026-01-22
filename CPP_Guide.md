# UE5 C++ 项目启动指南

很高兴你决定回到 C++！其实我已经为你写好了所有的 C++ 核心代码（敌人 AI、伤害系统、游戏模式），它们就在你的项目文件夹里。

我们只需要把它们编译出来并在编辑器里使用即可。

## 第一步：生成项目文件

1.  **关闭** 当前打开的所有虚幻编辑器窗口。
2.  打开你的项目文件夹：`d:\syuao\project_files\game\`。
3.  找到 **`MyFPSGame.uproject`** 文件。
4.  **右键点击** 它，选择 **Generate Visual Studio project files**。
    *   *如果没有这个选项，请确保你安装了 UE5 的 Visual Studio 集成组件。*
    *   *如果这一步报错，请告诉我报错内容。*

## 第二步：编译代码

1.  生成完成后，文件夹里会出现一个 **`MyFPSGame.sln`** 文件。
2.  双击打开它（使用 Visual Studio）。
3.  在顶部工具栏，设置编译配置：
    *   **Configuration**: Development Editor
    *   **Platform**: Win64
4.  在右侧 **Solution Explorer** (解决方案资源管理器) 中，右键点击 **MyFPSGame** 项目 -> **Build** (生成)。
5.  等待编译成功（Output 窗口显示 `Succeeded`）。

## 第三步：在编辑器中关联

编译成功后，我们可以直接从 VS 按 **F5** 启动编辑器，或者回到文件夹双击 `.uproject` 打开。

进入编辑器后，我们需要创建简单的蓝图来“包装”我们的 C++ 类（因为 C++ 没法直接绑定模型）：

### 1. 设置游戏模式
1.  在内容浏览器中，创建一个新蓝图，搜索父类 **`MyFPSGameMode`** (这是我们写的 C++ 类)。
2.  命名为 `BP_CPP_GameMode`。
3.  打开它，在 Details 面板设置 **Score To Win** (例如 5)。
4.  打开 **Project Settings** -> **Maps & Modes**，把 Default GameMode 设为 `BP_CPP_GameMode`。

### 2. 设置敌人
1.  创建一个新蓝图，搜索父类 **`FPSEnemyCharacter`**。
2.  命名为 `BP_CPP_Enemy`。
3.  打开它：
    *   在 Mesh 组件里设置骨骼模型 (SK_Mannequin)。
    *   调整位置和旋转。
    *   在 Details 面板里，你可以看到我们 C++ 定义的变量：**Health**, **Attack Range** 等，可以随意修改。
4.  把 `BP_CPP_Enemy` 拖入场景。

### 3. 设置子弹
1.  创建一个新蓝图，搜索父类 **`MyFPSProjectile`**。
2.  命名为 `BP_CPP_Projectile`。
3.  添加一个 Sphere Mesh 或 Particle System 让他能被看见。
4.  **重要**：打开你的玩家蓝图 (`BP_FirstPersonCharacter`)，找到 **Projectile Class** 变量，把它改成 `BP_CPP_Projectile`。

---

现在，所有的逻辑（扣血、得分、AI 追逐）都由 C++ 在后台自动处理了，你不需要在蓝图里连任何一根线！
