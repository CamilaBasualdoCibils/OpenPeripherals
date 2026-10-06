#include <OpenPeripheral/OpenPeripherals.hpp>
#include <OpenPeripheral/EvDev/EvdevProvider.hpp>

#include <iostream>
#include <memory>

int main() {
    OpenPeripherals::Instance context;
    context.RegisterProvider(std::make_shared<OpenPeripherals::EvdevProvider>());
    const auto devices = context.EnumerateDevices();

    for (const auto& device : devices) {
        const auto& info = device->GetInfo();
        std::cout << info.name << " (" << info.manufacturer << ") (" << info.id << ")\n";
        
    }

    return 0;
}
