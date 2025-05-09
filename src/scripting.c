#include <quickjs.h>
#include "scripting.h"
#include "log.h"
#include "client.h"

static JSRuntime *runtime;
static JSContext *ctx;

void scripting_init() {
    runtime = JS_NewRuntime();
    ctx = JS_NewContext(runtime);
}

void scripting_shutdown() {
    JS_FreeContext(ctx);
    JS_FreeRuntime(runtime);
}

void scripting_eval(const char *code) {
    JSValue value = JS_Eval(ctx, code, strlen(code), "<code>", 0);
    if (JS_IsException(value)) {
        JSValue exc = JS_GetException(ctx);
        if (JS_IsError(ctx, exc)) {
            log_printf(log_error, "JS error: %s", JS_ToCString(ctx, exc));
        }
    }
    const char *str = JS_ToCString(ctx, value);
    log_printf(log_info, "%s", str);
}

void scripting_eval_command(int argc, const char **argv, client_t *client) {
    char code[1024];
    memset(code, 0, sizeof code);

    size_t p = 0;
    for (int i = 1; i <= argc; i++) {
        size_t len = strlen(argv[i]);
        strcat(code + p, argv[i]);
        p += len;
        code[p++] = ' ';
    }

    JSValue value = JS_Eval(ctx, code, strlen(code), "<code>", 0);
    if (JS_IsException(value)) {
        JSValue exc = JS_GetException(ctx);
        if (JS_IsError(ctx, exc)) {
            client_send_message(client, "&c%s", JS_ToCString(ctx, exc));
            return;
        }
    }

    const char *str = JS_ToCString(ctx, value);
    client_send_message(client, "%s", str);
}