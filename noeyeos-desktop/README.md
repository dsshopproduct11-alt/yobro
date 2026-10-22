# NoEyeOS desktop edition

NoEyeOS is a Debian-based live desktop prototype inspired by the supplied black-and-white NoEyeOS reference.

## Included
- Real XFCE desktop, terminal and file manager
- Firefox ESR web browser (requires network access)
- NetworkManager Wi-Fi/Ethernet controls
- BlueZ + Blueman Bluetooth tools
- Linux firmware packages for common Wi-Fi adapters
- Desktop shortcut **Install NoEyeOS permanently** that launches Calamares

## Build
Open **Actions → Build NoEyeOS Desktop ISO → Run workflow**. When it finishes, open the workflow run and download the **NoEyeOS-desktop-live-ISO** artifact. GitHub Actions artifacts are ZIP downloads containing the ISO and checksum.

## Important limitations
- This is an amd64 (64-bit Intel/AMD PC) build, not an Android APK and not intended for ARM phones.
- Wi-Fi/Bluetooth support depends on the computer's chipset and firmware; not every adapter is guaranteed.
- The installer shortcut is included, but Calamares still needs a valid distro-specific configuration and must be tested in a VM before installing to real hardware. Back up files first. Do not assume a successful build means the ISO has been boot-tested.
- The live system uses a real Debian kernel and desktop packages; the reference image is a visual target, not a promise that every pixel or all hardware will match.
