---
title: systemd
---

## multi-Seat

### Definition of Terms
* seat: consists of all hardware devices assigned to a specific workplace. At least one graphics device, and usually also includes keyboard, mouse. It can also include video cameras, sound cards and more.
* session: It is defined by the time a user is logged in until he logs out. A session is bound to one or no seats(for 'virtual' ssh logins). Multiple sessions can be attached to the same seat, but only one of them can be active.
* user: Corresponds to the person using a computer, identified by a numeric user id(UID) or a user name(string).
* multi-session: A system allows multiple user sessions on the same seat at the same time.
* multi-seat: A system allows multiple independent seats that can be individually and simultaneously used by different user.

#### Note:
* hardware like printers, hard disks or network cards is generally not assigned to a specific seat. They are available to all seats equally. (Well, with one exception: USB sticks can be assigned to a seat)
* "seat0" always exists.

### udev Rules
Assignment of hardware devices to seats is managed inside the udev database, via settings on the devices:
* Tag "seat": if set this device is eligible to be assigned to a seat.
* Tag "master-of-seat"
* Property "ID_SEAT"
* Property "ID_AUTOSEAT"
* Property "ID_FOR_SEAT"

### Examples

```
loginctl list-seats
loginctl seat-status seat0
loginctl attach // assign hardware to a specific seat
```

##  Configuration

/etc/systemd/system.conf



## Debugging



Reference: https://freedesktop.org/wiki/Software/systemd/Debugging

