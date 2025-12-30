local debug = require("debug")

function testcmd()
	print("hi from lua")
	print(debug.traceback())
end

commands.register("luatest", testcmd)

print("Script was loaded")
