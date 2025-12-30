local debug = require("debug")

function testcmd(client)
	local map = client:get_map()
	local x, y, z = client:get_position()
	map:set(x, y, z, 15)
	print(tostring(client))
	print(tostring(map))
end

commands.register("luatest", testcmd)

print("Script loaded, using " .. _VERSION)
