#include <OpenPeripheral/OpenPeripheral.hpp>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>

namespace {

class MockDevice final : public OpenPeripheral::IDevice {
public:
    explicit MockDevice(OpenPeripheral::DeviceInfo info) : info_(std::move(info)) {}

    [[nodiscard]] const OpenPeripheral::DeviceInfo& GetInfo() const noexcept override {
        return info_;
    }

private:
    OpenPeripheral::DeviceInfo info_;
};

class MockProvider final : public OpenPeripheral::IProvider {
public:
    explicit MockProvider(std::shared_ptr<OpenPeripheral::IDevice> device)
        : device_(std::move(device)) {}

    [[nodiscard]] std::vector<std::shared_ptr<OpenPeripheral::IDevice>> EnumerateDevices() override {
        return {device_};
    }

private:
    std::shared_ptr<OpenPeripheral::IDevice> device_;
};

void Expect(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "Test failure: " << message << '\n';
        std::exit(EXIT_FAILURE);
    }
}

} // namespace

int main() {
    OpenPeripheral::Context context;
    Expect(context.EnumerateDevices().empty(), "a new context has no devices");

    OpenPeripheral::DeviceInfo expected{42, "Mock Controller", "OpenPeripheral", "Test device"};
    auto device = std::make_shared<MockDevice>(expected);
    context.RegisterProvider(std::make_shared<MockProvider>(device));

    const auto devices = context.EnumerateDevices();
    Expect(devices.size() == 1, "a registered provider exposes its device");
    const auto& info = devices.front()->GetInfo();
    Expect(info.id == expected.id, "device id is retained");
    Expect(info.name == expected.name, "device name is retained");
    Expect(info.manufacturer == expected.manufacturer, "manufacturer is retained");
    Expect(info.description == expected.description, "description is retained");
}
