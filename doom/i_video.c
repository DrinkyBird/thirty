// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// $Log:$
//
// DESCRIPTION:
//	DOOM graphics stuff for X11, UNIX.
//
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include "doomstat.h"
#include "i_system.h"
#include "v_video.h"
#include "m_argv.h"
#include "d_main.h"
#include "doomdef.h"
#include "../src/blocks.h"
#include "src/map.h"
#include "src/server.h"

#define MAKERGB(r,g,b)		(((r)<<16)|((g)<<8)|(b))
#define MAKEARGB(a,r,g,b)	(((a)<<24)|((r)<<16)|((g)<<8)|(b))

#define APART(c)			(((c)>>24)&0xff)
#define RPART(c)			(((c)>>16)&0xff)
#define GPART(c)			(((c)>>8)&0xff)
#define BPART(c)			((c)&0xff)

unsigned int blockpalette[256];
byte doompalette[256*3];

/*
===============
BestColor
(borrowed from Quake2 source: utils3/qdata/images.c)
===============
*/
byte BestColor (const unsigned int *palette, const int r, const int g, const int b, const int numcolors)
{
    int		i;
    int		dr, dg, db;
    int		bestdistortion, distortion;
    int		bestcolor;

    //
    // let any color go to 0 as a last resort
    //
    bestdistortion = 256*256*4;
    bestcolor = 0;

    for (i = 0; i < numcolors; i++)
    {
        dr = r - RPART(palette[i]);
        dg = g - GPART(palette[i]);
        db = b - BPART(palette[i]);
        distortion = dr*dr + dg*dg + db*db;
        if (distortion < bestdistortion)
        {
            if (!distortion)
                return i;		// perfect match

            bestdistortion = distortion;
            bestcolor = i;
        }
    }

    return bestcolor;
}

void I_ShutdownGraphics(void)
{
 
}



//
// I_StartFrame
//
void I_StartFrame (void)
{
    // er?

}


void I_GetEvent(void)
{

}

//
// I_StartTic
//
void I_StartTic (void)
{
	I_GetEvent();
}


//
// I_UpdateNoBlit
//
void I_UpdateNoBlit (void)
{
    // what is this?
}

//
// I_FinishUpdate
//
void I_FinishUpdate (void)
{
    byte *screen = screens[0];
    for (int x = 0; x < SCREENWIDTH; x++)
    for (int y = 0; y < SCREENHEIGHT; y++) {
        int pi = screen[x + y * SCREENWIDTH];
        int pr = doompalette[pi * 3 + 0];
        int pg = doompalette[pi * 3 + 1];
        int pb = doompalette[pi * 3 + 2];

        int bi = BestColor(blockpalette, pr, pg, pb, num_blocks);

        map_set(server.map, x, SCREENHEIGHT - y, 1, bi);
    }
}


//
// I_ReadScreen
//
void I_ReadScreen (byte* scr)
{
    memcpy (scr, screens[0], SCREENWIDTH*SCREENHEIGHT);
}

//
// I_SetPalette
//
void I_SetPalette (byte* p)
{
    memcpy(doompalette, p, 256 * 3);
}


void I_InitGraphics(void)
{
    for (int i = 0; i < num_blocks; i++)
    {
        blockpalette[i] = blockinfo[i].colour;
    }
}

