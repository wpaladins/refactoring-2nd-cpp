# 《重构（第2版）》书中代码的C++实现

## 测试
 - 使用 [googletest](https://github.com/google/googletest.git) 实现单元测试
 - googletest 以 git submodule 方式引入，需使用以下方式 clone 本项目：
    ```shell
    git clone --recurse-submodules https://github.com/wpaladins/refactoring-2nd-cpp.git
    ```
 - 使用 VSCode 插件 [C++ TestMate
](https://marketplace.visualstudio.com/items?itemName=matepek.vscode-catch2-test-adapter) 可以一键运行全部测试用例

## 头文件保护
 - 使用 VSCode 插件 [C/C++ Include Guard](https://marketplace.visualstudio.com/items?itemName=akiramiyakoda.cppincludeguard) 自动生成头文件保护
 - 配置如下
    ```json
    {
        "C/C++ Include Guard.Macro Type": "Filepath",
        "C/C++ Include Guard.Comment Style": "Line",
        "C/C++ Include Guard.Remove Extension": false,
        "C/C++ Include Guard.Skip Comment Blocks": true,
        "C/C++ Include Guard.Prefix": "REFACTORING_2ND_",
        "C/C++ Include Guard.Path Depth": 0,
        "C/C++ Include Guard.Path Skip": 0,
    }
    ```
