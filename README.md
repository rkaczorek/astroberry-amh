# astroberry-amh
Astroberry Motor HAT provides INDI focuser driver for Adafruit Motor HAT addon board to Raspberry Pi:

# How to start?
First, you need to download and install INDI server and libraries. See [INDI site](http://indilib.org/download.html) for more details.
In most cases it's enough to run:
```
sudo apt-add-repository ppa:mutlaqja/ppa
sudo apt-get update
sudo apt-get install libindi1
```
Second, download and install astroberry-amh

Compiling from source:
```
sudo apt-get install libindi-dev
git clone https://github.com/rkaczorek/astroberry-amh.git
cd astroberry-amh
mkdir build
cd build
cmake ..
make
make install
```
# How to use it?
Start your INDI server with Astroberry Motor HAT driver:

`indiserver -l /var/log/indi -f /var/run/indi -p 7624 indi_amh_focuser`

Start KStars with Ekos, connect to your INDI server and enjoy!

NOTE: You need to have wiringPi installed on your Pi to use this driver. The latest (and original) version of wiringPi is available [here](http://wiringpi.com/download-and-install/)  
You also need to activate I2C support on your Pi before you begin. Make sure you have these two lines in your /boot/config.txt:
```
dtparam=i2c1=on
dtparam=i2c_arm=on

```
