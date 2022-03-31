station_cfg = {}
station_cfg.ssid = "Omegalul"
station_cfg.pwd = "pepelaugh"
station_cfg.save = true
-- set wifi to AP mode
wifi.setmode(wifi.STATION)
wifi.sta.config(station_cfg)
wifi.sta.connect()
-- create a timer to wait for wifi connection
myTimer = tmr.create()
myTimer:register(1000, tmr.ALARM_SEMI,
function(myTimer)
    if wifi.sta.getip() == nil then
        print("IP unavailable, Waiting...")
        myTimer:start()
    else
        print("Config done, IP is "..wifi.sta.getip())
    end
end)

myTimer:start()
