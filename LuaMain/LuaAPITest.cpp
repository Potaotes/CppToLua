#include "LuaAPITest.h"

// luaL_dofile(L, "../luaScripts/luascoket/ltn12.lua");
// luaL_dofile(L, "../luaScripts/luascoket/mime.lua");
// luaL_dofile(L, "../luaScripts/luascoket/ftp.lua");
// luaL_dofile(L, "../luaScripts/luascoket/headers.lua");
// luaL_dofile(L, "../luaScripts/luascoket/http.lua");
// luaL_dofile(L, "../luaScripts/luascoket/mbox.lua");
// luaL_dofile(L, "../luaScripts/luascoket/smtp.lua");
// luaL_dofile(L, "../luaScripts/luascoket/tp.lua");
// luaL_dofile(L, "../luaScripts/luascoket/url.lua");
// luaL_dofile(L, "../luaScripts/luascoket/socket.lua");

luaL_Reg LuaAPITest::luax_exts[] = {
	{"socket.core", luaopen_socket_core},
	{"mime.core", luaopen_mime_core},
	{ NULL, NULL }
};

luaL_Reg LuaAPITest::luasocket_scripts[] = {
	{ "ltn12", [](lua_State* L)->int { luaL_dofile(L, "../luaScripts/luascoket/ltn12.lua"); return 1; } },
	{ "mime", [](lua_State* L)->int { luaL_dofile(L, "../luaScripts/luascoket/mime.lua"); return 1; } },
	{ "socket.ftp", [](lua_State* L)->int { luaL_dofile(L, "../luaScripts/luascoket/ftp.lua"); return 1; } },
	{ "socket.headers", [](lua_State* L)->int { luaL_dofile(L, "../luaScripts/luascoket/headers.lua"); return 1; } },
	{ "socket.http", [](lua_State* L)->int { luaL_dofile(L, "../luaScripts/luascoket/http.lua"); return 1; } },
	{ "socket.mbox", [](lua_State* L)->int { luaL_dofile(L, "../luaScripts/luascoket/mbox.lua"); return 1; } },
	{ "socket.smtp", [](lua_State* L)->int { luaL_dofile(L, "../luaScripts/luascoket/smtp.lua"); return 1; } },
	{ "socket.tp", [](lua_State* L)->int { luaL_dofile(L, "../luaScripts/luascoket/tp.lua"); return 1; } },
	{ "socket.url", [](lua_State* L)->int { luaL_dofile(L, "../luaScripts/luascoket/url.lua"); return 1; } },
	{ "socket", [](lua_State* L)->int { luaL_dofile(L, "../luaScripts/luascoket/socket.lua"); return 1; } },
};

void LuaAPITest::TestMain()
{
	lua_State* L = luaL_newstate(); // 创建Lua状态(虚拟机实例)
	luaL_openlibs(L);   // 初始化Lua的状态和全局环境和库

	// 初始化栈空
	std::cout << "Init Stack Element Nums: " << lua_gettop(L) << std::endl;

	lua_pushnumber(L, 10086);   // 将指定number类型数据入栈
	lua_setglobal(L, "nGlobalVal"); // 将栈顶数据设置为全局变量

	// 此时栈内为空 设置全局变量后 全局变量存储至_G表中 不存在于栈内
	std::cout << "Set Global Stack Element Nums: " << lua_gettop(L) << std::endl;

	lua_newtable(L);    // 声明一个table类型变量加入栈顶 该数据结构会占用一个位置
	lua_pushstring(L, "name");
	lua_pushstring(L, "zjx");   // 依次将key和value压入栈
	lua_settable(L, -3);        // 将上述键值设置进table

	// 此时栈内仅有一个table数据结构 table的位置为1(或-1)
	std::cout << "Set Table Stack Element Nums: " << lua_gettop(L) << std::endl;

	lua_pushstring(L, "name");  // 要获取键值需要先将key压栈
	lua_gettable(L, 1); // 此时栈内发生变化 栈顶为Key 该接口调用完后会将获取的值压入栈内
	std::string strName = lua_tostring(L, -1);  // 此时将栈顶数据读出即为内容
	std::cout << strName << std::endl;

	// 此时栈内有两个元素 栈底的table 和2位置的获取的值
	std::cout << "Get After Stack Element Nums: " << lua_gettop(L) << std::endl;

	// 将函数设置为全局函数给Lua调用
	lua_pushcfunction(L, addFunc);
	lua_setglobal(L, "CFunction");

	// 注册打印函数
	//lua_pushcfunction(L, PrintToConsole);
	//lua_setglobal(L, "PrintToC");
	lua_register(L, "PrintToC", PrintToConsole);

	// luaL_loadfile只加载脚本 不执行
	//int nLoadResult = luaL_loadfile(L, "main.lua");
	//if (nLoadResult != LUA_OK)
	//{
	//	std::cout << "Load File Failed!!!" << std::endl;
	//	std::cout << "Error: " << lua_tostring(L, -1) << std::endl;
	//}

	// 加载并执行模块 索引路径为cpp同级 此时第二个参为模块名 非文件名
	//luaL_requiref(L, "main", pInitFun, 0);


	std::cout << "Load File Before Stack Element Nums: " << lua_gettop(L) << std::endl;
	int nDoResult = luaL_dofile(L, "../luaScripts/test.lua");
	if (nDoResult != LUA_OK)
	{
		std::cout << "C Error Code: " << nDoResult << std::endl;
		std::cout << "Error Msg: " << lua_tostring(L, -1) << std::endl;
	}

	std::cout << "Load File Stack Element Nums: " << lua_gettop(L) << std::endl;

	//luaL_dostring(L, "PrintToC('fff')");

	lua_newtable(L);
	lua_pushstring(L, "testValue");
	std::cout << "Push Stack Element Nums: " << lua_gettop(L) << std::endl;
	lua_setfield(L, -2, "testKey");

	std::cout << "Set Field Stack Element Nums: " << lua_gettop(L) << std::endl;

	lua_close(L);
}

