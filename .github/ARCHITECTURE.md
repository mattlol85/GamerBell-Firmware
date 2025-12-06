# Architecture Overview

This document describes the architecture and workflow of the GamerBell Firmware project.

## 🏗️ Project Structure

```
GamerBell-Firmware/
│
├── .github/                    # GitHub configuration
│   ├── workflows/              # CI/CD workflows
│   │   ├── build.yml          # Build on push/PR
│   │   ├── release.yml        # Release on version tag
│   │   └── pr-validation.yml  # Validate pull requests
│   ├── ISSUE_TEMPLATE/        # Issue templates
│   ├── RELEASE.md             # Release process documentation
│   └── ARCHITECTURE.md        # This file
│
├── include/                   # Header files
│   └── version.h              # Version management
│
├── src/                       # Source code
│   ├── main.cpp               # Main firmware application
│   └── config.h.example       # Configuration template
│
├── lib/                       # Project libraries
├── test/                      # Unit tests
│
├── platformio.ini             # PlatformIO configuration
├── README.md                  # Main documentation
├── QUICKSTART.md              # Quick start guide
├── CHANGELOG.md               # Version history
└── LICENSE                    # MIT License

```

## 🔄 CI/CD Workflow

### Development Flow

```
┌─────────────┐
│   Develop   │
│    Code     │
└──────┬──────┘
       │
       ↓
┌─────────────┐
│  Commit &   │
│    Push     │
└──────┬──────┘
       │
       ↓
┌─────────────────────────┐
│  GitHub Actions:        │
│  - Build Workflow       │
│  - Compile Firmware     │
│  - Upload Artifacts     │
└──────┬──────────────────┘
       │
       ↓
┌─────────────┐
│   Review    │
│   & Test    │
└──────┬──────┘
       │
       ↓
┌─────────────┐
│   Merge to  │
│    Main     │
└─────────────┘
```

### Release Flow

```
┌─────────────┐
│  Create Tag │
│  (v1.0.0)   │
└──────┬──────┘
       │
       ↓
┌──────────────────────────┐
│  GitHub Actions:         │
│  - Release Workflow      │
│  - Build with Version    │
│  - Create Release        │
│  - Attach Binaries       │
└──────┬───────────────────┘
       │
       ↓
┌──────────────────────────┐
│  GitHub Release:         │
│  - firmware.bin          │
│  - firmware.elf          │
│  - version.json          │
│  - checksums.txt         │
└──────┬───────────────────┘
       │
       ↓
┌─────────────┐
│  Download   │
│  & Deploy   │
└─────────────┘
```

## 📦 Build Process

### Standard Build

1. **Checkout Code**: Clone repository with full history
2. **Setup Environment**: Install Python and PlatformIO
3. **Cache Dependencies**: Cache PlatformIO packages
4. **Extract Version**: Get version from git tag or commit
5. **Build Firmware**: Compile with version information
6. **Generate Artifacts**: Create distributable binaries
7. **Upload**: Store artifacts for download

### Release Build

The release build includes additional steps:

1. **Parse Version Tag**: Extract MAJOR.MINOR.PATCH from tag
2. **Embed Version**: Compile with version flags
3. **Create Manifest**: Generate version.json with metadata
4. **Calculate Checksums**: SHA256 for all binaries
5. **Create Release**: Attach all artifacts to GitHub Release
6. **Publish**: Make release available for download

## 🔐 Version Management

### Version Embedding

Versions are embedded at compile time using preprocessor definitions:

```cpp
// From version.h
#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_PATCH 0
#define VERSION_STRING "1.0.0"
#define GIT_COMMIT "abc123"
```

### Build Flags

Versions are passed to the compiler via build flags:

```bash
-D VERSION_MAJOR=1
-D VERSION_MINOR=0
-D VERSION_PATCH=0
-D GIT_COMMIT="abc123"
```

### Runtime Display

The firmware displays version information at startup:

```
========================================
GamerBell Firmware
Version: 1.0.0
Git Commit: abc123
========================================
```

## 📡 OTA Update Architecture

### Network Setup

```
┌──────────┐         WiFi         ┌──────────┐
│  ESP32   │ ←──────────────────→ │  Router  │
│  Device  │                       └──────────┘
└────┬─────┘                            ↑
     │                                  │
     │ OTA Update                       │
     ↓                                  │
┌──────────┐                            │
│  Local   │ ←──────────────────────────┘
│  Machine │   platformio run --target upload
└──────────┘
```

### OTA Update Process

1. **Initial Flash**: First upload via USB
2. **Network Connection**: Device connects to WiFi
3. **OTA Service**: ArduinoOTA service starts
4. **Update Trigger**: User initiates OTA update
5. **Authentication**: OTA password verification
6. **Transfer**: New firmware uploaded over WiFi
7. **Flash**: Device writes new firmware
8. **Reboot**: Device restarts with new firmware

## 🚀 Deployment Options

### Option 1: USB Flash (Initial)

```
Developer → USB Cable → ESP32 Device
```

### Option 2: OTA Update (Subsequent)

```
Developer → WiFi Network → ESP32 Device
```

### Option 3: GitHub Release (Distribution)

```
GitHub Release → Download → Upload to Device
```

## 🛡️ Security Considerations

### OTA Security

- Password-protected OTA updates
- Same network requirement
- Authentication before transfer

### Configuration Security

- WiFi credentials in config.h (not committed)
- OTA password should be changed from default
- Consider implementing:
  - Firmware signature verification
  - Encrypted communications
  - Secure boot

## 📊 Workflow Triggers

### Build Workflow

- **Push to**: `main`, `develop`
- **Pull Request to**: `main`
- **Action**: Build and validate

### Release Workflow

- **Tag Push**: `v*.*.*` (e.g., v1.0.0)
- **Action**: Build, release, and publish

### PR Validation Workflow

- **Pull Request to**: `main`, `develop`
- **Action**: Validate code compiles and structure

## 🔧 Configuration Management

### User Configuration

Users copy and customize:

```bash
cp src/config.h.example src/config.h
# Edit config.h with personal settings
```

### Build Configuration

Platform settings in `platformio.ini`:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
```

### Workflow Configuration

CI/CD settings in `.github/workflows/`:

- Python version
- PlatformIO version
- Cache strategy
- Build flags

## 📈 Future Enhancements

Potential improvements:

- [ ] Web-based OTA update interface
- [ ] Automatic update checking
- [ ] Firmware rollback capability
- [ ] A/B partition updates
- [ ] Firmware signature verification
- [ ] Update server integration
- [ ] Binary diff updates (smaller downloads)
- [ ] Multi-board support
- [ ] Unit test framework
- [ ] Code coverage reporting

## 🔗 External Dependencies

- **PlatformIO**: Build system and package manager
- **ESP32 Arduino Core**: Framework for ESP32
- **ArduinoOTA**: OTA update library
- **GitHub Actions**: CI/CD platform

## 📚 References

- [PlatformIO Documentation](https://docs.platformio.org/)
- [ESP32 Documentation](https://docs.espressif.com/projects/esp-idf/)
- [Arduino OTA Updates](https://arduino-esp8266.readthedocs.io/en/latest/ota_updates/readme.html)
- [GitHub Actions Documentation](https://docs.github.com/en/actions)
