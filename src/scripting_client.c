#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "scripting.h"
#include "commands.h"
#include "client.h"
#include "log.h"
#include "server.h"
#include "str.h"

#define METATABLE_CLIENT "Client"

static int scripting_client_get_name(lua_State *L);
static int scripting_client_get_map(lua_State *L);
static int scripting_client_get_position(lua_State *L);
static int scripting_client_get_angles(lua_State *L);
static int scripting_client_send_message(lua_State *L);
static int scripting_client_teleport(lua_State *L);
static int scripting_client_tostring(lua_State *L);

static const luaL_Reg client_methods[] = {
	{ "get_name", scripting_client_get_name },
	{ "get_map", scripting_client_get_map },
	{ "get_position", scripting_client_get_position },
	{ "get_angles", scripting_client_get_angles },
	{ "send_message", scripting_client_send_message },
	{ "teleport", scripting_client_teleport },
	{ NULL, NULL }
};

static const luaL_Reg client_meta_methods[] = {
	{ "__index",  NULL },
	{ "__tostring",  scripting_client_tostring },
	{ NULL, NULL }
};

void scripting_push_client(lua_State *L, client_t *client) {
	void **ud = lua_newuserdata(L, sizeof(void *));
	*ud = client;
	luaL_setmetatable(L, METATABLE_CLIENT);
}

void client_scripting_init(lua_State *L) {
	luaL_newmetatable(L, METATABLE_CLIENT);
	luaL_setfuncs(L, client_meta_methods, 0);
	luaL_newlibtable(L, client_methods);
	luaL_setfuncs(L, client_methods, 0);
	lua_setfield(L, -2, "__index");
	lua_pop(L, 1);
}

static client_t *getclient(lua_State *L) {
	void **p = luaL_checkudata(L, 1, METATABLE_CLIENT);
	return (client_t *)*p;
}

int scripting_client_get_name(lua_State *L) {
	client_t *client = getclient(L);

	lua_pushstring(L, client->name);
	return 1;
}

int scripting_client_get_map(lua_State *L) {
	client_t *client = getclient(L);

	scripting_push_map(L, server.map);
	return 1;
}

int scripting_client_get_position(lua_State *L) {
	client_t *client = getclient(L);

	lua_pushnumber(L, (lua_Number)client->x);
	lua_pushnumber(L, (lua_Number)client->y);
	lua_pushnumber(L, (lua_Number)client->z);

	return 3;
}

int scripting_client_get_angles(lua_State *L) {
	client_t *client = getclient(L);

	lua_pushnumber(L, (lua_Number)client->yaw);
	lua_pushnumber(L, (lua_Number)client->pitch);

	return 2;
}

int scripting_client_send_message(lua_State *L) {
	client_t *client = getclient(L);
	const char *msg = lua_tostring(L, 2);

	client_send_message(client, msgtype_chat, msg);
	return 0;
}

int scripting_client_teleport(lua_State *L) {
	client_t *client = getclient(L);
	float x = (float)lua_tonumber(L, 2);
	float y = (float)lua_tonumber(L, 3);
	float z = (float)lua_tonumber(L, 4);
	float yaw = client->yaw;
	float pitch = client->pitch;

	if (lua_gettop(L) >= 5) {
		yaw = (float)lua_tonumber(L, 5);
		if (lua_gettop(L) >= 6) {
			pitch = (float)lua_tonumber(L, 6);
		}
	}

	client_teleport(client, x, y, z, yaw, pitch);

	return 0;
}

int scripting_client_tostring(lua_State *L) {
	client_t *client = getclient(L);

	lua_pushfstring(L, "<client '%s' @ %p>", client->name, (void *)client);
	return 1;
}
