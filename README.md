# 🗜️ Huffman Text Compressor

A small C program for compressing and decompressing text files with Huffman coding. Comes with a simple CLI, no external dependencies.

---

## ✨ Features

- Text compression and decompression using Huffman coding
- Simple command-line interface
- `samples/` for inputs and `output/` for results, kept separate
- Temporary files (`Binary.txt`, `Binary2.txt`) get cleaned up automatically after each run
- Pure C — nothing to install besides a compiler

## 📁 Project Structure

```
Text-Compressor/
├── src/                      # Source code and build scripts
│   ├── main.c
│   ├── compress_functions.c
│   └── Compress_Functions.h
├── samples/                  # Drop your input .txt files here
├── output/                   # Compressed/decompressed files end up here
├── docs/                     # Extra docs and guides
├── compile.bat               # Windows build helper
└── README.md
```

## 🚀 Getting Started

**Prerequisites**
- Windows (the paths below use Windows-style separators)
- A C compiler — `gcc` (MinGW) works fine

**Build it**

```bash
cd src
gcc -o main.exe main.c
```

Or just run `compile.bat` from the repo root — it builds the project and prints a quick usage guide.

## ▶️ Usage

Everything gets written to `output/` by default. Drop your input files in `samples/` first.

**Compress a file**

```bash
main com <input_file>
```

Example (run from `src`):

```bash
main com ..\samples\sample.txt
```

You'll see something like:

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

**Decompress a file**

```bash
main decom <compressed_file> <guide_file>
```

Example:

```bash
main decom ..\output\Compressed.txt ..\output\Guide.txt
```

You'll see:

```
[OK] Guide file read successfully.
[OK] Binary decoding completed.
[OK] Decompression completed: ..\output\Decompressed.txt
Cleaned up: ..\output\Binary2.txt
[OK] Decompression completed successfully!
    Decompressed file: ..\output\Decompressed.txt
```

**Need a reminder?**

```bash
main help
```

## ✅ Quick Test

```bash
echo This is a test file for compression. > samples\test.txt

gcc -o main.exe main.c
main com ..\samples\test.txt
main decom ..\output\Compressed.txt ..\output\Guide.txt
```

Then check the result matches (PowerShell):

```powershell
$orig = Get-Content ..\samples\test.txt -Raw
$dec = Get-Content ..\output\Decompressed.txt -Raw
if ($orig -eq $dec) { Write-Host "SUCCESS: Files are identical" } else { Write-Host "ERROR: Files differ" }
```

## 📝 A Few Notes

- The program creates temporary binary files (`Binary.txt` / `Binary2.txt`) while it works, and removes them once it's done.
- `Guide.txt` holds the Huffman code mapping — you need it to decompress later, so keep it next to `Compressed.txt`.
- This is built for plain text. Feeding it binary files won't get you much (if any) compression.

## 🛠️ Troubleshooting

- **`File '...' couldn't be opened!`** — double check the path and that the file actually exists.
- **Decompression fails** — make sure you're pointing to the `Guide.txt` that was generated alongside that specific `Compressed.txt`.
- **Build fails** — make sure `gcc` is installed and available on your PATH.

## 🤝 Contributing

Found a bug or have an idea? Open an issue or send a pull request — contributions are always welcome.

## 📜 License

This project is licensed under the MIT License.
