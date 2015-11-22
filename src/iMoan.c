#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include <mach/mach_port.h>
#include <mach/mach_interface.h>
#include <mach/mach_init.h>

#include <IOKit/pwr_mgt/IOPMLib.h>
#include <IOKit/IOMessage.h>

const char *WAVEFORM_PATH = "scream.wav";

void MyMoanCallBack(
    void *refCon,
    io_service_t service,
    natural_t messageType,
    void *messageArgument
) {
    if (messageType == kIOMessageSystemWillPowerOn) {
        execlp("afplay", "afplay", WAVEFORM_PATH, (char *)NULL);
    }
}

int main(int argc, char **argv) {
    io_connect_t root_port;
    IONotificationPortRef notifyPortRef;
    io_object_t notifierObject;
    void *refCon = NULL;

    root_port = IORegisterForSystemPower(
        refCon,
        &notifyPortRef,
        MyMoanCallBack,
        &notifierObject
    );

    if (root_port == 0) {
        printf("IORegisterForSystemPower failed\n");
        return 1;
    }

    CFRunLoopAddSource(
        CFRunLoopGetCurrent(),
        IONotificationPortGetRunLoopSource(notifyPortRef),
        kCFRunLoopCommonModes
    );

    CFRunLoopRun();

    return (0);
}