void LuaAPITest::TestClass()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	luaopen_socket_core(L);

	LuaAPITest::RegisterLuasocket(L);

	// 以下内容均有报错 暂无法获取绝对路径
	//std::filesystem::path strPath = std::filesystem::current_path();	// C++17新功能 获取当前绝对路径
	////std::cout << strPath << std::endl;
	//const wchar_t* absPathW = strPath.c_str();	// 获取的字符为宽字符 需要转换为普通字符才能给Lua使用
	//// 方式一: 使用wcstombs_s(安全性检查会导致wcstombs无法使用)转换 无报错但退出主程序报错 原因未知
	////std::setlocale(LC_ALL, "");	// 设置本地地域信息 LC_ALL就是全部影响 否则中文转换会有问题
	////size_t nPathLength = wcslen(absPathW) + 1;
	////char* absPathC = new char(nPathLength);
	////wcstombs_s(nullptr, absPathC, nPathLength, absPathW, nPathLength);
	////std::cout << absPathC << std::endl;

	//// 方式二：使用ATL库转换 有报错 原因未知
	////const char* cPath = W2A(absPathW);

	//// 方式三：使用Windows API转换 主程序退出报错
	//char* cPath = new char(wcslen(absPathW));
	//// CP_ACP代表使用当前系统代码页
	//int wcLen = WideCharToMultiByte(CP_ACP, 0, absPathW, -1, NULL, 0, 0, NULL);
	//WideCharToMultiByte(CP_ACP, 0, absPathW, -1, cPath, wcLen, 0, NULL);

	//std::cout << cPath << std::endl;
	//delete(cPath);


	// 添加索引路径供给Lua使用(无法获取绝对路径 使用Lua相对路径处理)
	//lua_pushstring(L, );

	int nClassResult = luaL_dofile(L, "../luaScripts/class.lua");
	if (nClassResult != LUA_OK)
	{
		std::cout << "Error: " << std::endl;
		std::cout << lua_tostring(L, -1) << std::endl;
		lua_close(L);
		return;
	}

	int nInitResult = luaL_dofile(L, "../luaScripts/init.lua");
	if (nInitResult != LUA_OK)
	{
		std::cout << "Error: " << std::endl;
		std::cout << lua_tostring(L, -1) << std::endl;
		lua_close(L);
		return;
	}

	//while (1)
	//{

	//}

	lua_close(L);
}

int LuaAPITest::addFunc(lua_State* L)
{
	std::cout << "Current Stack Nums: " << lua_gettop(L) << std::endl;
	// 获取传入函数的两个值
	lua_Number nNumA = lua_tonumber(L, -1);
	lua_Number nNumB = lua_tonumber(L, -2);

	lua_Number nResult = nNumA + nNumB;

	// 将值重新压栈给Lua获取
	lua_pushnumber(L, nResult);

	// 压入一个测试值
	lua_pushstring(L, "TestString");

	// 需要返回结果个数
	return 2;
}

int LuaAPITest::PrintToConsole(lua_State* L)
{
	if (lua_isstring(L, -1))
	{
		std::cout << lua_tostring(L, -1) << std::endl;
	}
	if (lua_isnumber(L, -1))
	{
		std::cout << lua_tonumber(L, -1) << std::endl;
	}

	return 0;
}

void LuaAPITest::GenLuaClass(lua_State* L)
{
	int nArgNum = lua_gettop(L);
	if (nArgNum != 2)
	{
		luaL_error(L, "GenLuaClass has wrong number of arguments: %d, was expecting %d.", nArgNum, 2);
		return;
	}

	// 传入两个参 类名 父类对象或构造函数
	std::string strClassName = lua_tostring(L, -2);
	void* pSuperFunc = nullptr;
	

	// 父类
	if (lua_isfunction(L, -1))
	{
		// 函数继承
	}
	else if (lua_istable(L, -1))
	{
		// table继承

	}
	else
	{
		return;
	}

}

void LuaAPITest::RegisterLuasocket(lua_State* L)
{
	// 预加载 socket.core 和 mime.core 之后require的时候会调用这里指定的函数
	luaL_Reg* pLib = luax_exts;
	// 获取package.preload字段
	lua_getglobal(L, "package");	// stack: package
	lua_getfield(L, -1, "preload");	// stack: package preload

	for (; pLib->func; ++pLib)
	{
		// 设置执行函数给对应的preload字段
		lua_pushcfunction(L, pLib->func);	// stack: package preload cbfunc
		lua_setfield(L, -2, pLib->name);	// stack: package preload
	}
	
	pLib = luasocket_scripts;
	for (; pLib->func; ++pLib)
	{
		// 设置执行函数给对应的preload字段
		lua_pushcfunction(L, pLib->func);	// stack: package preload cbfunc
		lua_setfield(L, -2, pLib->name);	// stack: package preload
	}

	// 弹出 package 和 preload
	lua_pop(L, 2);
}


