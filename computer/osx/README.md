# Keylogger OS X

This is a simple keylogger used for data collection to train Seeloger. Keystrokes are captured in the following format:

```tsv
1496257064411 45221549257978 38 1
1496257064471 45221609344616 38 0
1496257064506 45221644244437 5 1
1496257064590 45221728325404 5 0
1496257065160 45222298183764 18 1
1496257065246 45222366141622 18 0
```

The first number is the epoch timestamp of when the event was logged. The second number is the timestamp of when the key was pressed according to OS X, it is measured in nanoseconds from machine startup. The third number refers to the key. The last is the state the key transitioned to where down is `1` and up is `0`.

## Usage

Run `make` to compile the `keylogger` binary. Run `sudo ./keylogger` or run `./keylogger` with Assitive devices enabled to collect data.

## Limitations

This keylogger does not yet handle keys like shift, control, option, command, or function keys.
