#pragma once

#include "OpenPeripherals/Core/Discovery/IDiscovery.hpp"
namespace OpenPeripherals
{

    class EvdevDiscovery : public IDiscovery
    {

    public:
      std::vector<PeripheralObservation> Discover() override;

      void Start() override {

      }

      void Stop() override {

      }

      void
      SetEndpointAddedCallback(std::function<void(const Endpoint &)>) override {

      }

      void
      SetEndpointRemovedCallback(std::function<void(EndpointID)>) override {

      }
    };
}