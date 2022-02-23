# Sample outputs:
# Enter city name : vancouver
# description = clear sky
# Temperature (in celsius unit) = -4.38
# Humidity = 48

import pyowm
from pyowm import OWM

owm = OWM('9e12875a014e100a631a56a3b16f74c9') #openweathermap api key
mgr = owm.weather_manager()
bool = 1
# Change unit celsius/kelvin
unit = "celsius"
# Search for current weather in given region
while True:
    city_name = input("Enter city name : ")
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

            print("description = " +
                                str(w.detailed_status) +
                "\nTemperature (in " + unit + " unit) = " +
                                str(w.temperature(unit)['temp']) +
                "\nHumidity = " +
                                str(w.humidity)
                )
            break
        except pyowm.commons.exceptions.NotFoundError:
            print("Oops! Invalid City Name. Try again...")
            break    