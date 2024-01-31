
package.path = package.path .. ";" .. "../luaScripts/?.lua"

-- C中添加了preload字段 此处无需添加C索引路径
-- C链接器中添加了socket和mime的动态库
-- 也无需引用socket/路径下的Lua文件 也在C加载的时候加入了prelaod了
-- package.cpath = package.cpath .. ";" .. "../socket/?.dll"
-- package.cpath = package.cpath .. ";" .. "../mine/?.dll"
-- package.cpath = package.cpath .. ";" .. "../?.dll"
package.path = package.path .. ";" .. "../?.lua"


local LuaPanda = require("LuaPanda")
LuaPanda.start("127.0.0.1", 8822)

require("util")

-- dump(package.preload, "Preload")

local main = require("main")

main:main()