// Thirty, a ClassiCube (Minecraft Classic) server
// Copyright (C) 2024 Sean Baggaley
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <libguile.h>
#include <string.h>
#include "scripting.h"
#include "client.h"

extern void commands_scripting_init();
extern void client_scripting_init();

void scripting_init() {
    commands_scripting_init();
    client_scripting_init();

    scm_c_primitive_load("test.scm");
}

void scripting_eval(const char *code) {
    SCM res = scm_c_eval_string(code);
}

static void scripting_eval_command_common(const char *code, client_t *client) {
    SCM res = scm_c_eval_string(code);
    if (scm_is_number(res)) {
        res = scm_number_to_string(res, scm_from_int(10));
    }

    if (scm_is_string(res)) {
        char *s = scm_to_stringn(res, NULL, "UTF-8", SCM_FAILED_CONVERSION_QUESTION_MARK);
        client_send_message(client, msgtype_chat, "%s", s);
    }
}

void scripting_eval_command(int argc, const char **argv, client_t *client, void *userdata) {
    char code[1024];
    memset(code, 0, sizeof code);

    size_t p = 0;
    for (int i = 1; i <= argc; i++) {
        size_t len = strlen(argv[i]);
        strcat(code + p, argv[i]);
        p += len;
        code[p++] = ' ';
    }

    scripting_eval_command_common(code, client);
}
