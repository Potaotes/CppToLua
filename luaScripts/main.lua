

local main = {}
local LuaBaseClass = require("InheritExample.LuaBaseClass") --[[@as LuaBaseClass]]
local LuaSubClass = require("InheritExample.LuaSubClass")   --[[@as LuaSubClass]]

function main:main()
    local pBaseInstance = LuaBaseClass.new(10, 30);
    print("BaseInstance Result: ", pBaseInstance:AddFunc());
    pBaseInstance:RewriteFunc("BaseClass Rewrite.");


    local pSubInstance = LuaSubClass.new(40, 50);
    print("SubInstance Result: ", pSubInstance:AddFunc());
    pSubInstance:RewriteFunc("SubClass Rewrite.");

end

return main