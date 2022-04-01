
-- user
function get_user(username)
  http.get(
    'http://18.191.115.7:8000/user?username=' .. username,
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
    'http://18.191.115.7:8000/user',
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

function put_increment_friendship(username)
  http.post(
    'http://18.191.115.7:8000/increment',
    'Content-Type: application/json\r\n',
    [[{
      "username": "]] .. username .. [["
    }]],
    function(code, data)
       if (code < 0) then
         print("PUT increment friendship request failed")
       else
         print(data)
       end
  end)
end


-- chat
function get_chat(sender, receiver)
  http.get(
    'http://18.191.115.7:8000/chat?sender_id=' .. sender .. '&receiver_id=' .. receiver,
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
    'http://18.191.115.7:8000/chat',
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
function get_friends(username)
  http.get(
    'http://18.191.115.7:8000/friendship?user_id=' .. username,
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
    'http://18.191.115.7:8000/friendship',
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
    'http://18.191.115.7:8000/friendship?user_id=' .. user .. '&friend_id=' .. friend,
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
    'http://18.191.115.7:8000/game?sender_id=' .. sender .. '&receiver_id=' .. receiver,
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
    'http://18.191.115.7:8000/game',
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
    'http://18.191.115.7:8000/game?sender_id=' .. sender .. '&receiver_id=' .. receiver,
    nil,
    function(code, data)
       if (code < 0) then
         print("DELETE friend request failed")
       else
         print(data)
       end
  end)
end
