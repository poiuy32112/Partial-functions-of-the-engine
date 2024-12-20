#include <iostream>
#include <string>
#include <unordered_map>
#include <typeinfo>

// 基础反射类，所有需要反射的类都应该继承此类
class Reflectable
{
public:
    // 纯虚函数，需要子类实现以返回类名
    virtual std::string getTypeName() const = 0;
};

// 添加一个函数指针类型，用于创建类实例
typedef Reflectable* (*CreateInstanceFunc)();

// 修改 ReflectionRegistry 类，支持通过类名创建实例
class ReflectionRegistry
{
public:
    // 注册类时，除了实例，还需要注册创建实例的函数
    static void registerClass(const std::string& className, Reflectable* instance, CreateInstanceFunc createFunc)
    {
        registry()[className] = instance;
        createRegistry()[className] = createFunc; // 存储创建函数
    }

    // 获取类实例
    static Reflectable* getClassInstance(const std::string& className)
    {
        return registry()[className];
    }

    // 通过类名创建类实例
    static Reflectable* createClassInstance(const std::string& className)
    {
        auto it = createRegistry().find(className);
        if (it != createRegistry().end())
        {
            return it->second(); // 调用创建函数
        }
        return nullptr;
    }

private:
    // 存储类实例的哈希表
    static std::unordered_map<std::string, Reflectable*>& registry()
    {
        static std::unordered_map<std::string, Reflectable*> instanceRegistry;
        return instanceRegistry;
    }

    // 存储创建函数的哈希表
    static std::unordered_map<std::string, CreateInstanceFunc>& createRegistry()
    {
        static std::unordered_map<std::string, CreateInstanceFunc> createFuncRegistry;
        return createFuncRegistry;
    }
};

// 示例类，继承自 Reflectable
class Player : public Reflectable
{
public:
    // 构造函数，自动将类注册到反射系统
    Player()
    {
        ReflectionRegistry::registerClass(getTypeName(), this, []() -> Reflectable* { return new Player(); });
    }

    // 实现 getTypeName 方法
    std::string getTypeName() const override
    {
        return "Player";
    }

    // 类的字段
    int health = 100;    // 生命值
    std::string name = "Hero";    // 玩家名称
};

int main()
{
    Player player; // 创建 Player 实例

    // 使用反射机制获取类实例
    Reflectable* reflectable = ReflectionRegistry::getClassInstance("Player");
    if (reflectable)
    {
        std::cout << "Class Name: " << reflectable->getTypeName() << std::endl; // 输出类名
    }

    // 使用反射机制创建 Player 类的新实例
    Reflectable* newPlayer = ReflectionRegistry::createClassInstance("Player");
    if (newPlayer)
    {
        std::cout << "New Player Created: " << newPlayer->getTypeName() << std::endl;
        delete newPlayer; // 别忘了删除新创建的实例以避免内存泄漏
    }

    // 直接访问字段（在实际的反射系统中，字段的访问也应该通过反射机制）
    std::cout << "Player Health: " << player.health << std::endl; // 输出生命值
    std::cout << "Player Name: " << player.name << std::endl; // 输出玩家名称

    return 0;
}