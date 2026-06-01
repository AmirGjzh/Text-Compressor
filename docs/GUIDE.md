# Huffman Text Compressor - Getting Started Guide

## What is Huffman Compression?

Huffman compression is a **lossless data compression algorithm** that reduces file size while preserving all original information. It's one of the most fundamental compression techniques used in modern computing.

### Key Concepts

1. **Frequency Analysis**: Count how often each character appears in the file
2. **Binary Tree**: Create a tree where frequent characters are closer to the root
3. **Variable-Length Codes**:
   - Common characters get short codes (e.g., "a" = 0)
   - Rare characters get long codes (e.g., "z" = 11010)
4. **Compression**: Replace each character with its code
5. **Decompression**: Rebuild the tree and decode the message

---

## Installation & Setup

### Step 1: Install a C Compiler

**Windows:**
- Download MinGW-w64 from https://www.mingw-w64.org/
- Or use Cygwin, MSVC, or Clang
- Add GCC to your PATH

**Verify installation:**
```bash
gcc --version
```

### Step 2: Navigate to Project

```bash
cd Text-Compressor-main
```

### Step 3: Compile

**Option A: Using the batch script**
```bash
compile.bat
```

**Option B: Manual compilation**
```bash
cd src
gcc -o .\main.exe .\main.c
cd ..
```

---

## Your First Compression

### Step 1: Prepare Input File

Place your text file in the `samples` folder, or create a new one:

```bash
echo "The quick brown fox jumps over the lazy dog." > samples\test.txt
```

### Step 2: Compress

```bash
cd src
.\main com ..\samples\test.txt
```

**Expected output:**
```
✓ Input file read successfully.
✓ Guide file created: ..\output\Guide.txt
✓ Binary encoding completed.
✓ Compression completed: ..\output\Compressed.txt
✓ Cleaned up: ..\output\Binary.txt
✓ Compression completed successfully!
  Guide file: ..\output\Guide.txt
  Compressed file: ..\output\Compressed.txt
```

**Output files created:**
- `output/Guide.txt` - The Huffman code mapping
- `output/Compressed.txt` - The compressed data

### Step 3: Decompress

```bash
.\main decom ..\output\Compressed.txt ..\output\Guide.txt
```

**Expected output:**
```
✓ Guide file read successfully.
✓ Binary decoding completed.
✓ Decompression completed: ..\output\Decompressed.txt
✓ Cleaned up: ..\output\Binary2.txt
✓ Decompression completed successfully!
  Decompressed file: ..\output\Decompressed.txt
```

### Step 4: Verify

Check if `output/Decompressed.txt` matches `samples/test.txt`:

```bash
fc samples\test.txt output\Decompressed.txt
```

If you get "FC: no differences encountered", it worked perfectly! ✓

---

## Understanding the Output Files

### During Compression

1. **Guide.txt**
   - Maps each character to its Huffman code
   - Format: `binary_code character_ascii_value`
   - Example:
     ```
     0 97
     10 98
     11 32
     ```

2. **Compressed.txt**
   - The actual compressed file
   - Binary data encoded as ASCII characters
   - Much smaller than original (usually 40-60% for text)

3. **Binary.txt** (automatically deleted)
   - Intermediate file: character-to-code conversion
   - Contains only 0s and 1s

### During Decompression

1. **Decompressed.txt**
   - Your reconstructed original file
   - Should be identical to the input file

2. **Binary2.txt** (automatically deleted)
   - Intermediate file: ASCII-to-binary conversion

---

## Command Reference

### Compression
```bash
.\main com <input_file>
```
- `<input_file>`: Path to your text file
- Creates `Guide.txt` and `Compressed.txt` in `output` folder

### Decompression
```bash
.\main decom <compressed_file> <guide_file>
```
- `<compressed_file>`: The Compressed.txt file
- `<guide_file>`: The Guide.txt file
- Creates `Decompressed.txt` in `output` folder

### Help
```bash
.\main help
```
- Displays quick reference

---

## Project Structure Explained

```
Text-Compressor/
├── src/
│   ├── main.c                    # Main program logic
│   ├── Compress_Functions.c      # Algorithm implementation
│   ├── Compress_Functions.h      # Function declarations
│   └── main.exe                  # Compiled executable (after gcc)
│
├── samples/                      # Your input text files go here
│   └── sample.txt               # Example file provided
│
├── output/                       # Generated files appear here
│   ├── Guide.txt                # Huffman mapping
│   ├── Compressed.txt           # Compressed data
│   └── Decompressed.txt         # Decompressed output
│
├── docs/                         # Documentation
│   └── GUIDE.md                 # This file
│
├── README.md                     # Main documentation
└── compile.bat                   # Compilation script
```

---

## Algorithm Deep Dive

### How it Works (Step by Step)

1. **Count Frequencies**
   ```
   Text: "aabbcc"
   Frequencies: a=2, b=2, c=2
   ```

2. **Build Tree** (bottom-up, combining smallest frequencies)
   ```
   Step 1: Pair (a,2) + (b,2) = [ab]:4, [c]:2
   Step 2: [ab]:4 + [c]:2 = [abc]:6

   Tree:        [6]
              /      \
            [4]      c:2
           /    \
         a:2   b:2
   ```

3. **Generate Codes** (left=0, right=1)
   ```
   a: 00
   b: 01
   c: 1
   ```

4. **Compress**
   ```
   Original: a a b b c c = 2×3 + 2×3 + 1×3 = 18 bits
   Compressed: 00 00 01 01 1 1 = 12 bits (packed into chars)
   Saving: 6 bits (33% compression)
   ```

### Why Huffman?

✓ **Optimal**: No better prefix-free code exists
✓ **Simple**: Easy to understand and implement
✓ **Fast**: O(n log n) time complexity
✓ **Reversible**: Lossless - perfect reconstruction

---

## Performance Notes

- **Compression Time**: Depends on file size, typically <1 second
- **Decompression Time**: Usually faster than compression
- **Memory Usage**: Proportional to unique character count
- **Compression Ratio**: 30-70% for typical text

---

## Reference

**Huffman Coding:**
- Invented by David Huffman (1952)
- Foundation for ZIP, GZIP, JPEG, MP3
- Optimal prefix-free code

**Related Algorithms:**
- Arithmetic Coding
- LZ77/LZ78 (DEFLATE)
- PPM (Prediction by Partial Matching)

---

## Questions?

Check the main README.md for more details or review the source code comments!

Happy Compressing! 🎉
