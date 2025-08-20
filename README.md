# huffman-compressor 

> A small command-line Huffman encoder/decoder for `.txt` files.

Compact C implementation that compresses and decompresses plain text files using Huffman coding. Originally written with Windows console colors.

---

## Features
- Huffman coding based text compression.
- CLI interface for compressing and decompressing files.
- Produces human-readable `Guide.txt` for decompression and `Compressed.txt` as the compressed output.
- Minimal dependencies — plain C, single-source distribution.

---

## Quick overview
- Compress: `./main.exe com <input-file>`
  - Outputs:
    - `Binary.txt` (intermediate file — internal use)
    - `Guide.txt` (needed to decompress)
    - `Compressed.txt` (the compressed file)
- Decompress: `./main.exe decom <Compressed_file> <Guide_file>`
  - Outputs:
    - `Binary2.txt` (intermediate file)
    - `Decompressed.txt` (restored original text)

Run `./main.exe help` for the program's internal help text.
