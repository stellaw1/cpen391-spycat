import csv
from django.shortcuts import render
from .models import database
import os
import pymongo
# Create your views here.


def get_points(request):
    template = 'leaderboard.html'
    os.system("rm db.sqlite3 && python3 manage.py migrate --run-syncdb")

    cluster = pymongo.MongoClient("mongodb+srv://admin:spycatadmin@cluster0.p2llx.mongodb.net/database?retryWrites=true&w=majority")
    db = cluster["database"]
    collection = db["users"]
    results = collection.find({})

    for result in results:
        database.objects.update_or_create(name = result["username"], points = result["friendship_points"])

    objects = database.objects.order_by('-points')

    return render(request,template, {'objects': objects})
    
