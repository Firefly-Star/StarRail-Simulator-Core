# StarRail-Simulator-Core

独立维护的 C++ core 子仓库。

当前状态：
- 已建立最小 CMake + pybind11 构建链路
- 已建立 `BattleEngine` / `BattleConfig` / `InputEvent` / `TickSnapshot` 边界骨架
- `BattleEngine` 已拆出开发期 tick phase API：`begin_tick_timing()` / `exchange_state_buffers()` / `get_snapshot()` / `compute_next(...)` / `wait_until_tick_end()`
- `CurrentActionState`、`ActionQueueState`、`ActionTopState`、`ResourcesState`、`GameState` 等是 C++ 内部类型，不再通过 pybind 导出给 Python
- 已迁入 `logic/advance` 的 C++ 版本
- 整体 namespace 使用 `srs`
- `BattleEngine::compute_next()` 当前仍是 mock，真实战斗逻辑待迁入
- 当前由主仓库 `pytest` 验证 Python/C++ 产品 bridge；C++ 内部逻辑后续由 C++ 自己的测试体系验证

当前目标：
- C++ core 承接战斗内逻辑
- Python 只通过 `BattleConfig`、tick 起始点 cutoff 的 `InputEvent[]`、`TickSnapshot` 与 core 交互
- `pybind11` 仅导出产品边界，core 内部不感知 Python
- C++ 内部逻辑后续由 C++ 自己的测试体系验证，不再为了 pytest 暴露内部类型
