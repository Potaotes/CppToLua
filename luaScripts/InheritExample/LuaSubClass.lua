
local LuaBaseClass = require("InheritExample.LuaBaseClass");

---@class LuaSubClass : LuaBaseClass 继承Lua基类
local LuaSubClass = class("LuaSubClass", LuaBaseClass);

---子类构造(测试成员变量)
---@param nNumA integer
---@param nNumB integer
function LuaSubClass:ctor(nNumA, nNumB)
    self.m_nNumA = nNumA;
    self.m_nNumB = nNumB;
end

-- ---加法函数(继承自父类)
-- ---@return integer
-- function LuaSubClass:AddFunc()
--     return 0
-- end

---基类函数(子类重写父类函数)
function LuaSubClass:RewriteFunc()
    print("SubClass RewriteFunc");
end

return LuaSubClass;