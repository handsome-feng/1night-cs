```
Install drivers and tools:
sudo apt install alsa-firmware-loaders alsa-oss alsa-source alsa-tools alsa-tools-gui alsa-utils alsamixergui

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
