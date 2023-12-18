
import 'ffi_test_platform_interface.dart';

class FfiTest {
  Future<String?> getPlatformVersion() {
    return FfiTestPlatform.instance.getPlatformVersion();
  }
}
