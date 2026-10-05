# OpenPeripheral

OpenPeripheral is a hardware capability and peripheral abstraction layer.
Devices will expose what they can do rather than requiring applications to
understand specific categories of hardware.

```
Physical Hardware
       ↓
OS / Vendor API
       ↓
OpenPeripheral Provider
       ↓
OpenPeripheral
       ↓
Application / VISR
```

OpenPeripheral is independent of VISR, although VISR is an intended consumer.
Provider implementations are kept outside the core and can later support
platform, vendor, and protocol-specific hardware.

Future devices may expose combinations of controls, state, events, streams,
operations, and resources. The capability specification is still under
development; this bootstrap intentionally implements only provider registration
and device enumeration.

## Build

The default preset has no dependencies:

```sh
cmake --preset default
cmake --build --preset default
ctest --preset default
./build/default/examples/openperipheral-enumerate
```

For a vcpkg-managed build, set `VCPKG_ROOT` and use the `vcpkg` preset.

## Consumer use

After installation, consumers can use:

```cmake
find_package(OpenPeripheral CONFIG REQUIRED)
target_link_libraries(MyProgram PRIVATE OpenPeripheral::OpenPeripheral)
```
