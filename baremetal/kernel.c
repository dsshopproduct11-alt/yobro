/* NoEyeOS Bare-Metal: tiny freestanding 32-bit x86 kernel.
 * No Linux, no libc, no userspace yet. Boots via GRUB Multiboot v1. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define VGA ((volatile u16*)0xB8000)
#define COLS 80
#define ROWS 25
#define WHITE_ON_BLACK 0x0F
#define DIM_WHITE 0x07
#define INK 0x0F

static u32 cursor_x = 0, cursor_y = 0;

static void put_at(char c, u8 attr, u32 x, u32 y) {
    if (x < COLS && y < ROWS) VGA[y * COLS + x] = ((u16)attr << 8) | (u8)c;
}
static void clear_screen(void) {
    for (u32 y=0; y<ROWS; ++y)
        for (u32 x=0; x<COLS; ++x) put_at(' ', WHITE_ON_BLACK, x, y);
    cursor_x=0; cursor_y=0;
}
static void write_at(const char *s, u8 attr, u32 x, u32 y) {
    while (*s && x < COLS) put_at(*s++, attr, x++, y);
}
static void line(u32 y) {
    for (u32 x=0; x<COLS; ++x) put_at('-', DIM_WHITE, x, y);
}
static void halt(void) {
    for (;;) __asm__ volatile ("hlt");
}

/* Multiboot v1 header must be in the first 8 KiB of the image. */
__attribute__((section(".multiboot"), used))
static const u32 multiboot_header[] = { 0x1BADB002, 0x00000003, (u32)-(0x1BADB002 + 0x00000003) };

void kernel_main(void) {
    clear_screen();
    write_at("GNU GRUB -> NoEyeOS Bare-Metal", INK, 2, 1);
    line(2);
    write_at("NO EYE OS", WHITE_ON_BLACK, 4, 4);
    write_at("Small system. Big freedom.", DIM_WHITE, 4, 5);
    line(7);
    write_at("A tiny operating-system kernel, running directly on x86 hardware.", INK, 2, 9);
    write_at("Kernel: freestanding C | Architecture: 32-bit x86 | Base: none", DIM_WHITE, 2, 11);
    write_at("Linux: NOT USED", INK, 2, 13);
    line(15);
    write_at("CURRENTLY AVAILABLE", INK, 2, 17);
    write_at("[OK] Booted by GRUB Multiboot", DIM_WHITE, 4, 18);
    write_at("[OK] VGA text display", DIM_WHITE, 4, 19);
    write_at("[--] Keyboard shell (next milestone)", DIM_WHITE, 4, 20);
    write_at("[--] GUI / browser / Wi-Fi / Bluetooth (not implemented)", DIM_WHITE, 4, 21);
    line(23);
    write_at("NoEyeOS Bare-Metal prototype  |  Press Ctrl+Alt+Del to reboot in emulator", DIM_WHITE, 1, 24);
    halt();
}
