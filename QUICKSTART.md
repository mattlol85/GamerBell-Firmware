# Quick Start Guide

Get your GamerBell firmware up and running in minutes!

## 🚀 First Time Setup

### 1. Install Prerequisites

```bash
# Install Python 3.7 or higher
# Then install PlatformIO
pip install platformio
```

### 2. Clone the Repository

```bash
git clone https://github.com/mattlol85/GamerBell-Firmware.git
cd GamerBell-Firmware
```

### 3. Configure WiFi

```bash
# Copy the example config
cp src/config.h.example src/config.h

# Edit src/config.h with your WiFi credentials
# Update WIFI_SSID and WIFI_PASSWORD
```

### 4. Build and Upload

```bash
# Build the firmware
platformio run

# Connect your ESP32 via USB and upload
platformio run --target upload

# Monitor serial output
platformio device monitor
```

## 📱 Using OTA Updates

### Initial Setup

1. Flash the firmware via USB the first time
2. Note the IP address shown in the serial monitor
3. Update `platformio.ini` with your device's IP address:
   ```ini
   upload_port = 192.168.1.XXX  ; Your device IP
   ```

### Updating via OTA

```bash
# After initial USB flash, use OTA for subsequent updates
platformio run --target upload
```

## 🏷️ Creating Your First Release

### 1. Make Your Changes

Edit the code as needed and test thoroughly.

### 2. Commit Your Changes

```bash
git add .
git commit -m "Add awesome feature"
git push
```

### 3. Create a Release Tag

```bash
# For initial release
git tag -a v0.1.0 -m "Initial release"
git push origin v0.1.0
```

### 4. Check GitHub Actions

1. Go to your repository on GitHub
2. Click on "Actions" tab
3. Watch the "Release" workflow build your firmware
4. Once complete, go to "Releases" to download the binary

## 📥 Installing Releases on Device

### Via OTA (Recommended)

1. Download the `.bin` file from releases
2. Use PlatformIO or Arduino IDE OTA update
3. Or implement web-based OTA in your firmware

### Via USB

```bash
# Use esptool to flash directly
pip install esptool
esptool.py --port /dev/ttyUSB0 write_flash 0x10000 firmware.bin
```

## 🔍 Troubleshooting

### Build Fails

```bash
# Clean build directory
platformio run --target clean

# Try building again
platformio run
```

### Can't Connect to WiFi

1. Check your WiFi credentials in `src/config.h`
2. Ensure your router is on 2.4GHz (ESP32 doesn't support 5GHz)
3. Check serial monitor for error messages

### OTA Update Fails

1. Verify device IP address
2. Check that device is on same network
3. Verify OTA password matches
4. Ensure device is running and not in deep sleep

## 📚 Next Steps

- Read the full [README.md](README.md) for detailed documentation
- Check [.github/RELEASE.md](.github/RELEASE.md) for release process
- Customize `src/main.cpp` for your specific needs
- Add your application logic to the `loop()` function

## 💡 Tips

- Always test builds locally before creating releases
- Use semantic versioning for your releases
- Keep the OTA feature enabled for easy updates
- Monitor serial output during development
- Use descriptive commit messages for better tracking

## 🆘 Getting Help

- Check the [Issues](https://github.com/mattlol85/GamerBell-Firmware/issues) page
- Review PlatformIO documentation for ESP32
- Join ESP32 community forums

Happy coding! 🎉
