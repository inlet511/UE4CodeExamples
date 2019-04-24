# UE4CodeExamples
UE4 C++ Code Examples

## 一. Plugins/EditorPluginSchema:
包含常见的编辑器扩展的示例代码
扩展菜单栏，扩展菜单像，扩展工具栏以及扩展蓝图编辑器中菜单栏

## 二. Plugins/CustomDetailPanel
自定义面板示例代码
模块入口: CustomDetailPanel

自定义面板包括两种类型：
###1. 对象细节面板自定义(自由度很高)
- **CustomDetailPanel** 模块入口,在模块启动时对自定义进行注册
- **CustomObject** 被自定义的对象
- **MyDetailCustomization** 继承自IDetailCustomization 的自定义类

###2. 属性类型自定义(仅适用于struct)
- **CustomDetailPanel** 模块入口,在模块启动时对自定义进行注册
- **StructVariable** 被自定义的Struct
- **StructVariableDetail** 继承自IPropertyTypeCustomization的自定义类
- **CustomObject** Struct变量的载体,CustomObject中包含了一个StructVariable类型的变量
