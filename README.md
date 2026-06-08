# Huffman Text Compressor 

A lightweight C implementation of Huffman encoding/decoding for text file compression. This repository includes a small CLI program to compress and decompress plain text files using Huffman coding.

---

## ✨ Features 

- Huffman coding based text compression
- Simple CLI interface for compressing and decompressing files
- Organized `samples/` (inputs) and `output/` (results) folders
- Automatic cleanup of temporary intermediate files (`Binary.txt`, `Binary2.txt`)
- Pure C implementation with no external dependencies

---

## 📁 Project Structure 

```
Text-Compressor/
├── src/                      # Source code and build scripts
│   ├── main.c
│   ├── compress_functions.c
│   └── Compress_Functions.h
├── samples/                  # Place input .txt files here
├── output/                   # Generated compressed/decompressed files
├── docs/                     # Documentation and guides
├── compile.bat               # Windows build helper
└── README.md                 # This file
```

---

## ⚙️ Setup & Compilation 

### Prerequisites

- Windows (instructions use Windows paths)
- A C compiler such as `gcc` (MinGW) or compatible toolchain

### Compile manually

Open a terminal, then:

```powershell
cd src
gcc -o main.exe main.c
```

Or run `compile.bat` from the repository root (Windows) to build and see quick usage hints.

---

## ▶️ Usage 

All outputs are written to the `output/` folder by default. Put your input files in `samples/` for convenience.

### 🗜️ Compress a file 

```
main com <input_file>
```

Example (from `src` folder):

```powershell
main com ..\samples\sample.txt
```

Typical output messages:

```
[OK] Input file read successfully.
[OK] Guide file created: ..\output\Guide.txt
[OK] Binary encoding completed.
[OK] Compression completed: ..\output\Compressed.txt
Cleaned up: ..\output\Binary.txt
[OK] Compression completed successfully!
    Guide file: ..\output\Guide.txt
    Compressed file: ..\output\Compressed.txt
```

### 📂 Decompress a file 

```
main decom <compressed_file> <guide_file>
```

Example:

```powershell
main decom ..\output\Compressed.txt ..\output\Guide.txt
```

Typical output messages:

```
[OK] Guide file read successfully.
[OK] Binary decoding completed.
[OK] Decompression completed: ..\output\Decompressed.txt
Cleaned up: ..\output\Binary2.txt
[OK] Decompression completed successfully!
    Decompressed file: ..\output\Decompressed.txt
```

### ❓ Help 

```
main help
```

---

## ✅ Quick Test 

1. Create or use an existing sample in `samples/`:

```powershell
echo This is a test file for compression. > samples\test.txt
```

2. From `src` compile and run:

```powershell
gcc -o main.exe main.c
main com ..\samples\test.txt
main decom ..\output\Compressed.txt ..\output\Guide.txt
```

3. Verify the result (PowerShell):

```powershell
$orig = Get-Content ..\samples\test.txt -Raw
$dec = Get-Content ..\output\Decompressed.txt -Raw
if ($orig -eq $dec) { Write-Host "SUCCESS: Files are identical" } else { Write-Host "ERROR: Files differ" }
```

---

## 📝 Implementation notes 

- The program creates temporary binary representations (`Binary.txt` / `Binary2.txt`) during processing. These files are removed automatically after each run.
- The `Guide.txt` file contains the Huffman code mapping (required for decompression). Keep it alongside `Compressed.txt` if you want to decompress later.
- This implementation is optimized for plain text files. Binary input may not produce meaningful compression gains.

---

## 🛠️ Troubleshooting 

- `Error: File '...' couldn't be opened!` — check the path and ensure the file exists.
- Decompression failed — make sure you supply the correct `Guide.txt` generated at compression time.
- If build fails, ensure `gcc` is installed and on your PATH.

---

## 📜 License 

This project is licensed under the MIT License.
