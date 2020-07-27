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

## For Administrator
ps xawf -eo pid,user,cgroup,args

systemd-cgls

systemctl kill crond.service

By symlinking a service file to /dev/null you tell systemd to never start the service in question and completely block its execution.
$ ln -s /dev/null /etc/systemd/system/ntpd.service
$ systemctl daemon-reload

systemd-nspawn

```
# which service took how much time to initialize, and what needed to wait for it.
systemd-analyze plot > plot.svg

# Plots in all detail what is happening during the boot, how much CPU and IO is used.
bootchart
```

Systemd currently cover pretty much everything most desktop and embedded distributions should need, plus a big part of the server needs:

* Checking and mounting of all file systems
* Updating and enabling quota on all file systems
* Setting the host name
* Configuring the loopback network device
* Loading the SELinux policy and relabelling /run and /dev as necessary on boot
* Registering additional binary formats in the kernel, such as Java, Mono and WINE binaries
* Setting the system locale
* Setting up the console font and keyboard map
* Creating, removing and cleaning up of temporary and volatile files and directories
* Applying mount options from /etc/fstab to pre-mounted API VFS
* Applying sysctl kernel settings
* Collecting and replaying readahead information
* Updating utmp boot and shutdown records
* Loading and saving the random seed
* Statically loading specific kernel modules
* Setting up encrypted hard disks and partitions
* Spawning automatic gettys on serial kernel consoles
* Maintenance of Plymouth
* Machine ID maintenance
* Setting of the UTC distance for the system clock


Here's a little overview over these new common configuration files systemd supports on all distributions:

/etc/hostname: the host name for the system. One of the most basic and trivial system settings. Nonetheless previously all distributions used different files for this. Fedora used /etc/sysconfig/network, OpenSUSE /etc/HOSTNAME. We chose to standardize on the Debian configuration file /etc/hostname.
/etc/vconsole.conf: configuration of the default keyboard mapping and console font.
/etc/locale.conf: configuration of the system-wide locale.
/etc/modules-load.d/*.conf: a drop-in directory for kernel modules to statically load at boot (for the very few that still need this).
/etc/sysctl.d/*.conf: a drop-in directory for kernel sysctl parameters, extending what you can already do with /etc/sysctl.conf.
/etc/tmpfiles.d/*.conf: a drop-in directory for configuration of runtime files that need to be removed/created/cleaned up at boot and during uptime.
/etc/binfmt.d/*.conf: a drop-in directory for registration of additional binary formats for systems like Java, Mono and WINE.
/etc/os-release: a standardization of the various distribution ID files like /etc/fedora-release and similar. Really every distribution introduced their own file here; writing a simple tool that just prints out the name of the local distribution usually means including a database of release files to check. The LSB tried to standardize something like this with the lsb_release tool, but quite frankly the idea of employing a shell script in this is not the best choice the LSB folks ever made. To rectify this we just decided to generalize this, so that everybody can use the same file here.
/etc/machine-id: a machine ID file, superseding D-Bus' machine ID file. This file is guaranteed to be existing and valid on a systemd system, covering also stateless boots. By moving this out of the D-Bus logic it is hopefully interesting for a lot of additional uses as a unique and stable machine identifier.
/etc/machine-info: a new information file encoding meta data about a host, like a pretty host name and an icon name, replacing stuff like /etc/favicon.png and suchlike. This is maintained by systemd-hostnamed.


Reference: https://freedesktop.org/wiki/Software/systemd/Debugging

