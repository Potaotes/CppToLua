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
	/// һ�������
	/// </summary>
	static void TestMain();

	/// <summary>
	/// Lua��̳в���
	/// </summary>
	static void TestClass();

private:
	/// <summary>
	/// �ӷ� ��������
	/// </summary>
	/// <param name="L">Lua�����ʵ��</param>
	/// <returns>���ؽ������</returns>
	static int addFunc(lua_State* L);

	/// <summary>
	/// ��ӡ��Ϣ������̨(��¶��Luaʹ��)
	/// </summary>
	/// <param name="L">Lua�����ʵ��</param>
	/// <returns>���ؽ������</returns>
	static int PrintToConsole(lua_State* L);

	/// <summary>
	/// ����Luaʹ��classȫ�ֺ���
	/// </summary>
	/// <param name="L">Lua�����ʵ��</param>
	static void GenLuaClass(lua_State* L);

	/// <summary>
	/// ע��Luasocket
	/// </summary>
	/// <param name="L">Lua�����ʵ��</param>
	static void RegisterLuasocket(lua_State* L);

private:
	static luaL_Reg luax_exts[];
	static luaL_Reg luasocket_scripts[];

};

