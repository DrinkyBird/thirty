# Thirty, a ClassiCube (Minecraft Classic) server
# Copyright (C) 2024 Sean Baggaley
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

project('thirty', 'c',
    version: '0.1.0',
    default_options: [ 'warning_level=0' ]
)

cc = meson.get_compiler('c')
ccflags = []

version_h = configure_file(input: 'version.h.in', output: 'version.h', configuration: {
    'project_version': meson.project_version(),
    'hg_changeset': '@hg_changeset@'
})

hg_identify = vcs_tag(command: ['hg', 'identify', '-T', '{node|short}', '-r', '.'], input: 'hginfo.h.in', output: 'hginfo.h', replace_string: '@hg_changeset@')

source_files = [
    'src/blocks.c',
    'src/blocks.h',
    'src/buffer.c',
    'src/buffer.h',
    'src/client.c',
    'src/client.h',
    'src/commands.c',
    'src/commands.h',
    'src/config.c',
    'src/config.h',
    'src/cpe.c',
    'src/heartbeat.c',
    'src/log.c',
    'src/log.h',
    'src/cpe.h',
    'src/main.c',
    'src/map.c',
    'src/map.h',
    'src/mapgen.c',
    'src/mapgen_classic.c',
    'src/mapgen_debug.c',
    'src/mapgen_flat.c',
    'src/mapgen_seantest.c',
    'src/mapimage.c',
    'src/mapimage.h',
    'src/mapsave.c',
    'src/mapsend.c',
    'src/namelist.c',
    'src/namelist.h',
    'src/nbt.c',
    'src/nbt.h',
    'src/perlin.c',
    'src/perlin.h',
    'src/rng.c',
    'src/rng.h',
    'src/server.c',
    'src/server.h',
    'src/util.c',
    'src/util.h',

    'lib/b64.c',
    'lib/b64.h',
    'lib/md5.c',
    'lib/md5.h',
    'lib/sha1.c',
    'lib/sha1.h',
    'lib/stb_image_write.c',
    'lib/stb_image_write.h',

    'doom/am_map.c',
    'doom/am_map.h',
    'doom/d_englsh.h',
    'doom/d_event.h',
    'doom/d_french.h',
    'doom/d_items.c',
    'doom/d_items.h',
    'doom/d_main.c',
    'doom/d_main.h',
    'doom/d_net.c',
    'doom/d_net.h',
    'doom/doomdata.h',
    'doom/doomdef.c',
    'doom/doomdef.h',
    'doom/doomstat.c',
    'doom/doomstat.h',
    'doom/doomtype.h',
    'doom/d_player.h',
    'doom/dstrings.c',
    'doom/dstrings.h',
    'doom/d_textur.h',
    'doom/d_think.h',
    'doom/d_ticcmd.h',
    'doom/f_finale.c',
    'doom/f_finale.h',
    'doom/f_wipe.c',
    'doom/f_wipe.h',
    'doom/g_game.c',
    'doom/g_game.h',
    'doom/hu_lib.c',
    'doom/hu_lib.h',
    'doom/hu_stuff.c',
    'doom/hu_stuff.h',
    'doom/i_net.c',
    'doom/i_net.h',
    'doom/info.c',
    'doom/info.h',
    'doom/i_sound.c',
    'doom/i_sound.h',
    'doom/i_system.c',
    'doom/i_system.h',
    'doom/i_video.c',
    'doom/i_video.h',
    'doom/m_argv.c',
    'doom/m_argv.h',
    'doom/m_bbox.c',
    'doom/m_bbox.h',
    'doom/m_cheat.c',
    'doom/m_cheat.h',
    'doom/m_fixed.c',
    'doom/m_fixed.h',
    'doom/m_menu.c',
    'doom/m_menu.h',
    'doom/m_misc.c',
    'doom/m_misc.h',
    'doom/m_random.c',
    'doom/m_random.h',
    'doom/m_swap.c',
    'doom/m_swap.h',
    'doom/p_ceilng.c',
    'doom/p_doors.c',
    'doom/p_enemy.c',
    'doom/p_floor.c',
    'doom/p_inter.c',
    'doom/p_inter.h',
    'doom/p_lights.c',
    'doom/p_local.h',
    'doom/p_map.c',
    'doom/p_maputl.c',
    'doom/p_mobj.c',
    'doom/p_mobj.h',
    'doom/p_plats.c',
    'doom/p_pspr.c',
    'doom/p_pspr.h',
    'doom/p_saveg.c',
    'doom/p_saveg.h',
    'doom/p_setup.c',
    'doom/p_setup.h',
    'doom/p_sight.c',
    'doom/p_spec.c',
    'doom/p_spec.h',
    'doom/p_switch.c',
    'doom/p_telept.c',
    'doom/p_tick.c',
    'doom/p_tick.h',
    'doom/p_user.c',
    'doom/r_bsp.c',
    'doom/r_bsp.h',
    'doom/r_data.c',
    'doom/r_data.h',
    'doom/r_defs.h',
    'doom/r_draw.c',
    'doom/r_draw.h',
    'doom/r_local.h',
    'doom/r_main.c',
    'doom/r_main.h',
    'doom/r_plane.c',
    'doom/r_plane.h',
    'doom/r_segs.c',
    'doom/r_segs.h',
    'doom/r_sky.c',
    'doom/r_sky.h',
    'doom/r_state.h',
    'doom/r_things.c',
    'doom/r_things.h',
    'doom/sounds.c',
    'doom/sounds.h',
    'doom/s_sound.c',
    'doom/s_sound.h',
    'doom/st_lib.c',
    'doom/st_lib.h',
    'doom/st_stuff.c',
    'doom/st_stuff.h',
    'doom/tables.c',
    'doom/tables.h',
    'doom/v_video.c',
    'doom/v_video.h',
    'doom/wi_stuff.c',
    'doom/wi_stuff.h',
    'doom/w_wad.c',
    'doom/w_wad.h',
    'doom/z_zone.c',
    'doom/z_zone.h',

    version_h, hg_identify
]

deps = [
    dependency('threads', required: true),
    dependency('zlib', required: true),
    dependency('libcurl', required: true),
]

if build_machine.system() == 'windows'
    deps += cc.find_library('ws2_32')
else
    deps += cc.find_library('m')
endif

libdir = include_directories('lib')

executable('thirty', source_files, dependencies: deps, include_directories: libdir, install: true, c_args: ['-DNORMALUNIX'])
install_data(sources: 'settings.ini', rename: 'thirty.ini', install_dir: '/etc')
