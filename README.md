# Huffman Text Compressor

A lightweight **C implementation** of Huffman encoding/decoding for text file compression. Compress your text files and decompress them back to their original form using optimal Huffman coding.

## 🚀 Features

- ✅ **Huffman Algorithm**: Implements optimal prefix-free codes for compression
- ✅ **CLI Interface**: Simple command-line interface for compression and decompression
- ✅ **Organized Output**: All output files organized in dedicated folders
- ✅ **Automatic Cleanup**: Temporary binary files cleaned up automatically
- ✅ **No External Dependencies**: Pure C with standard libraries only

## 📁 Project Structure

```
Text-Compressor/
├── src/                          # Source code
│   ├── main.c                    # Main program (compression/decompression)
│   ├── Compress_Functions.c      # Huffman algorithm implementation
│   └── Compress_Functions.h      # Function declarations
├── samples/                      # Place your input text files here
├── output/                       # Generated compressed/decompressed files
├── docs/                         # Documentation
├── README.md                     # This file
└── compile_and_run.bat           # Quick compile script
```

## 🔧 Setup & Installation

### Prerequisites
- **Windows OS** (uses Windows console API)
- **GCC compiler** (or any C compiler like MinGW, Clang)
- **Command line** (Command Prompt or PowerShell)

### Compilation

#### Option 1: Manual Compilation
```bash
cd src
gcc -o .\main.exe .\main.c
```

#### Option 2: Using Batch Script (if provided)
```bash
compile_and_run.bat
```

## 📖 Usage

### 1. Compress a File

**Command:**
```bash
.\main com <input_file>
```

**Example:**
```bash
.\main com ..\samples\mytext.txt
```

**Output Files** (in `output` folder):
- `Guide.txt` - Huffman code mapping (required for decompression)
- `Compressed.txt` - Your compressed file

**What Happens:**
1. Reads the input file
2. Builds the Huffman tree based on character frequencies
3. Generates the guide file with character-to-code mappings
4. Creates the compressed binary representation
5. Encodes it as ASCII characters
6. Cleans up temporary files

**Example Output:**
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

---

### 2. Decompress a File

**Command:**
```bash
.\main decom <compressed_file> <guide_file>
```

**Example:**
```bash
.\main decom ..\output\Compressed.txt ..\output\Guide.txt
```

**Output Files** (in `output` folder):
- `Decompressed.txt` - Your restored original file

**What Happens:**
1. Reads the guide file for Huffman codes
2. Reads the compressed file
3. Rebuilds the Huffman tree
4. Decodes the binary representation
5. Recreates the original text
6. Cleans up temporary files

**Example Output:**
```
✓ Guide file read successfully.
✓ Binary decoding completed.
✓ Decompression completed: ..\output\Decompressed.txt
✓ Cleaned up: ..\output\Binary2.txt
✓ Decompression completed successfully!
  Decompressed file: ..\output\Decompressed.txt
```

---

### 3. Get Help

**Command:**
```bash
.\main help
```

This displays the quick reference guide in the terminal.

---

## 🧪 Quick Test

1. **Create a sample file:**
   ```bash
   echo This is a test file for compression. Let's see how well Huffman encoding works! > samples\test.txt
   ```

2. **Compress it:**
   ```bash
   cd src
   .\main com ..\samples\test.txt
   ```

3. **Decompress it:**
   ```bash
   .\main decom ..\output\Compressed.txt ..\output\Guide.txt
   ```

4. **Verify the result:**
   - Compare `samples\test.txt` with `output\Decompressed.txt`
   - They should be identical!

---

## 📊 How Huffman Compression Works

### The Algorithm:
1. **Frequency Analysis**: Count how often each character appears
2. **Build Huffman Tree**: Create a binary tree where:
   - Frequent characters have shorter codes
   - Rare characters have longer codes
3. **Generate Codes**: Traverse the tree to assign binary codes
4. **Encode**: Replace characters with their codes
5. **Compress**: Pack binary digits into ASCII characters

### Example:
```
Original: "aaabbc"
Frequencies: a=3, b=2, c=1

Huffman Codes:
a → 0      (1 bit)
b → 10     (2 bits)
c → 11     (2 bits)

Original binary: aaabbc = 0 0 0 10 10 11 = 0000101011 (10 bits)
Original size: 6 characters × 8 bits = 48 bits
Compressed: 10 bits + overhead for codes = much smaller!
```

---

## 📝 File Descriptions

### `Compress_Functions.h`
Header file containing:
- Data structure definitions (Tree, Queue, Hf_code)
- Function declarations
- Enum for console colors

### `Compress_Functions.c`
Implementation of:
- Queue operations (add, delete, sort)
- Huffman tree construction
- Code generation and storage
- Binary encoding/decoding
- Memory management (free functions)

### `main.c`
The main program that:
- Parses command-line arguments
- Manages file I/O
- Orchestrates compression/decompression
- Displays user-friendly colored output
- Cleans up temporary files

---

## 📄 License & Credits

This is a educational implementation of Huffman coding. Free to use and modify.

---

## 🤝 Contributing

Have improvements? Feel free to:
1. Test the program with different file types
2. Report bugs or issues
3. Suggest optimizations
