# SPYCAT

------
## About
![img](https://github.com/stellaw1/cpen391-spycat/blob/main/Docs/spycat.png?raw=true)

SPYCAT (Smart Pet You Care About Tons) is a virtual pet system built on a De1-SoC FPGA board. Its aim is to improve the user’s quality of life by providing companionship and virtual interaction with friends. 

### [Demo](https://youtu.be/jjGQYYytCDU)

------
## Setup
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
 - python-opencv
