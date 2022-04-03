URL = 'http://3.140.252.116:8000'

-- user
function get_user(username)
  http.get(
    URL .. '/user?username=' .. username,
    nil,
    function(code, data)
       if (code < 0) then
         print("GET user request failed")
       else
         print(data)
       end
  end)
end

function post_user(username, pet_colour)
  http.post(
    URL .. '/user',
    'Content-Type: application/json\r\n',
    [[{
      "username": "]] .. username .. [[",
      "pet_colour": "]] .. pet_colour .. [["
    }]],
    function(code, data)
       if (code < 0) then
         print("POST user request failed")
       else
         print(data)
       end
  end)
end


-- chat
function get_chat(sender, receiver)
  http.get(
    URL .. '/chat?sender_id=' .. sender .. '&receiver_id=' .. receiver,
    nil,
    function(code, data)
       if (code < 0) then
         print("GET chat request failed")
       else
         print(data)
       end
  end)
end

function post_chat(sender, receiver, message)
  http.post(
    URL .. '/chat',
    'Content-Type: application/json\r\n',
    [[{
      "sender_id": "]] .. sender .. [[",
      "receiver_id": "]] .. receiver .. [[",
      "message": "]] .. message .. [["
    }]],
    function(code, data)
       if (code < 0) then
         print("POST chat request failed")
       else
         print(data)
       end
  end)
end


-- friendship
function get_is_friends(user, friend)
  http.get(
    URL .. '/isFriends?user_id=' .. user .. '&friend_id=' .. friend,
    nil,
    function(code, data)
       if (code < 0) then
         print("GET is friends request failed")
       else
         print(data)
       end
  end)
end

function get_friends(username)
  http.get(
    URL .. '/friendship?user_id=' .. username,
    nil,
    function(code, data)
       if (code < 0) then
         print("GET friends request failed")
       else
         print(data)
       end
  end)
end

function post_friendship(user, friend)
  http.post(
    URL .. '/friendship',
    'Content-Type: application/json\r\n',
    [[{
      "user_id": "]] .. user .. [[",
      "friend_id": "]] .. friend .. [["
    }]],
    function(code, data)
       if (code < 0) then
         print("POST friend request failed")
       else
         print(data)
       end
  end)
end

function delete_friendship(user, friend)
  http.delete(
    URL .. '/friendship?user_id=' .. user .. '&friend_id=' .. friend,
    nil,
    function(code, data)
       if (code < 0) then
         print("DELETE friend request failed")
       else
         print(data)
       end
  end)
end


-- game
function get_game(sender, receiver)
  http.get(
    URL .. '/game?sender_id=' .. sender .. '&receiver_id=' .. receiver,
    nil,
    function(code, data)
       if (code < 0) then
         print("GET game request failed")
       else
         print(data)
       end
  end)
end

function post_game(sender, receiver, choice)
  http.post(
    URL .. '/game',
    'Content-Type: application/json\r\n',
    [[{
      "sender_id": "]] .. sender .. [[",
      "receiver_id": "]] .. receiver .. [[",
      "choice": "]] .. choice .. [["
    }]],
    function(code, data)
       if (code < 0) then
         print("POST game request failed")
       else
         print(data)
       end
  end)
end

function delete_game(sender, receiver)
  http.delete(
    URL .. '/game?sender_id=' .. sender .. '&receiver_id=' .. receiver,
    nil,
    function(code, data)
       if (code < 0) then
         print("DELETE friend request failed")
       else
         print(data)
       end
  end)
end

-- weather
function get_weather()
  http.delete(
    URL .. '/weather',
    nil,
    function(code, data)
       if (code < 0) then
         print("GET weather request failed")
       else
         print(data)
       end
  end)
end
