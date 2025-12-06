# Release Process

This document describes how to create releases for the GamerBell Firmware.

## Semantic Versioning

We follow [Semantic Versioning](https://semver.org/) (MAJOR.MINOR.PATCH):

- **MAJOR**: Incompatible API changes or major features
- **MINOR**: Backwards-compatible functionality additions
- **PATCH**: Backwards-compatible bug fixes

## Creating a Release

### Step 1: Update Version

Ensure your code is ready for release and all tests pass.

### Step 2: Create and Push a Tag

```bash
# Create an annotated tag with version
git tag -a v1.0.0 -m "Release version 1.0.0 - Initial release"

# Push the tag to GitHub
git push origin v1.0.0
```

### Step 3: Automated Release

Once the tag is pushed, GitHub Actions will automatically:

1. Build the firmware with the version information embedded
2. Create a GitHub Release with the tag
3. Attach the compiled firmware binaries:
   - `gamerbell-firmware-v1.0.0.bin` - Binary for OTA updates
   - `gamerbell-firmware-v1.0.0.elf` - ELF file for debugging
4. Generate a `version.json` file with metadata
5. Create SHA256 checksums for all artifacts

### Step 4: Verify Release

1. Go to the [Releases page](https://github.com/mattlol85/GamerBell-Firmware/releases)
2. Verify the release was created with all artifacts
3. Download and test the firmware if needed

## Release Checklist

Before creating a release:

- [ ] All changes are committed and pushed
- [ ] Code builds successfully
- [ ] Tests pass (if applicable)
- [ ] Documentation is updated
- [ ] CHANGELOG is updated (if you maintain one)
- [ ] Version tag follows semantic versioning

## Example Tag Commands

```bash
# Major release (breaking changes)
git tag -a v2.0.0 -m "Release v2.0.0 - Major refactoring"

# Minor release (new features)
git tag -a v1.1.0 -m "Release v1.1.0 - Add new sensor support"

# Patch release (bug fixes)
git tag -a v1.0.1 -m "Release v1.0.1 - Fix WiFi connection issue"

# Push the tag
git push origin <tag-name>
```

## Deleting a Tag (if needed)

If you need to delete a tag:

```bash
# Delete local tag
git tag -d v1.0.0

# Delete remote tag
git push origin :refs/tags/v1.0.0
```

## Pre-releases

For pre-release versions, you can use tags like:

```bash
git tag -a v1.0.0-beta.1 -m "Beta release"
git tag -a v1.0.0-rc.1 -m "Release candidate"
```

The release workflow will still trigger, but you should manually mark the release as a pre-release in GitHub.

## OTA Update Distribution

Once a release is published:

1. Users can download the `.bin` file from the releases page
2. The firmware can be uploaded via OTA to devices
3. The `version.json` file can be used to check for updates programmatically

## Rollback

If a release has issues:

1. Create a new patch release with the fix
2. Or delete the problematic release and recreate it with fixes
3. Communicate the issue to users who may have updated
