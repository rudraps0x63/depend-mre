#include <assert.h>
#include <bare.h>
#include <js.h>

#if defined(_WIN32)
  #define DLLEXPORT __declspec(dllexport)
  #define DLLIMPORT __declspec(dllimport)
#else
  #define DLLEXPORT 
  #define DLLIMPORT 
#endif

DLLIMPORT int addon_a_fn(void);

extern "C" {

DLLEXPORT int callable(void) {
  return addon_a_fn();
}

}

static js_value_t *
addon_b_exports(js_env_t *env, js_value_t *exports) {
  return exports;
}

BARE_MODULE(addon_b, addon_b_exports)
