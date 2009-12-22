#include <stdio.h>
#include <windows.h>
#include <dlfcn.h>

void* dlopen(const char* path, int mode) {
  char *buf = malloc(strlen(path) + 20);
  sprintf(buf, "%s.dll", path);
  void *lib = (void*) LoadLibrary(buf);
  free(buf);
  return lib;
}

void* dlsym(void* handle, const char* symbol) {
  FARPROC retval;
  retval = GetProcAddress((HINSTANCE) handle, symbol);
  return (void*) retval;
}

int dlclose(void* handle) {
  // dlclose returns zero on success.
  // FreeLibrary returns nonzero on success.
  BOOL retval;
  retval = FreeLibrary((HINSTANCE) handle);
  return (int) (retval != 0);
}

static char dlerror_buf[200];

const char *dlerror(void) {
  DWORD err = GetLastError();
  sprintf(dlerror_buf, "%x", (unsigned int) err);
  return dlerror_buf;
}

