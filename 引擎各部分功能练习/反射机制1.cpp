#include <iostream>
#include <string>
#include <unordered_map>
#include <typeinfo>

// 基础反射类，所有需要反射的类都应继承自此类
class Reflectable
{
public:
    // 纯虚函数，要求子类实现以返回类名
    virtual std::string getTypeName() const = 0;
};

// 反射注册器类，用于注册和检索类的实例
class ReflectionRegistry
{
public:
    // 注册类实例到注册表中
    static void registerClass(const std::string& className, Reflectable* instance)
    {
        registry()[className] = instance; // 将类名和实例指针存储在哈希表中
    }

    // 根据类名检索类实例
    static Reflectable* getClassInstance(const std::string& className)
    {
        return registry()[className]; // 从哈希表中获取实例指针
    }

private:
    // 返回一个静态的哈希表，用于存储类名和实例指针的映射
    static std::unordered_map<std::string, Reflectable*>& registry()
    {
        static std::unordered_map<std::string, Reflectable*> instanceRegistry;
        return instanceRegistry;
    }
};

// 示例类，继承自 Reflectable
class Player : public Reflectable
{
public:
    // 构造函数，自动将自身注册到反射注册器中
    Player()
    {
        ReflectionRegistry::registerClass(getTypeName(), this);
    }

    // 实现 getTypeName 方法，返回类名
    std::string getTypeName() const override
    {
        return "Player";
    }

    // 类的字段
    int health = 100; // 玩家健康值
    std::string name = "Hero"; // 玩家名称
};

int main()
{
    Player player; // 创建 Player 类的实例

    // 使用反射机制获取类名
    Reflectable* reflectable = ReflectionRegistry::getClassInstance("Player");
    if (reflectable)
    {
        std::cout << "Class Name: " << reflectable->getTypeName() << std::endl; // 输出类名
    }

    // 直接访问字段（在真实的反射系统中，字段访问会更复杂）
    std::cout << "Player Health: " << player.health << std::endl; // 输出玩家健康值
    std::cout << "Player Name: " << player.name << std::endl; // 输出玩家名称

    return 0;
}