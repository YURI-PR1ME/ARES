// c_function.c
// Cortex-M中断中调用的C函数

// 声明为裸函数以避免编译器添加额外的函数调用框架
// 但这里我们用普通函数，让编译器处理调用约定
int modify_r7_in_c(int original_value)
{
    int new_value;
    
    // 在这里执行C代码逻辑
    // 例如：将传入的值增加100
    new_value = original_value + 100;
    
    // 可以添加更复杂的C代码
    if (new_value > 200) {
        new_value = new_value / 2;
    }
    
    // 做一些其他C操作
    for (int i = 0; i < 5; i++) {
        new_value += i;
    }
    
    // 返回新值，将被赋给R7
    return new_value;
}

// 如果需要，可以添加更多C函数
void another_c_function(void)
{
    // 这里可以访问全局变量等
    // 在中断上下文中需要小心处理共享数据
}
