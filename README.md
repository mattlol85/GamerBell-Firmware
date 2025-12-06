# GamerBell-Firmware

Firmware for ESP32 Fitz-Net Gamerbell with OTA update support.

## 🚀 Features

- ESP32-based firmware with Arduino framework
- Over-The-Air (OTA) update support
- Automatic version management via GitHub releases
- CI/CD pipeline with automated builds
- Semantic versioning support

## 📋 Prerequisites

- [PlatformIO Core](https://platformio.org/) or [PlatformIO IDE](https://platformio.org/platformio-ide)
- Python 3.7+ (for PlatformIO)
- ESP32 development board

## 🛠️ Building the Firmware

### Using PlatformIO CLI

```bash
# Install dependencies and build
platformio run

# Build and upload to device
platformio run --target upload

# Monitor serial output
platformio device monitor
```

### Using PlatformIO IDE

1. Open the project in VS Code with PlatformIO extension
2. Click the build button (checkmark icon) in the bottom toolbar
3. Click the upload button (arrow icon) to flash the device

## 📦 OTA Updates

### Configuration

1. Create your configuration file:
   ```bash
   cp src/config.h.example src/config.h
   ```

2. Update WiFi credentials in `src/config.h`:
   ```cpp
   #define WIFI_SSID "YOUR_SSID"
   #define WIFI_PASSWORD "YOUR_PASSWORD"
   ```

3. Update the OTA password for security:
   ```cpp
   #define OTA_PASSWORD "your_secure_password"
   ```

**Note:** `config.h` is gitignored to prevent accidentally committing credentials.

### Performing OTA Update

#### Method 1: Via PlatformIO

```bash
# Update the IP address in platformio.ini
# Then run:
platformio run --target upload
```

#### Method 2: Via Arduino IDE

1. Download the `.bin` file from the [releases page](https://github.com/mattlol85/GamerBell-Firmware/releases)
2. In Arduino IDE, go to Sketch → Export compiled Binary
3. Use the ESP32 OTA update tool to upload the firmware

#### Method 3: Via Web Browser (if web OTA is implemented)

1. Navigate to `http://<device-ip>/update`
2. Select the downloaded `.bin` file
3. Click "Update"

## 🏷️ Version Management

This project uses semantic versioning (MAJOR.MINOR.PATCH).

### Creating a New Release

1. Create and push a version tag:
   ```bash
   git tag -a v1.0.0 -m "Release version 1.0.0"
   git push origin v1.0.0
   ```

2. GitHub Actions will automatically:
   - Build the firmware with version information embedded
   - Create a GitHub release
   - Attach compiled binaries (`.bin` and `.elf` files)
   - Generate checksums for verification

3. Download the firmware from the [releases page](https://github.com/mattlol85/GamerBell-Firmware/releases)

### Version Information

The firmware embeds version information that can be viewed in the serial output:
- Version number (MAJOR.MINOR.PATCH)
- Git commit hash
- Build timestamp

## 🔄 CI/CD Workflows

### Build Workflow

Triggered on:
- Push to `main` or `develop` branches
- Pull requests to `main`

Actions:
- Compiles the firmware
- Uploads build artifacts
- Validates the build process

### Release Workflow

Triggered on:
- Push of tags matching `v*.*.*` pattern (e.g., v1.0.0)

Actions:
- Builds firmware with version information
- Creates GitHub release
- Attaches firmware binaries
- Generates version manifest and checksums

## 📁 Project Structure

```
GamerBell-Firmware/
├── .github/
│   └── workflows/
│       ├── build.yml      # Build workflow
│       └── release.yml    # Release workflow
├── include/
│   └── version.h          # Version definitions
├── lib/                   # Project-specific libraries
├── src/
│   └── main.cpp           # Main firmware code
├── test/                  # Unit tests
├── platformio.ini         # PlatformIO configuration
└── README.md
```

## 🔧 Configuration

### platformio.ini

Key configuration options:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200

; OTA settings
upload_protocol = espota
upload_port = 192.168.1.100  ; Your device IP
```

## 🐛 Troubleshooting

### OTA Update Fails

1. Verify the device is on the same network
2. Check the OTA password matches
3. Ensure sufficient flash memory is available
4. Verify the IP address is correct

### Build Fails

1. Clean the build directory: `platformio run --target clean`
2. Update PlatformIO: `platformio upgrade`
3. Clear cache: `rm -rf .pio`

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## 📞 Support

For issues and questions, please use the [GitHub Issues](https://github.com/mattlol85/GamerBell-Firmware/issues) page.
