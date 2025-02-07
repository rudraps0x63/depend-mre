#if defined(_WIN32)
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#endif
#include <assert.h>
#include <bare.h>
#include <iostream>
#include <js.h>
#include <string>
#include <vector>

#if defined(_WIN32)
  #define DLLEXPORT __declspec(dllexport)
  #define DLLIMPORT __declspec(dllimport)
#else
  #define DLLEXPORT 
  #define DLLIMPORT 
#endif

DLLEXPORT int addon_a_fn(void) {
  return 42;
}

void ErrorExit() {
#if defined(_WIN32)
  LPVOID lpMsgBuf;
  DWORD dw = GetLastError();
  int flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;

  if (FormatMessage(flags, NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL) == 0)
    std::cout << "Couldn't parse msg...\n";

  std::wcout << "Parsed error message from LoadLibraryW(): " << (LPCTSTR)lpMsgBuf << "\n";

  LocalFree(lpMsgBuf);
#else
  std::cout << "An error occured while trying to load a library\n";
#endif
}

std::vector<js_value_t*> getArguments(js_env_t *env, js_callback_info_t *info) {
  size_t argc;

  js_get_callback_info(env, info, &argc, NULL, NULL, NULL);
  std::vector<js_value_t*> args{ argc };
  js_get_callback_info(env, info, &argc, args.data(), NULL, NULL);

  return args;
}

static js_value_t *
open_library(js_env_t *env, js_callback_info_t *info) {
  size_t length;
  auto value = getArguments(env, info)[0];

  js_get_value_string_utf8(env, value, nullptr, 0, &length);

  std::string str(length, '\0');
  js_get_value_string_utf8(env, value, (utf8_t*)str.data(), length, nullptr);
  std::wstring wname { str.begin(), str.end() };

  auto handle =
  #if defined(_WIN32)
    LoadLibraryW(wname.c_str());
  #else
    dlopen(str.c_str());
  #endif

  if (!handle)
    ErrorExit();
  else
    std::cout << "Able to open the requested library.\n";

  return NULL;
}

static js_value_t *
addon_a_exports(js_env_t *env, js_value_t *exports) {
  int err = 0;

#define V(name, fn) \
  { \
    js_value_t *val; \
    err = js_create_function(env, name, -1, fn, NULL, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }

  V("openLibrary", open_library)
#undef V

  return exports;
}

BARE_MODULE(addon_a, addon_a_exports)
