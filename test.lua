local debug = require("debug")

function testcmd(client)
	local map = client:get_map()
	local x, y, z = client:get_position()
	map:set(x, y, z, Thirty.blocks.iron_ore)
	print(tostring(client))
	print(tostring(map))
end

commands.register("luatest", testcmd)

print("Script loaded, using " .. _VERSION)

for i, t in ipairs(Thirty.blockinfo) do
    print(string.format("%d -> %d %s", i, t.true_id, t.name))
end

for i = 0, #Thirty.blockinfo do
    local t = Thirty.blockinfo[i]
    print(i)
    print(string.format("%d -> %d %s", i, t.true_id, t.name))
end