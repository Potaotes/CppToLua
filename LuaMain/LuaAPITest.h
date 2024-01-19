#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <cwchar>
#include <stdlib.h>
#include <atlconv.h>
#include <cstdlib>
#include <locale>
#include <Windows.h>

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <luasocket.h>
#include <mime.h>
}

class LuaAPITest
{
public:
	/// <summary>
	/// 一般测试用
	/// </summary>
	static void TestMain();

	/// <summary>
	/// Lua类继承测试
	/// </summary>
	static void TestClass();

private:
	/// <summary>
	/// 加法 加两个数
	/// </summary>
	/// <param name="L">Lua虚拟机实例</param>
	/// <returns>返回结果个数</returns>
	static int addFunc(lua_State* L);

	/// <summary>
	/// 打印信息至控制台(暴露给Lua使用)
	/// </summary>
	/// <param name="L">Lua虚拟机实例</param>
	/// <returns>返回结果个数</returns>
	static int PrintToConsole(lua_State* L);

	/// <summary>
	/// 生成Lua使用class全局函数
	/// </summary>
	/// <param name="L">Lua虚拟机实例</param>
	static void GenLuaClass(lua_State* L);

	/// <summary>
	/// 注册Luasocket
	/// </summary>
	/// <param name="L">Lua虚拟机实例</param>
	static void RegisterLuasocket(lua_State* L);

private:
	static luaL_Reg luax_exts[];
	static luaL_Reg luasocket_scripts[];

};

