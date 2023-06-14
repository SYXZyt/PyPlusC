# PyPlus
Python is a great and powerful programming language, but there are a few slight annoyances which cause me to dislike the language.
Introducing PyPlus, a Python wrapper language which removes all of these annoyances.
***
## Why use PyPlus?
PyPlus is a custom syntax which compiles directly into Python. This means it can work with any existing Python library, and can even call `.py` files. If you can code it in Python, you can code it in PyPlus.

This project was created because I dislike using Python's whitespace based scoping and wanted to replace it with curly braces instead, while retaining everything that makes Python great.

## Usage
Call the compiler using the command `PythonPlus [.PYP file/s]` which will generate all of your .py files in the output folder. Then the code can be executed using the normal Python command line instruction.
For example
```
PythonPlus helloworld.pyp
Python output/helloworld.py
"Hello, World!"
```

## Can Python call PyPlus code?
No. Python cannot call PyPlus code as PyPlus is not valid syntax for the Python compiler. First, you would have to compile the PyPlus code first, before compiling it with Python.
PyPlus can call Python as the PyPlus compiler does not evaluate imports. Just be aware that the PyPlus compiler cannot compile Python, and will generate incorrect code if ran. PyPlus cannot import another PyPlus library for the same reason, unless that library is passed to the compiler along with the main PyPlus file.

## Can I compile PyPlus to an executable
This is planned. It will require that both Python and PyInstaller are installed on your system.

## How I can make a curly bracket appear in the compiled Python?
Since the PyPlus compiler will convert all curly brackets into indents, you can a blackslash to act as a pass through.
```
#Python
myMap = {}
myMap2 = {
    "a" : "b"
}
```
```
#PyPlus
myMap = \{\}
myMap2 = \{
    "a" : "b"
\}
```
The readability isn't great but it is the best way PyPlus can handle it without vastly changing syntax.

## PyPlus vs Python
Currently the main differences is that PyPlus uses curly braces for classes and functions, in the same way `C/C++` or `Java` do for example.
The list of new features is always expanding. Check out the [proposals](https://github.com/SYXZyt/PyPlusC/tree/main/Proposals) for a list of changes which have been proposed.

## Syntax Highlighting
Currently a Visual Studio Code extension has been created which implements syntax highlighting. It is in development and not on the extension browser within VS-Code. It can be installed manually using the following commands. (Note that npm is required)
```
Required if vsce is not installed already
npm install @vscode/vsce

cd extensions/visual-studio-code/
vsce package
```

Now open Visual Studio Code and click the `...` on the extension page and click `Install from VSIX...`.
![Install from VSIX...](https://github.com/SYXZyt/PyPlusC/blob/main/docs/images/extensions/vs-code/install_vsix.png?raw=true "Image showing the Install from VSIX option")
Select the `vsix` file created and now any `.pyp` file will use PyPlus syntax highlighting.

## Building
Two options are provided for compilation. If you are on Windows then it is recommended that you use Visual Studio to edit the application. A `.sln` file is provided for use with Visual Studio.
If you are using Linux then a cmake file is provided. The following commands should compile the compiler.
```
cd build
cmake ..
make
```

## Contributing
When it comes to contributing to the project, all changes must be made to the `DEV-MAIN` branch. The `main` branch is reserved to act as the latest stable version. When making a proposal, please use the issues forum to make the proposal. If the proposal is well liked, it will be added to the `proposals` branch.

## Known Issues
Multiline strings are likely to give you an error, as the PyPlus compiler sees them as a group of strings next to each other. This is on the list of things to fix.
Attempting to compile a Python file will result in a mangled `.py` which contains incorrect indentation.
Cannot use maps as the brackets will compile into indents. (This is semi-fixed. Keywords can be used to bypass this issue)
