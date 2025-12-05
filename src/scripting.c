#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "scripting.h"

#include "log.h"

lua_State *L = NULL;

static int fn_print(lua_State *L);

void scripting_init(void) {
    L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, fn_print);
    lua_setglobal(L, "print");

    luaL_dofile(L, "test.lua");
}

void scripting_shutdown(void) {
    lua_close(L);
}

int fn_print(lua_State *L) {
    int level = lua_tointeger(L, 1);
    const char *str = lua_tostring(L, 2);
    log_printf(level, "%s", str);
    return 0;
}