#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "commands.h"
#include "log.h"
#include "scripting.h"
#include "client.h"

extern lua_State *L;

static int script_commands_register(lua_State *L);

static void command_callback(commandctx_t *ctx);

static const luaL_Reg commandslib[] = {
	{"register", script_commands_register},
	{NULL, NULL}
};

void commands_scripting_init(void) {
	luaL_newlib(L, commandslib);
	lua_setfield(L, -2, "commands");
}

int script_commands_register(lua_State *L) {
	if (!lua_isstring(L, 1)) {
		lua_pushliteral(L, "first parameter must be a string");
		lua_error(L);
		return 0;
	}

	const char *name = lua_tostring(L, 1);

	if (!lua_isfunction(L, -1)) {
		lua_pushliteral(L, "must pass a Lua function");
		lua_error(L);
		return 0;
	}

	int func = luaL_ref(L, LUA_REGISTRYINDEX);

	commanddef_t def;
	def.name = name;
	def.func = command_callback;
	def.helpline = "";
	def.op_only = false;
	def.userdata = (void *)(intptr_t)func;
	command_register(&def);

	return 0;
}

void command_callback(commandctx_t *ctx) {
	int ref = (int)(intptr_t)ctx->userdata;
	int tn = lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
	if (!lua_isfunction(L, -1) || lua_isnil(L, -1) || tn != LUA_TFUNCTION) {
		log_printf(log_error, "Not a Lua function");
		return;
	}

	scripting_push_client(L, ctx->client);

	int r = lua_pcall(L, 1, 0, 0);
	if (r != 0) {
		scripting_handle_error(L);
	}
}
