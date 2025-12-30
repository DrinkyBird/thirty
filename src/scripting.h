#pragma once
#include <lua.h>

typedef struct client_s client_t;

void scripting_init(void);
void scripting_shutdown(void);

void scripting_handle_error(lua_State *L);

void scripting_push_client(lua_State *L, client_t *client);
