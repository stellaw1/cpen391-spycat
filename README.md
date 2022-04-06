# SPYCAT

------

### EC2 node server
URL: [http://3.140.252.116:8000](http://3.140.252.116:8000)
Code: https://github.com/stellaw1/l2b-15-something-node-server

### Leaderboard website
URL: [http://server.yslalan.xyz:8888/](http://server.yslalan.xyz:8888/)
Code: https://github.com/stellaw1/l2b-15-something-django-website

### Linux on De1
1. Load `/hardware/soc_system.rbf`
2. Compile and run `/hardware/drivers/UI/gui_logic.c` in Linux with
```
gcc ./gui_logic.c -lm -lpython3.5m -o project
```
### Software Dependencies on DE1
 - Python 2.7
 - Python 3.5
 - django 4.0.2
 - pymongo
