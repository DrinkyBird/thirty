local debug = require("debug")

function testcmd(client)
	client:send_message("&fhi from &blua&f, &d" .. client:get_name())
	x, y, z = client:get_position()
	yaw, pitch = client:get_angles()
	print(x, y, z)
	print(yaw, pitch)
	local map = client:get_map()
	map:set(x, y, z, 15)
end

commands.register("luatest", testcmd)

print("Script loaded, using " .. _VERSION)
