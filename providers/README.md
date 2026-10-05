# Provider boundary

The OpenPeripheral core owns common provider and device interfaces plus
in-process registration. It deliberately contains no platform discovery code.

Future implementations may live here or in separate projects, including evdev,
BlueZ, OpenXR, and vendor-specific providers. Each provider adapts an OS or
vendor API into `IProvider` and `IDevice`; the core must not acquire those
systems as dependencies.

Dynamic provider discovery, manifests, and hotplug support are future work.
