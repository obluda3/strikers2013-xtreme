#if DEBUG
#ifndef SHD_DEB
#define SHD_DEB

void app_err_prt(char* format, ...);
int bprintf(char *format, ...);
int eprintf(char* format, ...);
void sys_err_prt(char* format, ...);
int cprintf(char *format, ...);

#endif
#endif