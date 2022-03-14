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


HOST = "data.mongodb-api.com/app/data-vkqaw/endpoint/data/beta"
URI = "/action/insertOne"


function hello_world()
    http.get("http://jsonplaceholder.typicode.com/todos/1", nil, function(code, data)
         if (code < 0) then
           print("HTTP request failed")
         else
           print(code, data)
         end
    end)
end

-- function test_post()
--   local http = require("socket.http")
--   local ltn12 = require("ltn12")

--   local respbody = {}
--   local reqbody = {
--     "dataSource": "Cluster0",
--     "database": "todo",
--     "collection": "tasks",
--     "document": {
--       "status": "open",
--       "text": "Do the dishes"
--     }
--   }
--   reqbody = json.encode(reqbody)
--   local reqheader = {
--     ['Content-Type'] = 'application/json',
--     ['Access-Control-Request-Headers'] = '*',
--     ['api-key'] = 'ofr78BaUjULh1DiKunM7NJOgPTHNEpEb5pgQid5mtWGHzGdAy70emHXieARabZbt',
--     ['Content-Length'] = string.len(request_body)
--   }

--   local result, respcode, respheaders, respstatus = http.request {
--       method = "POST",
--       url = "https://data.mongodb-api.com/app/data-vkqaw/endpoint/data/beta/action/insertOne";,
--       source = ltn12.source.string(reqbody),
--       headers = reqheader,
--       sink = ltn12.sink.table(respbody)
--   }
-- end

function build_post_request(host, uri, data_table)

  data = ""

  for param,value in pairs(data_table) do
       data = data .. param.."="..value.."&"
  end

  request = "POST "..uri.." HTTP/1.1\r\n"..
  "Host: "..host.."\r\n"..
  "Connection: close\r\n"..
  "Content-Type: application/json\r\n"..
  "Access-Control-Request-Headers: *\r\n"..
  "api-key: ofr78BaUjULh1DiKunM7NJOgPTHNEpEb5pgQid5mtWGHzGdAy70emHXieARabZbt\r\n"..
  "Content-Length: "..string.len(data).."\r\n"..
  "\r\n"..
  data
  print(request)
  return request
end

function test_dbpost()
  data = {
    dataSource = "Cluster0",
    database = "hehe",
    collection = "tasks",
    document = '{}'
  }

  socket = net.createConnection(net.TCP,0)
  socket:on("receive",display)
  socket:connect(80,HOST)

   socket:on("connection",function(sck)
    post_request = build_post_request(HOST,URI,data)
    sck:send(post_request)
  end)
end
