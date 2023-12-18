import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'ffi_test_platform_interface.dart';

/// An implementation of [FfiTestPlatform] that uses method channels.
class MethodChannelFfiTest extends FfiTestPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('ffi_test');

  @override
  Future<String?> getPlatformVersion() async {
    final version = await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }
}
