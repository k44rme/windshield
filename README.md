# Description

Windshield is a simple cli-based generator, which helps C/C++ programmers to generate header files. First of all, you need to initialize windshield, using 'windshield init' command.

## Try it yourself

You can try windshield by yourself. In order to do it make those steps:

### 1. Download windshield

For now, Exists only one method to download windshield - compile it from source.

First of all, clone repository:

```bash
git clone https://github.com/k44rme/windshield
```

Then, go the project path:

```bash
cd windshield
```

Now, compile it:

```bash
cmake -S . -B build
```

Now, you can use it by typing:

```bash
./build/windhsield [COMMAND]
```

### 2. Initialize windshield

Type this, to initialize windshield:

```bash
windshield init
```

### 3. Launch test

Now, we can launch a test. Type this command in your terminal:

```bash
windshield gen test/test.cpp
```

Windshield will read test.cpp file, bring function declarations from it and write into the header file.
