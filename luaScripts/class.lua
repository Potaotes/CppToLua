---@diagnostic disable: lowercase-global, invisible, missing-fields

---@class BaseClass
---@field private __ctype 1|2 标识类型(1: C类 2: Lua类) 默认为2
---@field private __cname string 类名
---@field private __create fun(...):BaseClass 实例化函数 仅C类的继承使用 Lua类使用元表
---@field public ctor fun(...) 构造函数
---@field public new fun(...):BaseClass 实例化函数
---@field public class BaseClass 当前类内的数据
---@field public super BaseClass 父类

---构建类
---@param strClassName string
---@param unionSuper BaseClass|function|nil
---@return BaseClass
function class(strClassName, unionSuper)
    -- 继承的对象可以是一个table; 也可以是一个函数, 函数的返回值是C的对象
    unionSuper = unionSuper or {}
    local strSuperType = type(unionSuper);

    ---@type BaseClass
    local cNewClass = {
        __ctype = 0,
        __cname = strClassName,
        __create = function (...) return {} end,
        super = {},
        class = {},
        ctor = function (...) end,
        new = function (...) return {} end,
    };

    -- 处理函数类的继承
    if strSuperType == "function" then
        local funSuper = unionSuper;
        -- 函数类继承, 将传入的函数赋值给实例化函数即可, 由传入的函数负责, 该函数返回一个实例化后的对象
        cNewClass.__create = funSuper;
        cNewClass.__ctype = 1;

        -- 函数类型父类不一定有ctor函数, 此处初始化一个空的函数
        cNewClass.ctor = function(...) end;

        -- 创建new函数
        function cNewClass.new(...)
            -- 创建实例
            local instance = cNewClass.__create(...);
            -- C的继承就是将新增的类内的成员依次赋值给C创建的对象内
            for strFiledName, anyFiledVal in pairs(cNewClass) do
                instance[strFiledName] = anyFiledVal;
            end
            -- 记录当前类内 存在的数据
            cNewClass.class = cNewClass;
            -- 调用构造函数初始化
            cNewClass:ctor(...);
            return instance;
        end
    end

    if strSuperType == "table" then
        local cInheritClass = unionSuper;
        local nSuperType = unionSuper.__ctype or 2;  -- 若非1类型则为Lua原生类, 可为基类; 2类型必须为C对象
        if nSuperType == 1 then
            -- C类继承
            cNewClass.__ctype = 1;
            -- table类型继承则代表父类也是一个完整的BaseClass 可继承__create等函数
            -- C的继承就是将新增的类内的成员依次赋值给C创建的对象内
            for filedName, filedValue in pairs(cNewClass) do
                cInheritClass[filedName] = filedValue;
            end
            -- 再覆写__create 如果是完整的BaseClass则直接启用其实例化函数
            cNewClass.__create = cInheritClass.__create;
            cNewClass.super = cInheritClass;
            -- 构造则由类内自行构建

            -- 创建new函数
            function cNewClass.new(...)
                local instance = cNewClass.__create(...);
                for strFiledName, anyFiledVal in pairs(cNewClass) do
                    instance[strFiledName] = anyFiledVal;
                end
                cNewClass.class = cNewClass;
                cNewClass:ctor(...);
                return instance;
            end
        elseif nSuperType == 2 then
            -- Lua类继承

            -- Lua产生的类则不具有__create实例化函数, 无需实例化C的对象, 仅需设置元表的__index字段去访问不存在于当前类的字段

            cNewClass.__ctype = 2;
            -- 若存在基类, 则将其作为__index的访问内容; 否则即自身为基类
            if cInheritClass then
                setmetatable(cNewClass, { __index = cInheritClass });    -- 访问字段时优先访问子类, 若子类没有时访问基类查找. 可实现函数重写功能
                cNewClass.super = cInheritClass;
            else
                -- 自身为基类则保证构造存在即可 上方初始化时已声明构造函数
            end

            -- 构建实例化函数
            function cNewClass.new(...)
                -- Lua类实例化即为声明空表, 函数等的使用去父类查找
                local instance = setmetatable({}, {__index = cNewClass});
                instance.class = cNewClass;
                instance:ctor(...);
                return instance;
            end
        else
            -- 错误类别 一般不会进
        end
    end

    return cNewClass;
end