#pragma once

struct client_s;

void scripting_init();
void scripting_shutdown();
void scripting_eval(const char *code);
void scripting_eval_command(int argc, const char **argv, struct client_s *client);