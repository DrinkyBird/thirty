#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "scripting.h"
#include "str.h"
#include "log.h"
#include "blocks.h"

lua_State *L = NULL;

void client_scripting_init(lua_State *L);
void commands_scripting_init(void);
void map_scripting_init(lua_State *L);

static void scripting_register_blocks(lua_State *L);

static int fn_print(lua_State *L);

void scripting_init(void) {
	L = luaL_newstate();
	luaL_openlibs(L);

	lua_pushcfunction(L, fn_print);
	lua_setglobal(L, "print");

	lua_newtable(L);
	scripting_register_blocks(L);
	lua_setglobal(L, "Thirty");

	map_scripting_init(L);
	client_scripting_init(L);
	commands_scripting_init();

	if (luaL_dofile(L, "test.lua") != 0) {
		scripting_handle_error(L);
	}
}

void scripting_shutdown(void) {
	lua_close(L);
}

void scripting_register_blocks(lua_State *L) {
	// block IDs
	lua_newtable(L);
	for (int i = 0; i < num_blocks; i++) {
		lua_pushinteger(L, i);
		lua_setfield(L, -2, blockinfo[i].name);
	}
	lua_setfield(L, -2, "blocks");

	// block info
	lua_newtable(L);
	for (int i = 0; i < num_blocks; i++) {
		lua_newtable(L);

		lua_pushinteger(L, i);
		lua_setfield(L, -2, "id");
		lua_pushinteger(L, i);
		lua_setfield(L, -2, "true_id");
		lua_pushstring(L, blockinfo[i].name);
		lua_setfield(L, -2, "name");
		lua_pushinteger(L, blockinfo[i].colour);
		lua_setfield(L, -2, "colour");
		lua_pushboolean(L, blockinfo[i].solid);
		lua_setfield(L, -2, "solid");
		lua_pushboolean(L, blockinfo[i].block_light);
		lua_setfield(L, -2, "block_light");
		lua_pushboolean(L, blockinfo[i].liquid);
		lua_setfield(L, -2, "liquid");
		lua_pushboolean(L, blockinfo[i].op_only_place);
		lua_setfield(L, -2, "op_only_place");
		lua_pushboolean(L, blockinfo[i].op_only_break);
		lua_setfield(L, -2, "op_only_break");

		lua_rawseti(L, -2, i);
	}
	lua_setfield(L, -2, "blockinfo");
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
