local ws = WebSocket.connect("ws://127.0.0.1:58008")
local UserInputService = game:GetService("UserInputService")
local data = {}
local proxy = {} 
local meta = {
	__newindex = function(t, k, v)
		if proxy[k] ~= v then
			proxy[k] = v
			print(t, k, v)
			rawset(t, k, nil)
			
	    	local data2send = string.format("%s_%s_%s",data.rightDown, data.firstPerson, data.winActive)
	    	ws:Send(data2send)
		end
	end,
	__index = function(t, k) return tostring(proxy[k]) end
}
setmetatable(data, meta)

data.firstPerson, data.rightDown, data.winActive=false,false,false

game:GetService("RunService").Stepped:Connect(function()
    data.firstPerson = game.Players.LocalPlayer.Character.Head.LocalTransparencyModifier == 1 
    data.rightDown = UserInputService:IsMouseButtonPressed(Enum.UserInputType.MouseButton2)
end)

UserInputService.WindowFocusReleased:Connect(function()
	data.winActive = false
end)
UserInputService.WindowFocused:Connect(function()
	data.winActive = true
end)