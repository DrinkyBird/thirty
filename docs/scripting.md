Scripting
=========

Thirty supports scripting using [GNU Guile](https://www.gnu.org/software/guile), an implementation of the Scheme programming language.

The scripting support is very early, poorly tested, and prone to API breakage.
You have been warned.

## Reference

### Commands

#### `register-command` _name_ _callback_

Registers a command with the given _name_.
The _callback_ is a procedure taking two arguments (args, client).

### Events

#### `handle-event` _event_ _callback_

Registers a handler for _event_.
The event name can be a string or symbol.
The _callback_ is a procedure taking relevant arguments.

#### Event types

| Name                | Parameters                             | Description                                                                                      |
|---------------------|----------------------------------------|--------------------------------------------------------------------------------------------------|
| `server-ready`      |                                        | Server has started.                                                                              |
| `server-tick`       |                                        | Server ticked.                                                                                   |
| `client-connect`    | _client_                               | Client is connecting to the server. At this point, login and CPE information has been completed. |
| `client-spawned`    | _client_                               | Client spawned in the level.                                                                     |
| `client-disconnect` | _client_ _msg_                         | Client has left the server.                                                                      |
| `client-move`       | _client_ _x_ _y_ _z_                   | Client position changed.                                                                         |
| `client-message`    | _client_ _msg_                         | Client sent a chat message.                                                                      |
| `client-set-block`  | _client_ _map_ _x_ _y_ _z_ _old_ _new_ | Client changed a block. The _old_ and _new_ blocks are symbols, see [Blocks](#blocks).           |

### Clients

#### `client-name` _client_

Returns the client's name.

#### `client-spawned?` _client_

Whether the client has spawned.

#### `client-op?` _client_

Whether the client is an op.

#### `client-map` _client_

Returns the client's current map.
Even though the server currently only has one map, the map procedures take a map pointer for future-proofing.

#### `client-x` _client_

Client's X position.

#### `client-y` _client_

Client's Y position.

#### `client-z` _client_

Client's Z position.

#### `client-yaw` _client_

Client's yaw.

#### `client-pitch` _client_

Client's pitch.

#### `send-message` _client_ _message_ [_type_]

Sends a chat message to a client.

_type_ is the type of the message, as per CPE MessageTypes.
It can be one of the following symbols.
The parameter is optional and defaults to `'chat`.

- **`'chat`:** regular chat message
- **`'status1`:** shown in the top-right
- **`'status2`:** below `status1`
- **`'status3`:** below `status2`
- **`'bottomright1`:** shown in the bottom-right
- **`'bottomright2`:** below `bottomright1`
- **`'bottomright3`:** below `bottomright2`
- **`'announcement`:** shown in large font in the centre

#### `teleport` _client_ _x_ _y_ _z_ [_yaw_ [_pitch_]]

Teleports the client to the given position.
If _yaw_ and _pitch_ are not specified, the client's angles remain unchanged.

#### `client-supports-extension?` _client_ _extension_ _version_

Returns `#t` if the _client_ supports the given [CPE extension](cpe.md), `#f` otherwise.

### Maps

#### Blocks

Blocks can be supplied as a Scheme symbol or numeric ID.

| ID | Symbol               | Description                                 |
|----|----------------------|---------------------------------------------|
| 0  | `'air`               | Air                                         |
| 1  | `'stone`             | Stone                                       |
| 2  | `'grass`             | Grass                                       |
| 3  | `'dirt`              | Dirt                                        |
| 4  | `'cobblestone`       | Cobblestone                                 |
| 5  | `'wood_planks`       | Wood planks                                 |
| 6  | `'sapling`           | Sapling                                     |
| 7  | `'bedrock`           | Bedrock                                     |
| 8  | `'water`             | Water                                       |
| 9  | `'water_still`       | Still water                                 |
| 10 | `'lava`              | Lava                                        |
| 11 | `'lava_still`        | Still lava                                  |
| 12 | `'sand`              | Sand                                        |
| 13 | `'gravel`            | Gravel                                      |
| 14 | `'gold_ore`          | Gold ore                                    |
| 15 | `'iron_ore`          | Iron ore                                    |
| 16 | `'coal_ore`          | Coal ore                                    |
| 17 | `'wood`              | Wood logs                                   |
| 18 | `'leaves`            | Leaves                                      |
| 19 | `'sponge`            | Sponge                                      |
| 20 | `'glass`             | Glass                                       |
| 21 | `'red_wool`          | Red wool                                    |
| 22 | `'orange_wool`       | Orange wool                                 |
| 23 | `'yellow_wool`       | Yellow wool                                 |
| 24 | `'lime_wool`         | Lime wool                                   |
| 25 | `'green_wool`        | Green wool                                  |
| 26 | `'aquagreen_wool`    | Aquagreen wool                              |
| 27 | `'cyan_wool`         | Cyan wool                                   |
| 28 | `'blue_wool`         | Blue wool                                   |
| 29 | `'purple_wool`       | Purple wool                                 |
| 30 | `'indigo_wool`       | Indigo wool                                 |
| 31 | `'violet_wool`       | Violet wool                                 |
| 32 | `'magenta_wool`      | Magenta wool                                |
| 33 | `'pink_wool`         | Pink wool                                   |
| 34 | `'black_wool`        | Black wool                                  |
| 35 | `'grey_wool`         | Grey wool                                   |
| 36 | `'white_wool`        | White wool                                  |
| 37 | `'dandelion`         | Dandelion                                   |
| 38 | `'rose`              | Rose                                        |
| 39 | `'brown_mushroom`    | Brown mushroom                              |
| 40 | `'red_mushroom`      | Red mushroom                                |
| 41 | `'gold_block`        | Gold block                                  |
| 42 | `'iron_block`        | Iron block                                  |
| 43 | `'double_slab`       | Double stone slab                           |
| 44 | `'slab`              | Stone slab                                  |
| 45 | `'bricks`            | Bricks                                      |
| 46 | `'tnt`               | TNT                                         |
| 47 | `'bookshelf`         | Bookshelf                                   |
| 48 | `'mossy_cobblestoe`  | Mossy cobblestone                           |
| 49 | `'obsidian`          | Obsidian                                    |
| 50 | `'cobblestone_slab`  | Cobblestone slab<br/>(CPE CustomBlocks v1)  |
| 51 | `'rope`              | Rope<br/>(CPE CustomBlocks v1)              |
| 52 | `'sandstone`         | Sandstone<br/>(CPE CustomBlocks v1)         |
| 53 | `'snow`              | Snow<br/>(CPE CustomBlocks v1)              |
| 54 | `'fire`              | Fire<br/>(CPE CustomBlocks v1)              |
| 55 | `'light_pink_wool`   | Light pink wool<br/>(CPE CustomBlocks v1)   |
| 56 | `'forest_green_wool` | Forest green wool<br/>(CPE CustomBlocks v1) |
| 57 | `'brown_wool`        | Brown wool<br/>(CPE CustomBlocks v1)        |
| 58 | `'deep_blue`         | Deep blue wool<br/>(CPE CustomBlocks v1)    |
| 59 | `'turquoise`         | Turquoise wool<br/>(CPE CustomBlocks v1)    |
| 60 | `'ice`               | Ice<br/>(CPE CustomBlocks v1)               |
| 61 | `'ceramic_tile`      | Ceramic tile<br/>(CPE CustomBlocks v1)      |
| 62 | `'magma`             | Magma<br/>(CPE CustomBlocks v1)             |
| 63 | `'pillar`            | Pillar<br/>(CPE CustomBlocks v1)            |
| 64 | `'crate`             | Crate<br/>(CPE CustomBlocks v1)             |
| 65 | `'stone_brick`       | Stone bricks<br/>(CPE CustomBlocks v1)      |

#### `server-map`

Returns the server map.
Even though the server currently only has one map, the map procedures below take a map pointer for future-proofing.

#### `map-width` _map_

Returns the width (X size) of the given map.

#### `map-depth` _map_

Returns the depth (Y size) of the given map.

#### `map-height` _map_

Returns the height (Z size) of the given map.

#### `map-block` _map_ _x_ _y_ _z_

Returns the block at the given coordinates as a symbol.

#### `map-set-block!` _map_ _x_ _y_ _z_ _block_

Sets the block at the given coordinates.
_block_ can be a symbol or numeric ID.

#### `symbol->blockid` _symbol_

Converts the given Scheme symbol to a numeric ID.

#### `blockid->symbol` _id_

Converts the given numeric block ID to a Scheme symbol.

#### `map-set-weather!` _map_ _type_

Sets the map weather. _type_ can be either `'clear`, `'rain`, or `'snow`.
