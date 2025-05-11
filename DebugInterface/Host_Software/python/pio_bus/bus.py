# I use Windows, libusb_package rids of a hassle to load libusb manually
import libusb_package
import usb

VID = 0x04D8
PID = 0x003F
PROD = "Parallel bus bridge"

class PIOBusDevice:
    def __init__(self, dev):
        self.dev = dev
        dev.reset()
        self.endpoint_in = dev[0][(0,0)][0]
        self.endpoint_out = dev[0][(0,0)][1]

    def _transact(self, request):
        assert self.endpoint_out.write(request) == 65
        reply = self.dev.read(self.endpoint_in.bEndpointAddress, 64, 1000)
        for i in range(0, 10):
            if reply[i] != request[i]:
                print("Protocol failure!")
                print("Request:", request)
                print("Reply  :", reply)
                raise IOError()
        return reply[10:]

    def reset(self):
        data = bytearray(64)
        data[1] = 0x53 # 'S'
        data[11] = 1
        self._transact(data)
        
    def write(self, addr, data):
        report = bytearray(64)
        report[0] = 0x57 #'W'
        report[1] = len(data);
        report[2] = addr
        for i in range(0, len(data)):
            report[10 + i] = data[i]
        self._transact(report)
        
    def read(self, addr, length):
        report = bytearray(64)
        report[0] = 0x52 #'R'
        report[1] = length;
        report[2] = addr
        reply = self._transact(report)
        return reply[:length]

def find_devices():
    bus_devs = []

    for dev in libusb_package.find(idVendor=VID, idProduct=PID, find_all=True):
        if str(usb.util.get_string(dev, dev.iProduct)) == PROD:
            bus_devs.append(PIOBusDevice(dev))

    return bus_devs
