#ifndef USBController_h
#define USBController_h
#include "Arduino.h"

// make sure that it is a supported Architecture
#ifndef ARDUINO_ARCH_AVR
#error "Unsupported Architecture"
#endif

#include "PluggableUSB.h"
#include "HID.h"

#define USBController_D_HIDREPORT(length) { 9, 0x21, 0x11, 0x01, 0, 1, 0x22, lowByte(length), highByte(length) }

typedef struct {
	InterfaceDescriptor hid;
  HIDDescDescriptor desc;
  EndpointDescriptor in;
	EndpointDescriptor out;
} USBControllerHIDDescriptor;
typedef union {
	uint8_t dataInHeader[0];
	uint8_t dataInBlock[0];
	uint8_t dataOutHeader[0];
	uint8_t dataOutBlock[0];
	struct {
		uint8_t dataIn;
		uint8_t dataOut;
	};
} USBControllerDataPacket;

static const uint8_t USBControllerReportDescriptor[] PROGMEM = {
	0x06, 0x00, 0xff,              // USAGE_PAGE (vendor defined page 1)
	0x09, 0x00,                    // USAGE (Undefined)
	0xa1, 0x01,                    // COLLECTION (Application)
	0x85, 0x01,                    //   REPORT_ID (1)
	0x09, 0x00,                    //   USAGE (Undefined)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
	0x75, 0x08,                    //   REPORT_SIZE (8)
	0x95, 0x01,                    //   REPORT_COUNT (1)
	0x81, 0x06,                    //   INPUT (Data,Var,Rel)
	0x85, 0x02,                    //   REPORT_ID (2)
	0x09, 0x00,                    //   USAGE (Undefined)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
	0x75, 0x08,                    //   REPORT_SIZE (8)
	0x95, 0x01,                    //   REPORT_COUNT (1)
	0x91, 0x06,                    //   OUTPUT (Data,Var,Rel)
	0xc0                           // END_COLLECTION
};

#define USBControllerInterface pluggedInterface
#define USBControllerEndpointIn pluggedEndpoint
#define USBControllerEndpointOut (pluggedEndpoint + 1)
#define USBControllerTX USBControllerEndpointIn
#define USBControllerRX USBControllerEndpointOut

class USBController : public PluggableUSBModule {
public:
	USBController();
	int write(const uint8_t *buffer, size_t size);
	int read();
private:

protected:
	uint8_t endpointTypes[2];
	uint8_t protocol;
	uint8_t idle;

	int getInterface(uint8_t *interfaceNumber);
	int getDescriptor(USBSetup &setup);
	bool setup(USBSetup &setup);
};

#endif // USBController_h import guard
