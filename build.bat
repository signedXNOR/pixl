gcc -o pixl.exe pixl.c pixl.h neighbourPixl.c neighbourPixl.h -lraylib -lgdi32 -lwinmm -Wl,--subsystem,windows
:: for debugging, remove -Wl,--subsystem,windows