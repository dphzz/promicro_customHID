#include <Arduino.h>
#include <HID_custom.h>

static const uint8_t _hidReportDescriptor[] PROGMEM = {

		//  Test custom HID device descriptor code
		// Usage page (Vendor-defined)
		0x06, 0xFF, 0xFF,

		// Usage (Vendor-defined)
		0x09, 0x01,

		// Collection (Application)
		0xA1, 0x01,

			// Report ID (1)
			0x85, 0x01,

			// Input report (2 bytes)
			0x09, 0x02,        // Usage (Vendor-defined)
			0x15, 0x00,        // Logical minimum (0)
			0x26, 0xFF, 0x00,  // Logical maximum (255)
			0x75, 0x08,        // Report size (8 bits)
			0x95, 0x03,        // Report count (3 bytes)
			0x81, 0x02,        // Input (Data, Variable, Absolute)

			// Output report (1 byte)
			0x09, 0x03,        // Usage (Vendor-defined)
			0x15, 0x00,        // Logical minimum (0)
			0x26, 0xFF, 0x00,  // Logical maximum (255)
			0x75, 0x08,        // Report size (8 bits)
			0x95, 0x03,        // Report count (2 bytes)
			0x91, 0x02,        // Output (Data, Variable, Absolute)

		// End collection
		0xC0                         // END_COLLECTION
	};

//USB receive variable
uint8_t rx_buffer[64];
uint8_t tx_buffer[64] = {0x17, 0x16};

void setup(){
    static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
	HID().AppendDescriptor(&node);
}

int last_send_time = millis();
int last_serial_time = millis();
int last_read_time = millis();
void loop(){
    if ((millis() - last_send_time) > 100)
    {
        // byte data[2] = {0x17, 0x16};
        HID().SendReport(1, tx_buffer, 3);
        last_send_time = millis();

    }

  if(HID().Receive_data(1, rx_buffer, 3))
  {
    if ((uint8_t)rx_buffer[1] != 0x18 && (uint8_t)rx_buffer[1] != 0x1C && (uint8_t)rx_buffer[1] != 0x0C)
    {  //Use a control byte to reject irrelevant data such as 0x18, 0x1C, 0x0C
      tx_buffer[0] = (uint8_t)rx_buffer[1];
      tx_buffer[1] = (uint8_t)rx_buffer[2];

    }
  }


}