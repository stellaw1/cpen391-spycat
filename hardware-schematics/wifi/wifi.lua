station_cfg = {}
station_cfg.ssid = "Omegalul"
station_cfg.pwd = "pepelaugh"
station_cfg.save = true

-- set wifi to AP mode
wifi.setmode(wifi.STATION)
wifi.sta.config(station_cfg)
wifi.sta.connect()

-- create a timer to wait for wifi connection
tmr.delay(1000000)

-- This should print 5 if connection was successful
print(wifi.sta.status())

-- Prints the IP given to ESP8266
--print(wifi.sta.getip())

-- List all available wireless network ---
-- See documentation: https://nodemcu.readthedocs.io/en/master/en/modules/wifi/#wifistagetap


function hello_world()
    http.get("http://jsonplaceholder.typicode.com/todos/1", nil, function(code, data)
         if (code < 0) then
           print("HTTP request failed")
         else
           print(code, data)
         end
    end)
end
