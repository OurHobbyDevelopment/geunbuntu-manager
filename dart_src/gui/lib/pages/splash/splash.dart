import 'package:flutter/material.dart';
import 'package:gui/test/linux_test.dart';

class SplashScreen extends StatelessWidget {
  const SplashScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        body: Center(
          child: ElevatedButton(
            onPressed: () {
              Navigator.push(context, MaterialPageRoute(
                builder: (context) => LinuxTest())
              );
            },
            child: const Text('자')
          ),
        )
      );
  }
}