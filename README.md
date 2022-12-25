<div align="center">
<p>
    <img width="150" src="https://raw.githubusercontent.com/julelang/resources/main/jule_icon.svg?sanitize=true">
</p>
<h1>The Jule Programming Language</h1>

This repository is the main source tree of Jule. \
It contains the reference compiler, API and standard library.

[Website](https://jule.dev) |
[Documentations](https://jule.dev/pages/docs.html) |
[Contributing](https://jule.dev/pages/contributing.html)

</strong>
</div>

<h2 id="motivation">Motivation</h2>

> **Warning** \
> [JuleC](#what-is-julec) is still under pre development. Therefore, design changes and the like may occur in the language. \
> Some commits may not be fully honored due to some compiler/API errors. \
> Please report it with the [Jule Issue Tracker](https://github.com/julelang/jule/issues) if you come across something like this.

Our motivation is to create a safe and fast programming language option that focused on system programming.
A safer, more modern and readable option than C.
However, we do not want to stray too far from C, C is a language that excels in systems programming.
Since Jule is transpiled to C++ code, it can have very high interoperability with C++.
Due to its interoperability with C++, it also offers a great deal of support for C.

Jule designed for maintainable and reliable software development.
Guarantees memory safety and committed not contain undefined behavior, has a reference compiler with obsessions that encourage developers to build safe software.
It offers fully integrated Jule-C++ development with API and interoperability.

<img src="./docs/images/quicksort.png"/>

<h2 id="key-features">Design Principles</h2>

Jule is develops within the framework of certain design principles.
These principles often follow the motivation for the emergence of Jule.
Our aim is to present a design and implementation that meets these principles in the most balanced way.

### Our Design Principles

- Simplicity and maintainability
- Fast and scalable development
- Performance-critical software
- Memory safety
- Immutability by default
- Efficient and performant
- High C++ interoperability

<h2 id="what-is-julec">What is JuleC?</h2>
JuleC is the name of the reference compiler for the Jule programming language.
It is the original compiler of the Jule programming language.
The features that JuleC has represent the official and must-have features of the Jule programming language.
This is sort of a standard for the Jule programming language and represents the minimum competency that unofficial compilers should have.

<h2 id="memory-safety">Memory Safety and Management</h2>
Memory safety and memory management is a major challenge in C , C++ and similar programming languages.
Jule has a reference-based memory management design to solve these issues.
Jule guarantees memory safety and uses reference counting for memory management.
An account-allocation is automatically released as soon as the reference count reaches zero.
Please read the <a href="https://jule.dev/pages/docs.html?page=memory-memory-management">memory management documentations</a> for more information about reference-counting approach of Jule.
<br><br>
Variables are immutable by default, and each variable is encouraged to be initialized at declaration.
Safe Jule performs bounds checking and nil (aka null) checking.
It is committed to no undefined behavior.
Unsafe behaviors are encouraged to be done deliberately with unsafe scopes.
Please read the <a href="https://jule.dev/pages/docs.html?page=unsafe-jule">Unsafe Jule documentations</a> for more information about of Unsafe Jule.

<h2 id="cpp-interoperability">C++ Interoperability</h2>
Jule is designed to be interoperable with C++.
A C++ header file dependency can be added to the Jule code and its functions can be linked.
It's pretty easy to write C++ code that is compatible with the Jule code compiled by the compiler.
JuleC keeps all the C++ code it uses for Jule in its <a href="https://github.com/julelang/jule/tree/main/api">api</a> directory.
This API makes it possible and easy to write C++ code that can be fully integrated into Jule.
<ol></ol> <!-- for space -->
<img src="./docs/images/cpp_interop.png"/>

<h2 id="future-changes">Future Changes</h2>
JuleC is in early development and currently it can only be built from source.
However, despite being in the early development stage, many algorithms (<a href="https://github.com/julelang/jule/tree/main/std">see the standard library</a>) can be successfully implemented.
It is planned to rewrite the compiler with Jule after reference compiler and standard library reaches sufficient maturity.
JuleC has or is very close to having many of the things Jule was intended to have, such as memory safety, properties, structures with methods and generics.
<br><br>
A release is not expected until JuleC itself is developed with the Jule programming language.
The syntax and language design of the Jule programming language has emerged and is not expected to undergo major changes.
When the reference compiler is rewritten with Jule, it is thought that AST, Lexer and some packages will be included in the standard library.
This will be a change that will cause the official compiler's project structure to be rebuilt.
The reference compiler will probably use the standard library a lot.
This will also allow developers to quickly develop tools for the language by leveraging Jule's standard library.
<br><br>
There is an idea to include a package manager in JuleC as well, although it doesn't have one yet.
Jule's modern understanding of language and convenience suggests that there should be a package manager that comes with the compiler.
This package manager will provide management of non-standard library packages developed and published by the community.
Jule's standard library only gets updates with compiler releases.
<br><br>
The language and standard library will continue to evolve and change in the future but JuleC will guarantee stability since its first stable release.
Some packages of the standard library
(<a href="https://github.com/julelang/jule/tree/main/std/math">std::math</a>,
<a href="https://github.com/julelang/jule/tree/main/std/conv">std::conv</a>,
<a href="https://github.com/julelang/jule/tree/main/std/unicode/utf8">std::unicode::utf8</a>
or etc.) are almost complete and are not expected to undergo major changes.

<h2 id="documentations">Documentations</h2>

All documentation about Jule and JuleC is on the website. <br>
[See Documentations](https://julelang.github.io/website/pages/docs.html)
<br><br>
To contribute to the website, documentations or something else, please use the <a href="https://github.com/julelang/website">website repository</a>.

<h2 id="os-support">Compiler and C++ Standard Support</h2>
JuleC officially supports some C++ compilers.
When you try to compile with these compilers, it promises that code can be compiled in the officially supported C++ standard.
JuleC is committed to creating code according to the most ideal C++ standard it has adopted.
Commits that the generated code can be compiled by C++ compilers that fully support this standard.
Likewise, this commit is also available for the <a href="./api">API</a> of JuleC.
Jule's ideal C++ standard is determined by the most ideal C++ standard, fully supported by officially supported C++ compilers.
<br><br>
If you are getting a compiler error even though you are using the officially supported compiler and standard, please let us know with the <a href="https://github.com/julelang/jule/issues">Jule Issue Tracker</a>.
If you are trying to use a standard or compiler that is not officially supported, you can still contact us to find out about the problem.
But keep in mind that since it's out of official support, it's likely that the maintainers won't make the effort to fix it.
<br><br>

[See compiling documentations](https://jule.dev/pages/docs.html?page=compiler-compiling) for supported compilers and C++ standards.

<h2 id="os-support">Platform Support</h2>
Jule supports multiple platforms.
It supports development on i386, amd64 architectures on Windows, Linux and Darwin platforms.
JuleC undertakes that the code and standard library it produces will be compatible with all these platforms.
All supported platforms by JuleC are documented in the <a href="https://jule.dev/pages/docs.html?page=compiler-platform-support">platform support documentations</a>.

<h2 id="building-project">Building Project</h2>

> [Website documentation](https://julelang.github.io/website/pages/docs.html?page=getting-started-install-from-source) for install from source.

When you enter the directory where the source code is located, you can find some compilation scripts for compiling of JuleC. \
These scripts are written to run from the [src](./src) directory:

- `build`: scripts used for compile.
- `brun`: scripts used for compile and execute if compiling is successful.

JuleC aims to have a single main build file. \
JuleC is in development with the [Go](https://github.com/golang/go) programming language.

### Building with Go Compiler

> In main directory.

#### Windows (PowerShell)
```powershell
go build -o julec.exe -v src\cmd\julec\main.go
```

#### Linux (Bash)
```bash
go build -o julec -v src/cmd/julec/main.go
```

Run the above command in your terminal, in the Jule project directory.

<h2 id="contributing">Contributing</h2>

Thanks for you want contributing to Jule! \
Every contribution, big or small, to Jule is greatly appreciated.

The Jule project use issues for only bug reports and proposals. \
To contribute, please read the [contribution guidelines](https://jule.dev/pages/contributing.html). \
To discussions and ask questions, please use [discussions](https://github.com/julelang/jule/discussions). \
Regarding security, please refer to the [security policy](SECURITY.md).

<h2 id="code-of-conduct">Code of Conduct</h2>

[See Julenour Code of Conduct](https://jule.dev/pages/code_of_conduct.html)

<h2 id="license">License</h2>

The JuleC and standard library is distributed under the terms of the BSD 3-Clause license. <br>
[See License Details](https://julelang.github.io/website/pages/license.html)
