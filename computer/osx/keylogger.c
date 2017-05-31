#include <stdio.h>
#include <sys/time.h>
#include <ApplicationServices/ApplicationServices.h>

CGEventRef keyPressCallback(CGEventTapProxy, CGEventType, CGEventRef, void*);
long long currentMillis();

int main(int argc, const char* argv[]) {
  CGEventMask eventsOfInterestMask = (CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventKeyUp));
  CFMachPortRef eventTap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, 0, eventsOfInterestMask, keyPressCallback, NULL);

  if (!eventTap) {
    fprintf(stderr, "Could not create event tap. Either run as root enable access for assitive devices in System Preferences.");
    exit(1);
  }

  CFRunLoopSourceRef runLoopSourceRef = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
  CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSourceRef, kCFRunLoopCommonModes);
  CGEventTapEnable(eventTap, true);
  CFRunLoopRun();

  return 0;
}

CGEventRef keyPressCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *userInfo) {
  CGKeyCode keyCode = (CGKeyCode) CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
  CGEventTimestamp eventTimestamp = (CGEventTimestamp) CGEventGetTimestamp(event);

  int pressType = -1;

  switch (type) {
    case kCGEventKeyDown:
      pressType = 1;
      break;
    case kCGEventKeyUp:
      pressType = 0;
      break;
  }

  fprintf(stdout, "%lld %lld %i %i\n", currentMillis(), eventTimestamp, keyCode, pressType);
  fflush(stdout);

  return event;
}

// function copied from https://stackoverflow.com/a/17083824
// Uses POSIX gettimeofday to get the current time in milliseconds
long long currentMillis() {
    struct timeval te;

    // get current time
    gettimeofday(&te, NULL);

    // caculate milliseconds
    return te.tv_sec * 1000LL + te.tv_usec / 1000;
}
