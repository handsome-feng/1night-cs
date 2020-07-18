```
Check the device:
cat /proc/asound/cards
sudo lshw -numeric -class multimedia

Bluetooth:
sudo apt install pulseaudio-module-bluetooth
pactl load-module module-bluetooth-discover

Restart pulseaudio:
pulseaudio -k
pulseaudio -D
```
