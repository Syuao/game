# UE5 蓝图版 FPS 游戏开发指南

既然 C++ 环境配置较复杂，我们直接使用虚幻引擎最强大的**蓝图（Blueprint）**系统来实现所有功能。这不需要编写代码，也不需要 Visual Studio。

请按照以下步骤操作：

## 第一步：创建新项目
1. 打开 **Unreal Editor (5.7.2)**。
2. 在项目浏览器中选择 **Games** > **First Person**（第一人称模板）。
3. 核心设置：
   - **Blueprint** (蓝图)
   - **Target Platform**: Desktop
   - **Quality Preset**: Scalable
   - **Starter Content**: Checked (勾选，方便使用内置素材)
4. 命名项目（例如 `MyFPSDemo`），点击 **Create**。

---

## 第二步：实现敌人 (Enemy)

我们需要一个会追逐玩家并受到伤害的敌人。

1. **创建敌人蓝图**：
   - 在 **Content Browser**（内容浏览器）中，右键点击空白处 -> **Blueprint Class**。
   - 选择父类为 **Character**。
   - 命名为 `BP_Enemy`，双击打开。

2. **设置外观**：
   - 在左侧 Components 面板选中 **Mesh**。
   - 在右侧 Details 面板的 **Skeletal Mesh Asset** 中，选择 `SK_Mannequin` (如果没有，选一个简单的 Cube 也可以)。
   - 调整 Mesh 的位置（Location Z 通常是 -90）和旋转（Rotation Z -90）以匹配胶囊体方向。

3. **添加生命值**：
   - 在左侧 **My Blueprint** 面板，点击 **Variables** 旁的 `+` 号。
   - 命名为 `Health`，类型设为 **Float**。
   - 编译（Compile），在 Details 面板设置 **Default Value** 为 `100.0`。
   - **网络同步**：在 Details 面板中，将 **Replication** 设置为 `Replicated`。

4. **受伤与死亡逻辑 (Event Graph)**：
   - 切换到 **Event Graph** 标签页。
   - 右键搜索并添加 `Event AnyDamage` 节点。
   - 拖入 `Health` 变量（选择 Get），再拖入 `Health`（选择 Set）。
   - 连接逻辑：`Health (Get)` - `Damage` -> `Health (Set)`。
   - 添加分支 (`Branch`, 快捷键 B+左键)：判断 `Health <= 0`。
   - 如果 True：添加 `Destroy Actor` 节点。

5. **简单的 AI 移动 (追逐玩家)**：
   - 在 Event Graph 中找到 `Event Tick`。
   - 右键搜索添加 `AI MoveTo` 节点。
   - **Pawn**: 连接 `Self`（右键搜索 Get Reference to Self）。
   - **Target Actor**: 右键搜索 `Get Player Character`，索引保持 0。
   - *注意：为了让 AI 移动，场景中需要有 NavMeshBoundsVolume。我们在最后一步添加。*

---

## 第三步：让子弹造成伤害

模板自带的子弹只是物理碰撞，我们需要让它能扣血。

1. 在内容浏览器找到 `FirstPersonProjectile` 蓝图（通常在 `Content/FirstPerson/Blueprints`）。
2. 打开它，找到 **Event Hit** 节点。
3. 在销毁子弹（Destroy Actor）之前，添加一段逻辑：
   - 从 `Other` 引脚拉出连线，搜索 `Apply Damage`。
   - **Damaged Actor**: 连接 `Other`。
   - **Base Damage**: 设置为 `20.0`。
   - **Damage Causer**: 连接 `Self`。

---

## 第四步：游戏规则与得分 (GameMode)

1. **创建游戏模式**：
   - 在内容浏览器右键 -> **Blueprint Class** -> 搜索并选择 **GameModeBase**。
   - 命名为 `BP_MyGameMode`。

2. **添加得分逻辑**：
   - 打开 `BP_MyGameMode`。
   - 添加整数变量 `TotalScore`，默认值 0。
   - 创建自定义事件（右键 -> Add Custom Event），命名为 `AddEnemyKill`。
   - 逻辑：`TotalScore` + 1 -> Set `TotalScore`。
   - 判断：如果 `TotalScore >= 5` -> `Print String "You Win!"` -> `Execute Console Command` (Command 填 "RestartLevel")。

3. **连接敌人死亡与得分**：
   - 回到 `BP_Enemy` 的死亡逻辑（Destroy Actor 之前）。
   - 添加：`Get Game Mode` -> `Cast to BP_MyGameMode`。
   - 从 As BP_MyGameMode 引脚拉出，调用 `AddEnemyKill`。

4. **启用游戏模式**：
   - 打开 **Edit** > **Project Settings** > **Maps & Modes**。
   - 将 **Default GameMode** 设置为刚才创建的 `BP_MyGameMode`。
   - 确保 **Default Pawn Class** 还是 `BP_FirstPersonCharacter`。

---

## 第五步：完善场景与测试

1. **添加导航网格 (NavMesh)**：
   - 只有添加了这个，敌人才能移动。
   - 在主界面左侧 **Place Actors** 面板，搜索 `NavMeshBoundsVolume`。
   - 拖入场景，按 `R` 键放大，确保它包裹整个原本的关卡区域。
   - 按 `P` 键，如果地面变绿，说明导航设置成功。

2. **放置敌人**：
   - 将 `BP_Enemy` 从内容浏览器拖入场景中。放 5-6 个。

3. **多人联机测试**：
   - 点击顶部工具栏 **Play** 按钮旁边的三个点（更多选项）。
   - **Number of Players**: 设置为 `2`。
   - **Net Mode**: 选择 `Play as Listen Server`。
   - 点击 Play。你会看到两个窗口，分别代表两个玩家。你可以互相看到，也可以一起打敌人。

---

## 进阶：玩家受伤（可选）

1. 打开 `BP_FirstPersonCharacter`。
2. 添加 `Health` 变量 (Float, 100)。
3. 添加 `Event AnyDamage` -> 扣血 -> 如果 <= 0 -> `Print String "Player Died"` 或 `Destroy Actor`。
4. 要让敌人攻击玩家：
   - 在 `BP_Enemy` 中添加一个 **Sphere Collision** 组件，半径设为 100。
   - 右键该组件 -> Add Event -> **OnComponentBeginOverlap**。
   - Cast to BP_FirstPersonCharacter -> Apply Damage (10.0)。

祝你开发愉快！如果遇到任何具体步骤卡住了，请随时告诉我。
