#pragma once
#include <lua.h>

void scripting_init(void);
void scripting_shutdown(void);

void scripting_handle_error(lua_State *L);
