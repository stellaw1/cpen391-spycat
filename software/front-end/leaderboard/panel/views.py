import csv
from django.shortcuts import render
from .models import database
import os
# Create your views here.

def get_points(request):
    template = 'leaderboard.html'
    os.system("rm db.sqlite3 && python manage.py migrate --run-syncdb")
    with open('./data.csv', newline='', encoding='utf-8') as f:
        reader = csv.reader(f)
        for column in reader:
            database.objects.update_or_create(name = column[0], points = column[1])
    objects = database.objects.order_by('-points')
    return render(request,template, {'objects': objects})
    
