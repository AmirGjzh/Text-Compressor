# huff-compress

> A small command-line Huffman encoder/decoder for `.txt` files.

Compact C implementation that compresses and decompresses plain text files using Huffman coding. Originally written with Windows console colors; small portability tips are included so you can build on Linux/macOS as well.

---

## Features
- Huffman coding based text compression.
- CLI interface for compressing and decompressing files.
- Produces human-readable `Guide.txt` for decompression and `Compressed.txt` as the compressed output.
- Minimal dependencies — plain C, single-source distribution.

---

## Quick overview
- Compress: `./huff-compress com <input-file>`
  - Outputs:
    - `Binary.txt` (intermediate file — internal use)
    - `Guide.txt` (needed to decompress)
    - `Compressed.txt` (the compressed file)
- Decompress: `./huff-compress decom <Compressed_file> <Guide_file>`
  - Outputs:
    - `Binary2.txt` (intermediate file)
    - `Decompressed.txt` (restored original text)

Run `./huff-compress help` for the program's internal help text.

---

## Getting started

### Build (Windows)
Open a Developer Command Prompt (MSVC) or use MinGW:

**MinGW / GCC (on Windows):**
```bash
gcc src/main.c -o huff-compress
