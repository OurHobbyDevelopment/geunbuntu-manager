import 'package:flutter/material.dart';

import 'package:linux_terminal/linux_terminal.dart' as terminal;

class LinuxTest extends StatefulWidget {
  const LinuxTest({super.key});

  @override
  State<LinuxTest> createState() => _LinuxTestState();
}

class _LinuxTestState extends State<LinuxTest> {
  late int sumResult;

  @override
  void initState() {
    super.initState();
    sumResult = terminal.sum(2, 5);
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('되면 개꿀잼 ㅋㅋ'),
      ),
      body: Center(child: Text('2+5=$sumResult')),
    );
  }
}
