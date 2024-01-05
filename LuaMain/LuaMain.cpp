
#include <iostream>
#include <string>

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include "LuaAPITest.h"
#include <luasocket.h>

int main()
{
    LuaAPITest::TestClass();


    return 0;
}
