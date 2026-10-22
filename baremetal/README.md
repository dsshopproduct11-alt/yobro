# NoEyeOS Bare-Metal (No Linux)

This is a separate, ultra-small, freestanding x86 OS prototype. It does **not** use Linux or a Linux distribution. It compiles a tiny C kernel and boots it using GRUB Multiboot.

## Build an ISO
1. Open GitHub Actions.
2. Run **Build NoEyeOS Bare-Metal (No Linux)**.
3. Download the `NoEyeOS-BareMetal-ISO` artifact from the completed run.

## What works in this first milestone
- Boots a freestanding kernel directly (not a Linux kernel)
- Minimal monochrome VGA text interface
- GRUB boot menu and bootable ISO output

## Not implemented yet
This is not yet a full desktop OS. There is no real web browser, GUI window manager, keyboard shell, filesystem, networking, Wi-Fi, or Bluetooth stack. Those require substantial additional kernel, driver, protocol and application work. A normal modern browser is especially large; a tiny hobby kernel cannot simply include Firefox/Chromium without first building the required OS services and graphics/networking APIs.

The installer button is intentionally not included yet: a safe permanent installer needs disk drivers, partitioning, filesystem support and a recovery path. Do not install this prototype to a real disk. Test only in QEMU/another virtual machine.

Target: legacy BIOS/GRUB-compatible x86 PC or emulator. This initial kernel is 32-bit and is not for Android/ARM devices.
