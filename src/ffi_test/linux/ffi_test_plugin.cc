#include "include/ffi_test/ffi_test_plugin.h"

#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>
#include <sys/utsname.h>

#include <cstring>

#include "ffi_test_plugin_private.h"

#define FFI_TEST_PLUGIN(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), ffi_test_plugin_get_type(), \
                              FfiTestPlugin))

struct _FfiTestPlugin {
  GObject parent_instance;
};

G_DEFINE_TYPE(FfiTestPlugin, ffi_test_plugin, g_object_get_type())

// Called when a method call is received from Flutter.
static void ffi_test_plugin_handle_method_call(
    FfiTestPlugin* self,
    FlMethodCall* method_call) {
  g_autoptr(FlMethodResponse) response = nullptr;

  const gchar* method = fl_method_call_get_name(method_call);

  if (strcmp(method, "getPlatformVersion") == 0) {
    response = get_platform_version();
  } else {
    response = FL_METHOD_RESPONSE(fl_method_not_implemented_response_new());
  }

  fl_method_call_respond(method_call, response, nullptr);
}

FlMethodResponse* get_platform_version() {
  struct utsname uname_data = {};
  uname(&uname_data);
  g_autofree gchar *version = g_strdup_printf("Linux %s", uname_data.version);
  g_autoptr(FlValue) result = fl_value_new_string(version);
  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}

static void ffi_test_plugin_dispose(GObject* object) {
  G_OBJECT_CLASS(ffi_test_plugin_parent_class)->dispose(object);
}

static void ffi_test_plugin_class_init(FfiTestPluginClass* klass) {
  G_OBJECT_CLASS(klass)->dispose = ffi_test_plugin_dispose;
}

static void ffi_test_plugin_init(FfiTestPlugin* self) {}

static void method_call_cb(FlMethodChannel* channel, FlMethodCall* method_call,
                           gpointer user_data) {
  FfiTestPlugin* plugin = FFI_TEST_PLUGIN(user_data);
  ffi_test_plugin_handle_method_call(plugin, method_call);
}

void ffi_test_plugin_register_with_registrar(FlPluginRegistrar* registrar) {
  FfiTestPlugin* plugin = FFI_TEST_PLUGIN(
      g_object_new(ffi_test_plugin_get_type(), nullptr));

  g_autoptr(FlStandardMethodCodec) codec = fl_standard_method_codec_new();
  g_autoptr(FlMethodChannel) channel =
      fl_method_channel_new(fl_plugin_registrar_get_messenger(registrar),
                            "ffi_test",
                            FL_METHOD_CODEC(codec));
  fl_method_channel_set_method_call_handler(channel, method_call_cb,
                                            g_object_ref(plugin),
                                            g_object_unref);

  g_object_unref(plugin);
}
