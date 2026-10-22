# NoEyeOS Bare-Metal 0.4

A tiny freestanding 32-bit x86 kernel with a monochrome text-mode interface inspired by the supplied NoEyeOS mockup. It is not based on Linux.

## Build ISO
1. Open GitHub Actions and run **Build NoEyeOS Bare-Metal (No Linux)**.
2. Download the `NoEyeOS-BareMetal-ISO` artifact from the completed run.
3. Test in QEMU/VirtualBox configured for legacy BIOS before any hardware experiments.

## Implemented prototype
- GRUB boot menu
- NoEyeOS text-mode desktop menu
- Keyboard navigation using a polling PS/2 keyboard controller
- Terminal, file-manager, browser, settings, about and power-menu mockup panels
- Freestanding C kernel with no Linux kernel or Linux userspace

## Not implemented
The panels are early UI placeholders, not full applications. There is no real graphical desktop, real disk filesystem, web browser, TCP/IP networking, Wi-Fi/Bluetooth drivers, or safe permanent installer. Do not install to a real disk. This is a 32-bit x86 hobby OS prototype; it is not for Android/ARM devices.
