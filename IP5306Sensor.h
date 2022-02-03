#include "esphome.h"
#include "IP5306.h"

class IP5306Sensor : public PollingComponent {
 public:
  IP5306 ip5306;

  Sensor *battery_level = new Sensor();
  BinarySensor *is_charge_connected = new BinarySensor();
  BinarySensor *is_charge_full = new BinarySensor();

  
  IP5306Sensor() : PollingComponent(5000) {}

  float get_setup_priority() const override { return esphome::setup_priority::HARDWARE; }

  void setup() override {
	 ip5306.setup();
  }
  void update() override {
    int _battery_level = ip5306.getBatteryLevel();
    battery_level->publish_state(_battery_level);

    int _is_charge_connected = ip5306.isChargerConnected();
    is_charge_connected->publish_state(_is_charge_connected != 0);

    int _is_charge_full = ip5306.isChargerConnected();
    is_charge_full->publish_state(_is_charge_full != 0);
  }
};