
package.path = package.path .. ";" .. "../luaScripts/?.lua"

package.cpath = package.cpath .. ";" .. "../mine/?.dll"
package.cpath = package.cpath .. ";" .. "../mine/?.dll"
package.cpath = package.cpath .. ";" .. "../?.dll"
package.path = package.path .. ";" .. "../?.lua"


-- local LuaPanda = require("LuaPanda")
-- LuaPanda.start("127.0.0.1", 8822)

require("util")

local main = require("main")

main:main()