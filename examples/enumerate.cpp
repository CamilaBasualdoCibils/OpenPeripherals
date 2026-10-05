#include <OpenPeripheral/OpenPeripheral.hpp>

#include <iostream>

int main() {
    OpenPeripheral::Context context;
    const auto devices = context.EnumerateDevices();

    for (const auto& device : devices) {
        const auto& info = device->GetInfo();
        std::cout << info.name << " (" << info.manufacturer << ")\n";
    }

    return 0;
}
