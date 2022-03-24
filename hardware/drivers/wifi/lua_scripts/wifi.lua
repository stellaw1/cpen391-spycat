station_cfg = {}
station_cfg.ssid = "Omegalul"
station_cfg.pwd = "pepelaugh"
station_cfg.save = true

-- set wifi to AP mode
wifi_got_ip_event = function(T)
  local site = "jsonplaceholder.typicode.com"
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
  
  test_post_toilet()

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

function test_get_json()
  http.get("http://jsonplaceholder.typicode.com/todos/1", nil, function(code, data)
       if (code < 0) then
         print("HTTP GET request failed")
       else
         print(code, data)
       end
  end)
end

function test_post_toilet()
    http.post(
      'http://ptsv2.com/t/tn6gz-1648092962/post', 
      'Content-Type: application/json\r\n', 
      [[{"dataSource": "Cluster0",
      "database": "todo",
      "collection": "tasks",
      "document": {
        "status": "open",
        "text": "Do the dishes"
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
