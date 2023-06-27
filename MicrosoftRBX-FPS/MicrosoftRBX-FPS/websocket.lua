local ws = WebSocket.connect("ws://127.0.0.1:58008")
local UserInputService = game:GetService("UserInputService")
local data = {
    rightDown = false,
    firstPerson = false,
    winActive = false
}

game:GetService("RunService").Stepped:Connect(function()
    data.firstPerson = game.Players.LocalPlayer.Character.Head.LocalTransparencyModifier == 1 
    data.rightDown = UserInputService:IsMouseButtonPressed(Enum.UserInputType.MouseButton2)
    data.winActive = UserInputService:IsWindowFocused()
end)

function varChanged()
    local data2send = string.format("%s_%s_%s",data.firstPerson, data.rightDown, data.winActive)
    ws:Send(data2send)
end

for name, vardata in pairs(data) do
    name.connect(varChanged)
end