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

#pragma once
#include <stdint.h>
#include <libguile.h>

#define CPE_CUSTOMBLOCKS_LEVEL 1

typedef struct map_s map_t;

typedef void (*blocktickfunc_t)(map_t *map, size_t x, size_t y, size_t z, uint8_t block);

enum {
#define X(n) n,
#include "blocks.inc"
#undef X

	num_blocks
};

typedef struct blockinfo_s {
	bool solid : 1;
	bool block_light : 1;
	bool liquid : 1;
	bool op_only_place : 1;
	bool op_only_break : 1;

	uint32_t colour;

	blocktickfunc_t tickfunc;
	uint64_t ticktime;
	blocktickfunc_t random_tickfunc;
	blocktickfunc_t placefunc;
	blocktickfunc_t breakfunc;

	const char *name;
	void *symbol;
} blockinfo_t;

extern blockinfo_t blockinfo[num_blocks];

void blocks_init(void);

uint8_t block_get_fallback(uint8_t block);

uint8_t block_get_by_scm(SCM x);
