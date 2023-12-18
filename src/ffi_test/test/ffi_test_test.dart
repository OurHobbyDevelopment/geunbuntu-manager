import 'package:flutter_test/flutter_test.dart';
import 'package:ffi_test/ffi_test.dart';
import 'package:ffi_test/ffi_test_platform_interface.dart';
import 'package:ffi_test/ffi_test_method_channel.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockFfiTestPlatform
    with MockPlatformInterfaceMixin
    implements FfiTestPlatform {

  @override
  Future<String?> getPlatformVersion() => Future.value('42');
}

void main() {
  final FfiTestPlatform initialPlatform = FfiTestPlatform.instance;

  test('$MethodChannelFfiTest is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelFfiTest>());
  });

  test('getPlatformVersion', () async {
    FfiTest ffiTestPlugin = FfiTest();
    MockFfiTestPlatform fakePlatform = MockFfiTestPlatform();
    FfiTestPlatform.instance = fakePlatform;

    expect(await ffiTestPlugin.getPlatformVersion(), '42');
  });
}
