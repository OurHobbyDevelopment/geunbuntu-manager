import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'ffi_test_method_channel.dart';

abstract class FfiTestPlatform extends PlatformInterface {
  /// Constructs a FfiTestPlatform.
  FfiTestPlatform() : super(token: _token);

  static final Object _token = Object();

  static FfiTestPlatform _instance = MethodChannelFfiTest();

  /// The default instance of [FfiTestPlatform] to use.
  ///
  /// Defaults to [MethodChannelFfiTest].
  static FfiTestPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [FfiTestPlatform] when
  /// they register themselves.
  static set instance(FfiTestPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }
}
