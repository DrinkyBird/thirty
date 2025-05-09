#include <quickjs.h>
#include <stdlib.h>
#include "scripting.h"
#include "log.h"
#include "client.h"
#include "map.h"
#include "server.h"

static void scripting_export_map();

static JSRuntime *runtime;
static JSContext *ctx;

void scripting_init() {
    runtime = JS_NewRuntime();
    ctx = JS_NewContext(runtime);
    scripting_export_map();
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

static void scripting_eval_command_common(const char *code, const char *filename, client_t *client) {
    JSValue value = JS_Eval(ctx, code, strlen(code), filename, 0);
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

    scripting_eval_command_common(code, "<eval>", client);
}

void scripting_run_command(int argc, const char **argv, client_t *client) {
    if (argc < 1) {
        client_send_message(client, "Syntax: /run <file>");
        return;
    }

    char fn[512];
    snprintf(fn, sizeof(fn), "scripts/%s", argv[1]);
    FILE *fp = fopen(fn, "r");
    if (!fp) {
        client_send_message(client, "&cFailed to open %s", fn);
        return;
    }

    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *code = malloc(size + 1);
    fread(code, sizeof(char), size, fp);
    code[size] = 0;
    fclose(fp);

    scripting_eval_command_common(code, fn, client);
    free(code);
}

static JSValue js_map_width(JSContext *ctx, JSValueConst this_val, int magic) {
    return JS_NewInt64(ctx, (int64_t)server.map->width);
}

static JSValue js_map_depth(JSContext *ctx, JSValueConst this_val, int magic) {
    return JS_NewInt64(ctx, (int64_t)server.map->depth);
}

static JSValue js_map_height(JSContext *ctx, JSValueConst this_val, int magic) {
    return JS_NewInt64(ctx, (int64_t)server.map->height);
}

static JSValue js_map_get(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    // (x, y, z)
    if (argc != 3) {
        return JS_EXCEPTION;
    }

    int x, y, z;
    JS_ToInt32(ctx, &x, argv[0]);
    JS_ToInt32(ctx, &y, argv[1]);
    JS_ToInt32(ctx, &z, argv[2]);

    uint8_t type = map_get(server.map, x, y, z);
    return JS_NewInt32(ctx, (int32_t)type);
}

static JSValue js_map_set(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    // (x, y, z, type)
    if (argc != 4) {
        return JS_EXCEPTION;
    }

    int x, y, z;
    int type;
    JS_ToInt32(ctx, &x, argv[0]);
    JS_ToInt32(ctx, &y, argv[1]);
    JS_ToInt32(ctx, &z, argv[2]);
    JS_ToInt32(ctx, &type, argv[3]);

    map_set(server.map, x, y, z, type);
    return JS_UNDEFINED;
}

static JSClassID js_map_classid;
static const JSCFunctionListEntry js_map_funcs[] = {
    JS_CGETSET_MAGIC_DEF( "width", js_map_width, NULL, 0 ),
    JS_CGETSET_MAGIC_DEF( "depth", js_map_depth, NULL, 1 ),
    JS_CGETSET_MAGIC_DEF( "height", js_map_height, NULL, 2 ),
    JS_CFUNC_DEF("get", 3, js_map_get),
    JS_CFUNC_DEF("set", 4, js_map_set),
};

void scripting_export_map() {
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_map_funcs, 5);

    JS_SetPropertyStr(ctx, JS_GetGlobalObject(ctx), "world", proto);
}