/* NoEyeOS 0.4 Bare-Metal desktop prototype.
 * Freestanding 32-bit x86 C kernel. No Linux, libc, or userspace.
 * VGA text UI and polling PS/2 keyboard. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#define VGA ((volatile u16*)0xB8000)
#define COLS 80
#define ROWS 25
#define NORMAL 0x0F
#define DIM 0x07
#define SELECTED 0x70
#define BLACK 0x00
static u8 inb(u16 p){u8 v;__asm__ volatile("inb %1, %0":"=a"(v):"Nd"(p));return v;}
static void put(char c,u8 a,u32 x,u32 y){if(x<COLS&&y<ROWS)VGA[y*COLS+x]=((u16)a<<8)|(u8)c;}
static void text(const char*s,u8 a,u32 x,u32 y){while(*s&&x<COLS)put(*s++,a,x++,y);}
static void fill(u8 a){for(u32 y=0;y<ROWS;y++)for(u32 x=0;x<COLS;x++)put(' ',a,x,y);}
static void hline(u32 y){for(u32 x=0;x<COLS;x++)put('-',DIM,x,y);}
static void frame(u32 x,u32 y,u32 w,u32 h,const char*t){
 put('+',NORMAL,x,y);put('+',NORMAL,x+w-1,y);put('+',NORMAL,x,y+h-1);put('+',NORMAL,x+w-1,y+h-1);
 for(u32 i=1;i<w-1;i++){put('-',DIM,x+i,y);put('-',DIM,x+i,y+h-1);}
 for(u32 i=1;i<h-1;i++){put('|',DIM,x,y+i);put('|',DIM,x+w-1,y+i);}text(t,NORMAL,x+2,y);
}
static void logo(u32 x,u32 y){
 text("   .-------.   ",NORMAL,x,y);text("  /  .---.  \\  ",NORMAL,x,y+1);
 text(" /  /     \\  \\ ",NORMAL,x,y+2);text("|  (  (o)  )  |",NORMAL,x,y+3);
 text(" \\  \\  /  /  / ",NORMAL,x,y+4);text("  '---X---'   ",NORMAL,x,y+5);text("   NO EYE OS  ",NORMAL,x,y+6);
}
static u8 key(void){
 while(!(inb(0x64)&1))__asm__ volatile("pause");
 u8 s=inb(0x60);if(s&0x80)return 0;
 switch(s){case 0x01:return 27;case 0x1C:return 13;case 0x48:return 0x80;case 0x50:return 0x81;default:return 0;}
}
static void boot_screen(void){
 fill(BLACK);text("GNU GRUB  version 2.12",NORMAL,28,1);frame(2,4,76,8,"NoEyeOS 0.4 (Custom Kernel)");
 text("NoEyeOS 0.4 (Bare-Metal)",SELECTED,4,6);text("Advanced options for NoEyeOS 0.4",NORMAL,4,7);
 text("Memory test (memtest86+)",NORMAL,4,8);text("Use UP/DOWN to select. ENTER to boot.",DIM,5,15);
 text("Independent kernel - no Linux base",DIM,5,16);for(;;)if(key()==13)return;
}
static int selected=0;
static const char*items[]={"Terminal","File Manager","Browser","Settings","About","Power"};
static void desktop(void){
 fill(BLACK);text("NO EYE OS",NORMAL,2,1);text("Small System. Big Freedom.",DIM,2,2);hline(4);
 for(int i=0;i<6;i++){if(i==selected){text(">",NORMAL,2,6+i*2);text(items[i],SELECTED,4,6+i*2);}else text(items[i],NORMAL,4,6+i*2);}
 logo(34,7);text("Use UP/DOWN and ENTER",DIM,28,19);hline(22);text("[eye] NoEyeOS",DIM,1,23);text("Bare-Metal 0.4",DIM,60,23);
}
static void panel(const char*n){
 fill(BLACK);frame(2,1,76,22,n);text("X",NORMAL,75,1);
 if(n[0]=='T'){text("noeyeos> help",NORMAL,4,4);text("Available commands:",DIM,4,6);text("help  - Show this help",NORMAL,6,7);text("clear - Clear screen",NORMAL,6,8);text("about - System information",NORMAL,6,9);text("desktop - Return to desktop",NORMAL,6,10);text("Commands are currently demonstration text.",DIM,4,14);}
 else if(n[0]=='F'){text("Home",SELECTED,5,4);text("Documents",NORMAL,7,6);text("Downloads",NORMAL,7,8);text("Music",NORMAL,7,10);text("Pictures",NORMAL,7,12);text("Videos",NORMAL,7,14);text("No real disk filesystem yet.",DIM,4,18);}
 else if(n[0]=='B'){text("URL: https://example.com",SELECTED,4,4);text("Browser is not implemented in this bare-metal kernel.",NORMAL,4,8);text("A real browser needs graphics, networking, TLS, fonts,",DIM,4,10);text("memory management and a large application runtime.",DIM,4,11);}
 else if(n[0]=='S'){text("Network       Not implemented",NORMAL,5,5);text("Wi-Fi         No driver",NORMAL,5,7);text("Bluetooth     No driver",NORMAL,5,9);text("Display       VGA text mode",NORMAL,5,11);text("Keyboard      PS/2 polling",NORMAL,5,13);}
 else if(n[0]=='A'){text("NoEyeOS 0.4 - Custom Kernel",NORMAL,5,4);text("Architecture: Intel/AMD x86 32-bit",DIM,5,6);text("Kernel: freestanding C",DIM,5,7);text("Base: none (not Linux)",DIM,5,8);text("Available: GRUB boot, VGA text UI, PS/2 keyboard",DIM,5,10);text("Not implemented: GUI, filesystem, browser, networking,",DIM,5,12);text("Wi-Fi, Bluetooth, permanent installer.",DIM,5,13);}
 else{text("Power Menu",NORMAL,5,4);text("Return to desktop",SELECTED,7,7);text("Safe reboot is not implemented yet.",DIM,5,10);}
 text("ESC: return to desktop",DIM,4,20);
}
void kernel_main(void){
 boot_screen();
 for(;;){desktop();u8 k=key();if(k==0x80)selected=(selected+5)%6;else if(k==0x81)selected=(selected+1)%6;else if(k==13){panel(items[selected]);for(;;){u8 p=key();if(p==27||p==13)break;}}}
}
