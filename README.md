# 🔍 sigscan - Scan binary files for signature

**sigscan** is a command-line tool to scan binary files for hexadecimal signatures.<br>
You can use it to:
- Detect specific instruction patterns in executables
- Locate custom data sequences in binary files  

## Features
- Support for wildcard nybbles (`x`/`X`) in signatures
- Validation of input signatures
- Reports all matching offsets in the file
- Provides a clear summary of total matches found

## Installation
Clone the repository and compile the tool using **The KMAK Build System** and a C compiler:

```bash
git clone https://github.com/komodoresoft/sigscan.git
cd sigscan
kmak make.kmak build
```

## Usage
```bash
sigscan [Options] File Signature
```

```
Signatures should contain only hexadecimal characters and optionally special characters
listed below:
  x,X - Any nybble value (wildcard)
```

### Example
```
./sigscan bios.bin FEAXXXXX
```

## License
© 2025 Komodore - blueberry077 (Marc-Daniel DALEBA).
Released under the MIT License.  
See [LICENSE](LICENSE) for details.
