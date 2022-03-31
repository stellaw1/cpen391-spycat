-- import requests
-- import json
-- url = "https://data.mongodb-api.com/app/data-rurzl/endpoint/data/beta/action/findOne"
-- payload = json.dumps({
--     "collection": "users",
--     "database": "database",
--     "dataSource": "Cluster0",
--     "projection": {
--         "_id": 1
--     }
-- })
-- headers = {
--     'Content-Type': 'application/json',
--     'Access-Control-Request-Headers': '*',
--     'api-key': 'EB601U8qsA4zsHyZFq9Ppk4GLQUhVmXEkeqYhLpSWc5d0qcJbBF3wSpt2f3TqsTR'
-- }
-- response = requests.request("POST", url, headers=headers, data=payload)
-- print(response.text)

station_cfg = {}
station_cfg.ssid = "Omegalul"
station_cfg.pwd = "pepelaugh"
station_cfg.save = true

-- set wifi to AP mode
wifi_got_ip_event = function(T)
  local site = "data.mongodb-api.com"
  -- Note: Having an IP address does not mean there is internet access!
  -- Internet connectivity can be determined with net.dns.resolve().
  print("WiFi connection is established! IP address is: " .. T.IP)
  dns1 = net.dns.getdnsserver(0)
  dns2 = net.dns.getdnsserver(1)
  if (dns1 == nil) then dns1 = "FAILED" end
  if (dns2 == nil) then dns2 = "FAILED" end

  print("DNS server 1: " .. dns1)
  print("DNS server 2: " .. dns2)
  net.dns.resolve(site, function(sk, ip)
    if (ip == nil) then
      print("DNS fail!")
    else
      print("Connected to the internet")
      print(site .. " IP: " .. ip)
    end
  end)

  test_get_db()

end

wifi.eventmon.register(wifi.eventmon.STA_GOT_IP, wifi_got_ip_event)

print("Connecting to WiFi access point...")
wifi.setmode(wifi.STATION)
wifi.sta.config(station_cfg)

function post_request_json(url, reqbody)
  http.post(
    url,
    'Content-Type: application/json\r\n',
    reqbody,
    function(code, data)
       if (code < 0) then
         print("HTTP POST request failed")
       else
         print(code, data)
       end
  end)
end

function test_get_db()
    http.post(
      'https://data.mongodb-api.com/app/data-rurzl/endpoint/data/beta/action/findOne',
      [[{
        'Content-Type': 'application/json',
        'Access-Control-Request-Headers': '*',
        'api-key': 'EB601U8qsA4zsHyZFq9Ppk4GLQUhVmXEkeqYhLpSWc5d0qcJbBF3wSpt2f3TqsTR'
      }]],
      [[{
        "collection": "users",
        "database": "database",
        "dataSource": "Cluster0",
        "filter": {
          "id": 1
        }
      }]],
      function(code, data)
         if (code < 0) then
           print("HTTP POST request failed")
         else
           print(code, data)
         end
    end)
end

function test_post_db()
  http.post(
    'https://data.mongodb-api.com/app/data-rurzl/endpoint/data/beta/action/insertOne',
    'Content-Type: application/json, Access-Control-Request-Headers: *, api-key: EB601U8qsA4zsHyZFq9Ppk4GLQUhVmXEkeqYhLpSWc5d0qcJbBF3wSpt2f3TqsTR\r\n',
    [[{
      "collection": "users",
      "database": "database",
      "dataSource": "Cluster0",
      "document": {
        "id": 4,
        "pet_colour: "pink",
        friendship_points: 0
      }
    }]],
    function(code, data)
       if (code < 0) then
         print("HTTP POST request failed")
       else
         print(code, data)
       end
  end)
end
