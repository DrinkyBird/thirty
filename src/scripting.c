#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "scripting.h"
#include "str.h"
#include "log.h"

lua_State *L = NULL;

void commands_scripting_init(void);

static int fn_print(lua_State *L);

void scripting_init(void) {
	L = luaL_newstate();
	luaL_openlibs(L);

	lua_pushcfunction(L, fn_print);
	lua_setglobal(L, "print");

	commands_scripting_init();

	if (luaL_dofile(L, "test.lua") != 0) {
		scripting_handle_error(L);
	}
}

void scripting_shutdown(void) {
	lua_close(L);
}

int fn_print(lua_State *L) {
	str_t str;
	string_create(&str);

	int n = lua_gettop(L);
	for (int i = 1; i <= n; i++) {
		const char *arg = lua_tostring(L, i);
		if (i > 1) {
			string_appendl(&str, " ");
		}
		string_appendl(&str, arg);
	}

	log_printf(log_info, "%s", string_get_buffer(&str));
	string_destroy(&str);

	return 0;
}

void scripting_handle_error(lua_State *L) {
	const char *msg = lua_tostring(L, -1);

	luaL_traceback(L, L, msg, 1);

	log_printf(log_error, "Lua error: %s", lua_tostring(L, -1));

	lua_pop(L, 1);
}