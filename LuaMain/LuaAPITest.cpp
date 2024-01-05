#include "LuaAPITest.h"

luaL_Reg LuaAPITest::luax_exts[] = {
	{"socket.core", luaopen_socket_core},
	{"mime.core", luaopen_mime_core},
	{ NULL, NULL }
};

luaL_Reg LuaAPITest::luasocket_scripts[] = {
	{},
};

void LuaAPITest::TestMain()
{
	lua_State* L = luaL_newstate(); // ����Lua״̬(�����ʵ��)
	luaL_openlibs(L);   // ��ʼ��Lua��״̬��ȫ�ֻ����Ϳ�

	// ��ʼ��ջ��
	std::cout << "Init Stack Element Nums: " << lua_gettop(L) << std::endl;

	lua_pushnumber(L, 10086);   // ��ָ��number����������ջ
	lua_setglobal(L, "nGlobalVal"); // ��ջ����������Ϊȫ�ֱ���

	// ��ʱջ��Ϊ�� ����ȫ�ֱ����� ȫ�ֱ����洢��_G���� ��������ջ��
	std::cout << "Set Global Stack Element Nums: " << lua_gettop(L) << std::endl;

	lua_newtable(L);    // ����һ��table���ͱ�������ջ�� �����ݽṹ��ռ��һ��λ��
	lua_pushstring(L, "name");
	lua_pushstring(L, "zjx");   // ���ν�key��valueѹ��ջ
	lua_settable(L, -3);        // ��������ֵ���ý�table

	// ��ʱջ�ڽ���һ��table���ݽṹ table��λ��Ϊ1(��-1)
	std::cout << "Set Table Stack Element Nums: " << lua_gettop(L) << std::endl;

	lua_pushstring(L, "name");  // Ҫ��ȡ��ֵ��Ҫ�Ƚ�keyѹջ
	lua_gettable(L, 1); // ��ʱջ�ڷ����仯 ջ��ΪKey �ýӿڵ������Ὣ��ȡ��ֵѹ��ջ��
	std::string strName = lua_tostring(L, -1);  // ��ʱ��ջ�����ݶ�����Ϊ����
	std::cout << strName << std::endl;

	// ��ʱջ��������Ԫ�� ջ�׵�table ��2λ�õĻ�ȡ��ֵ
	std::cout << "Get After Stack Element Nums: " << lua_gettop(L) << std::endl;

	// ����������Ϊȫ�ֺ�����Lua����
	lua_pushcfunction(L, addFunc);
	lua_setglobal(L, "CFunction");

	// ע���ӡ����
	//lua_pushcfunction(L, PrintToConsole);
	//lua_setglobal(L, "PrintToC");
	lua_register(L, "PrintToC", PrintToConsole);

	// luaL_loadfileֻ���ؽű� ��ִ��
	//int nLoadResult = luaL_loadfile(L, "main.lua");
	//if (nLoadResult != LUA_OK)
	//{
	//	std::cout << "Load File Failed!!!" << std::endl;
	//	std::cout << "Error: " << lua_tostring(L, -1) << std::endl;
	//}

	// ���ز�ִ��ģ�� ����·��Ϊcppͬ�� ��ʱ�ڶ�����Ϊģ���� ���ļ���
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

	// �������ݾ��б��� ���޷���ȡ����·��
	//std::filesystem::path strPath = std::filesystem::current_path();	// C++17�¹��� ��ȡ��ǰ����·��
	////std::cout << strPath << std::endl;
	//const wchar_t* absPathW = strPath.c_str();	// ��ȡ���ַ�Ϊ���ַ� ��Ҫת��Ϊ��ͨ�ַ����ܸ�Luaʹ��
	//// ��ʽһ: ʹ��wcstombs_s(��ȫ�Լ��ᵼ��wcstombs�޷�ʹ��)ת�� �ޱ����˳������򱨴� ԭ��δ֪
	////std::setlocale(LC_ALL, "");	// ���ñ��ص�����Ϣ LC_ALL����ȫ��Ӱ�� ��������ת����������
	////size_t nPathLength = wcslen(absPathW) + 1;
	////char* absPathC = new char(nPathLength);
	////wcstombs_s(nullptr, absPathC, nPathLength, absPathW, nPathLength);
	////std::cout << absPathC << std::endl;

	//// ��ʽ����ʹ��ATL��ת�� �б��� ԭ��δ֪
	////const char* cPath = W2A(absPathW);

	//// ��ʽ����ʹ��Windows APIת�� �������˳�����
	//char* cPath = new char(wcslen(absPathW));
	//// CP_ACP����ʹ�õ�ǰϵͳ����ҳ
	//int wcLen = WideCharToMultiByte(CP_ACP, 0, absPathW, -1, NULL, 0, 0, NULL);
	//WideCharToMultiByte(CP_ACP, 0, absPathW, -1, cPath, wcLen, 0, NULL);

	//std::cout << cPath << std::endl;
	//delete(cPath);


	// �������·������Luaʹ��(�޷���ȡ����·�� ʹ��Lua���·������)
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
	// ��ȡ���뺯��������ֵ
	lua_Number nNumA = lua_tonumber(L, -1);
	lua_Number nNumB = lua_tonumber(L, -2);

	lua_Number nResult = nNumA + nNumB;

	// ��ֵ����ѹջ��Lua��ȡ
	lua_pushnumber(L, nResult);

	// ѹ��һ������ֵ
	lua_pushstring(L, "TestString");

	// ��Ҫ���ؽ������
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

	// ���������� ���� ���������캯��
	std::string strClassName = lua_tostring(L, -2);
	void* pSuperFunc = nullptr;
	

	// ����
	if (lua_isfunction(L, -1))
	{
		// �����̳�
	}
	else if (lua_istable(L, -1))
	{
		// table�̳�

	}
	else
	{
		return;
	}

}

void LuaAPITest::RegisterLuasocket(lua_State* L)
{
	// Ԥ���� socket.core �� mime.core ֮��require��ʱ����������ָ���ĺ���
	luaL_Reg* pLib = luax_exts;
	// ��ȡpackage.preload�ֶ�
	lua_getglobal(L, "package");	// stack: package
	lua_getfield(L, -1, "preload");	// stack: package preload

	for (; pLib->func; ++pLib)
	{
		// ����ִ�к�������Ӧ��preload�ֶ�
		lua_pushcfunction(L, pLib->func);	// stack: package preload cbfunc
		lua_setfield(L, -2, pLib->name);	// stack: package preload
	}
	// ���� package �� preload
	lua_pop(L, 2);

	// Ԥ������Ҫ��Lua�ļ�
}


