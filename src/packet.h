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

enum {
	packet_ident = 0x00,
	packet_ping = 0x01,
	packet_level_init = 0x02,
	packet_level_chunk = 0x03,
	packet_level_finish = 0x04,
	packet_set_block_client = 0x05,
	packet_set_block_server = 0x06,
	packet_player_spawn = 0x07,
	packet_player_pos_angle = 0x08,
	packet_player_pos_angle_update = 0x09,
	packet_player_pos_update = 0xa,
	packet_player_angle_update = 0x0b,
	packet_player_despawn = 0x0c,
	packet_message = 0x0d,
	packet_player_disconnect = 0x0e,
	packet_player_set_type = 0x0f,

	packet_extinfo = 0x10,
	packet_extentry = 0x11,

	packet_custom_block_support_level = 0x13,

	packet_set_text_colour = 0x27,

	packet_two_way_ping = 0x2b,
};

enum {
	alphapacket_keepalive = 0x00,
	alphapacket_ident = 0x01,
	alphapacket_handshake = 0x02,
	alphapacket_chat = 0x03,
	alphapacket_world_spawn = 0x06,
	alphapacket_player = 0x0a,
	alphapacket_player_pos = 0x0b,
	alphapacket_player_angle = 0x0c,
	alphapacket_player_pos_angle = 0x0d,
	alphapacket_entity_teleport = 0x21,
	alphapacket_chunk_visibility = 0x32,
	alphapacket_block_data = 0x33,
	alphapacket_kick = 0xff,
};