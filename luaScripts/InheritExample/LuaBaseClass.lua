
---@class LuaBaseClass : BaseClass 纯Lua基类
---@field public new fun(nNumA:integer, nNumB:integer):LuaBaseClass 重新定义new函数, 指明需传参数及返回类型. 该函数由class封装 参数为不定长传递 此处仅定义无实现
local LuaBaseClass = class("BaseClass");

---基类构造(测试成员变量)
---@param nNumA integer
---@param nNumB integer
function LuaBaseClass:ctor(nNumA, nNumB)
    -- 此时为空表通过__index访问至此函数, 传入的self亦为空表. 以此实现实例化对象
    self.m_nNumA = nNumA;
    self.m_nNumB = nNumB;
end

---加法函数(测试子类继承)
---@return integer
---@nodiscard
function LuaBaseClass:AddFunc()
    print("BaseClass AddFunc");
    return self.m_nNumA + self.m_nNumB;
end

---基类函数(测试子类重写)
---@param strTest string 测试文本(子类重写无法重载指定参, 会覆盖函数)
function LuaBaseClass:RewriteFunc(strTest)
    print(strTest);
    print("BaseClass RewriteFunc");
end

return LuaBaseClass;