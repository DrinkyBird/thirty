#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "scripting.h"
#include "map.h"

#define METATABLE_MAP "Map"

static int scripting_map_get_size(lua_State *L);
static int scripting_map_get_block(lua_State *L);
static int scripting_map_set_block(lua_State *L);

static const luaL_Reg map_methods[] = {
	{ "get_size", scripting_map_get_size },
	{ "get", scripting_map_get_block },
	{ "set", scripting_map_set_block },
	{ NULL, NULL }
};

static const luaL_Reg map_meta_methods[] = {
	{ "__index",  NULL },
	{ NULL, NULL }
};

void scripting_push_map(lua_State *L, map_t *map) {
	lua_pushlightuserdata(L, map);
	luaL_setmetatable(L, METATABLE_MAP);
}

void map_scripting_init(lua_State *L) {
	luaL_newmetatable(L, METATABLE_MAP);
	luaL_setfuncs(L, map_meta_methods, 0);
	luaL_newlibtable(L, map_methods);
	luaL_setfuncs(L, map_methods, 0);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 1);
}

static map_t *getmap(lua_State *L) {
	void *p = luaL_checkudata(L, 1, METATABLE_MAP);
	return (map_t *)p;
}

int scripting_map_get_size(lua_State *L) {
	map_t *map = getmap(L);

	lua_pushinteger(L, (lua_Integer)map->width);
	lua_pushinteger(L, (lua_Integer)map->depth);
	lua_pushinteger(L, (lua_Integer)map->height);

	return 3;
}

int scripting_map_get_block(lua_State *L) {
	map_t *map = getmap(L);
	int x = lua_tointeger(L, 2);
	int y = lua_tointeger(L, 3);
	int z = lua_tointeger(L, 4);

	uint8_t block = map_get(map, x, y, z);
	lua_pushinteger(L, block);

	return 1;
}

static bool get_integer(lua_State *L, int n, int *out) {
	if (lua_isnumber(L, n)) {
		*out = (int)lua_tonumber(L, n);
		return true;
	}
	else if (lua_isinteger(L, n)) {
		*out = lua_tointeger(L, n);
		return true;
	}
	else {
		lua_pushfstring(L, "function expected number, but got %s", lua_typename(L, lua_type(L, n)));
		lua_error(L);
		return false;
	}
}

int scripting_map_set_block(lua_State *L) {
	map_t *map = getmap(L);
	int x, y, z;
	if (!get_integer(L, 2, &x) || !get_integer(L, 3, &y) || !get_integer(L, 4, &z)) {
		return 0;
	}
	uint8_t block = lua_tointeger(L, 5);

	map_set(map, x, y, z, block);

	return 0;
}
