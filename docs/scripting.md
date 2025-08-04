Scripting
=========

Thirty supports scripting using [GNU Guile](https://www.gnu.org/software/guile), an implementation of the Scheme programming language.

The scripting support is very early, poorly tested, and prone to API breakage.
You have been warned.

## Reference

### Commands

#### `register-command` _name_, _callback_

Registers a command with the given _name_.
The _callback_ is a procedure taking two arguments (args, client).

### Clients

#### `client-name` _client_

Returns the client's name.

#### `client-spawned?` _client_

Whether the client has spawned.

#### `client-op?` _client_

Whether the client is an op.

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

#### `send-message` _client_, _message_[, _type_]

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

#### `teleport` _client_, _x_, _y_, _z_[, _yaw_[, _pitch_]]

Teleports the client to the given position.
If _yaw_ and _pitch_ are not specified, the client's angles remain unchanged.
