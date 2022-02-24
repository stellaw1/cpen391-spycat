from django.db import models
# Create your models here.

class database(models.Model):
    id = models.AutoField(primary_key=True)
    name = models.CharField(max_length=200)
    points = models.IntegerField()


    def __str__(self):
        return self.name
