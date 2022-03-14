from weather_fetch import *
from PIL import Image
import matplotlib.pyplot as plt


# Test:
city_name = input("City Name: ")
background, mood = weather_background_mood(city_name)
if background == -1 or mood == -1:
    print("ERROR: Wrong cityname passed in")
else:
    print("Display Background: " + background + "\n" + "Pet Mood: " + mood)

    a = plt.imread("http://openweathermap.org/img/w/" + background + ".png", background + ".png")
    plt.imshow(a)
    plt.show()
