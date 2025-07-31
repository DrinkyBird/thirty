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

#### `send-message` _client_, _message_

Sends a chat message to a client.