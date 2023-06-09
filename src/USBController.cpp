#include "USBController.h"

USBController::USBController() : PluggableUSBModule(2, 1, endpointTypes) {
	endpointTypes[0] = EP_TYPE_INTERRUPT_IN; //Use interrupt transfer method
	endpointTypes[1] = EP_TYPE_INTERRUPT_OUT;
	PluggableUSB().plug(this);
}

int USBController::getInterface(uint8_t *interfaceNumber) {
	interfaceNumber[0] += 1;
	USBControllerHIDDescriptor interfaceDescriptor = {
		D_INTERFACE(USBControllerInterface, 2, USB_DEVICE_CLASS_HUMAN_INTERFACE, 0, 0),
		USBController_D_HIDREPORT(sizeof(USBControllerReportDescriptor)),
		D_ENDPOINT(USB_ENDPOINT_IN(USBControllerEndpointIn), USB_ENDPOINT_TYPE_BULK, USB_EP_SIZE, 0),
		D_ENDPOINT(USB_ENDPOINT_OUT(USBControllerEndpointOut), USB_ENDPOINT_TYPE_BULK, USB_EP_SIZE, 0),
	};
	return USB_SendControl(0, &interfaceDescriptor, sizeof(interfaceDescriptor));
}

int USBController::getDescriptor(USBSetup &setup) {
	// code copied and modified from NicoHood's HID-Project
	// check if it is a HID class Descriptor request
	if (setup.bmRequestType != REQUEST_DEVICETOHOST_STANDARD_INTERFACE) { return 0; }
	if (setup.wValueH != HID_REPORT_DESCRIPTOR_TYPE) { return 0; }

	// In a HID Class Descriptor wIndex cointains the interface number
	if (setup.wIndex != pluggedInterface) { return 0; }

	protocol = HID_REPORT_PROTOCOL;

	return USB_SendControl(TRANSFER_PGM, USBControllerReportDescriptor, sizeof(USBControllerReportDescriptor));
}

bool USBController::setup(USBSetup &setup) {
	// code copied from NicoHood's HID-Project
	if (pluggedInterface != setup.wIndex) {
		return false;
	}

	uint8_t request = setup.bRequest;
	uint8_t requestType = setup.bmRequestType;

	if (requestType == REQUEST_DEVICETOHOST_CLASS_INTERFACE)
	{
		if (request == HID_GET_REPORT) {
			// TODO: HID_GetReport();
			return true;
		}
		if (request == HID_GET_PROTOCOL) {
			// TODO: Send8(protocol);
			return true;
		}
	}

	if (requestType == REQUEST_HOSTTODEVICE_CLASS_INTERFACE)
	{
		if (request == HID_SET_PROTOCOL) {
			protocol = setup.wValueL;
			return true;
		}
		if (request == HID_SET_IDLE) {
			idle = setup.wValueL;
			return true;
		}
		if (request == HID_SET_REPORT)
		{
		}
	}

	return false;
}

int USBController::write(const uint8_t *buffer, size_t size) {
	return USB_Send(USBControllerTX, buffer, size);
}

int USBController::read() {
	if (USB_Available(USBControllerRX)) {
		return USB_Recv(USBControllerRX);
	}
	else {
		return 0;
	}
}
