#pragma once
#include <lua.h>

typedef struct client_s client_t;
typedef struct map_s map_t;

void scripting_init(void);
void scripting_shutdown(void);

void scripting_handle_error(lua_State *L);

void scripting_push_client(lua_State *L, client_t *client);
void scripting_push_map(lua_State *L, map_t *client);
