# StarRail-Simulator-Core

独立维护的 C++ core 子仓库。

当前状态：
- 已建立最小 CMake + pybind11 构建链路
- 已建立 `BattleEngine` / `BattleConfig` / `InputEvent` / `TickSnapshot` 边界骨架
- 已迁入 `CurrentActionState`、`ActionQueueState`、`ActionTopState`、`ResourcesState` 等迁移期 C++ 类型
- 已迁入 `logic/advance` 的 C++ 版本
- 整体 namespace 使用 `srs`
- `BattleEngine::tick()` 当前仍是 mock，真实战斗逻辑待迁入
- 当前由主仓库 `pytest` 驱动验证

当前目标：
- C++ core 承接战斗内逻辑
- Python 只通过 `BattleConfig`、`InputEvent[]`、`TickSnapshot` 与 core 交互
- `pybind11` 仅用于 binding 层，core 内部不感知 Python
