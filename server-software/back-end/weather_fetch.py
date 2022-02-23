# Sample outputs:
# Enter city name : vancouver
# description = clear sky
# Temperature (in celsius unit) = -4.38
# Humidity = 48

import pyowm
from pyowm import OWM

# Search weather accoring to the given city name
def weather_fetch(city_name):
    # openweathermap api key
    owm = OWM('9e12875a014e100a631a56a3b16f74c9')
    mgr = owm.weather_manager()
    # Change unit celsius/kelvin
    unit = "celsius"
    while True:
        try:
            observation = mgr.weather_at_place(city_name)
            w = observation.weather

            w.detailed_status         # 'clear sky'
            w.wind()                  # {'speed': #, 'deg': #}
            w.humidity                # #
            w.temperature('celsius')  # {'temp_max': #, 'temp': #, 'temp_min': #}
            w.rain                    # {}
            w.heat_index              # None
            w.clouds                  # #
            w.weather_icon_name       # 10d
            return 1, w.detailed_status, w.temperature(unit)['temp'], w.weather_icon_name
            break
        except pyowm.commons.exceptions.NotFoundError:
            return 0, 0, 0, 0
            break

# Determine mood of pet and background
def weather_background_mood (city_name):
    bool, weather, temp, icon = weather_fetch(city_name)
    if bool == 0:
        return -1, -1
    else:
        background = icon
        mood_opt = {
            # Day time
            "01d" : "happy",
            "02d" : "happy",
            "03d" : "happy",
            "04d" : "mid",
            "09d" : "mid",
            "10d" : "mid",
            "11d" : "sad",
            "13d" : "happy",
            "50d" : "mid",

            # Night time
            "01n": "happy",
            "02n": "happy",
            "03n": "happy",
            "04n": "mid",
            "09n": "mid",
            "10n": "mid",
            "11n": "sad",
            "13n": "happy",
            "50n": "mid"
        }
        mood = mood_opt[icon]
        return background, mood
