# Description

Windshield is a simple cli-based generator, which helps C/C++ programmers to generate header files.

## How it works?

## C/C++ files

For example, we have a file with two functions. First function we will call as 'sum' and second as 'multiple'. So, now, our file looks like:

```cpp
int sum(int a, int b) {
  /* Some code */
}

int multiple(int a, int b) {
  /* Some code */
}
```

Now, in order to windshield will find our functions we should add some commentaries above functions:

```cpp
// #ws test.h
int sum(int a, int b) {
  /* Some code */
}

// #ws another_test.h
int multiple(int a, int b) {
  /* Some code */
}
```

> [!warning]
> Look! Space between '//' and '#ws' is required!

Those commentaries says windshield: "Hey! That function, that declared below, needs to be in that header file". If specified header doesn't exists, windshield will create it in [include path] folder. By the way, if your header file exists, windshield will try to find it in your include path(which specified in windshield config file).

## Header files

Windshield doesn't where functions will be declared. So, you need to indicate it. For example, you have header file with content:

```h
#pragma once

#ifndef MYHEADER_H
#define MYHEADER_H

void test();

#endif // MYHEADER_H
```
If you request this file to windshield, it will throw an error. So, you need to add some commentaries:

```h
#pragma once

#ifndef MYHEADER_H
#define MYHEADER_H

void test();
// #ws declarations start
// #ws declarations end

#endif // MYHEADER_H
```
Now, your functions will be putted correctly!

## Try it yourself

You can try windshield by yourself. In order to do it, make those steps:

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
> [!warning]
> Before run next command, make sure, that you have C/C++ compilers in your computer. And install cmake in your computer

Now, compile it:

```bash
cmake -S . -B build
```

And build:

```bash
cmake --build build
```

And check, that windshield have built successfully:

```bash
./build/windshield version
```

### 1.5 Create alias for windshield
Bonus section. In this section, we will create windshield alias for bash.

Copy executable windshield file into /usr/bin

```bash
cp [path to windshield dir]/build/windshield /usr/bin
```

Now, you can use it:

```bash
windshield -v
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

# License
MIT
