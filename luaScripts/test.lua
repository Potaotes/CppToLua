local test = {}

-- PrintToC("Hello World")

local nNum, strString = CFunction(1, 2)

PrintToC(nNum)
PrintToC(strString)

print("lua print")

---C调用Lua函数测试
---@param nInputNum integer
---@param strInputString string
function G_TEST_FUNC(nInputNum, strInputString)
    print(nInputNum)
    print(strInputString)
end

return test, 10, "000", {a = 1}