#ifndef VERSION_H
#define VERSION_H

// Version information - these can be overridden by build flags
#ifndef VERSION_MAJOR
#define VERSION_MAJOR 0
#endif

#ifndef VERSION_MINOR
#define VERSION_MINOR 1
#endif

#ifndef VERSION_PATCH
#define VERSION_PATCH 0
#endif

// Build a version string
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define VERSION_STRING TOSTRING(VERSION_MAJOR) "." TOSTRING(VERSION_MINOR) "." TOSTRING(VERSION_PATCH)

// Git commit hash (if available from build)
#ifndef GIT_COMMIT
#define GIT_COMMIT "unknown"
#endif

#endif // VERSION_H
