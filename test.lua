local debug = require("debug")

function testcmd(client)
	client:send_message("&fhi from &blua&f, &d" .. client:get_name())
	x, y, z = client:get_position()
	yaw, pitch = client:get_angles()
	print(x, y, z)
	print(yaw, pitch)
	client:teleport(12, 24, 56)
end

commands.register("luatest", testcmd)
