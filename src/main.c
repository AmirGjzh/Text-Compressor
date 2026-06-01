#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Compress_Functions.h"
#include "Compress_Functions.c"

#define OUTPUT_DIR "..\\output\\"
#define SAMPLES_DIR "..\\samples\\"

// Helper function to create full file path
void get_output_path(char *dest, const char *filename) {
    strcpy(dest, OUTPUT_DIR);
    strcat(dest, filename);
}

// Helper function to delete a file
void delete_file(const char *filename) {
    if (remove(filename) == 0) {
        printf("Cleaned up: %s\n", filename);
    }
}

int main(int argc, char *argv[]) {

    // Check if sufficient arguments provided
    if (argc < 2) {
        printf("Error: Please provide arguments. Use 'help' for usage instructions.\n");
        return 1;
    }

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//                            |-- COMPRESSION --|
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

    if (strcmp(argv[1], "com") == 0) {

        if (argc < 3) {
            printf("Error: Please provide input file. Usage: main com <input_file>\n");
            return 1;
        }

//------------------------ Opening file and creating the queue ------------------------

        Queue *head = NULL;

        FILE *input_file = fopen(argv[2], "r");
        if (input_file == NULL) {
            printf("Error: File '%s' couldn't be opened!\n", argv[2]);
            return 1;
        }

        int word;
        while (!feof(input_file)) {
            word = fgetc(input_file);
            if (word != -1) {
                head = add_to_queue(head, word);
            }
        }
        fclose(input_file);

        printf("[OK] Input file read successfully.\n");

//------------------------------- Building huffman tree -------------------------------

        sort_queue(head);
        head = build_huffman_tree(head);
        Tree *root = head->main;

//-------------------------------- Creating guide file ---------------------------------

        char guide_path[200];
        get_output_path(guide_path, "Guide.txt");

        FILE *guide_file = fopen(guide_path, "w");
        if (guide_file == NULL) {
            printf("Error: Guide file couldn't be created at %s!\n", guide_path);
            return 1;
        }

        char a[100];
        show_huffman_codes(root, a, 0, guide_file);
        fclose(guide_file);

        printf("[OK] Guide file created: %s\n", guide_path);

//-------------------- Reading from guide file and creating hf_queue --------------------

        FILE *read_guide = fopen(guide_path, "r");
        if (read_guide == NULL) {
            printf("Error: Guide file couldn't be opened!\n");
            return 1;
        }

        Hf_code *node = NULL;
        char code[100], code1[100];

        while (!feof(read_guide)) {
            int index = 0;
            while ((code[index] = (char) fgetc(read_guide)) != ' ') {
                if (code[index] == EOF) {
                    break;
                }
                index++;
            }
            code[index] = '\0';

            index = 0;
            int k = 0;
            while ((code1[index] = (char) fgetc(read_guide)) != '\n') {
                if (code[index] == EOF) {
                    k = 1;
                    break;
                }
                index++;
            }
            if (k == 0) {
                int value = 0;
                for (int i = 0; i < index; i++) {
                    value += (code1[i] - '0');
                    value *= 10;
                }
                value /= 10;
                node = add_to_hf_queue(node, code, value);
            }
        }

        fclose(read_guide);

//-------------------------------- Building binary file ---------------------------------

        char binary_path[200];
        get_output_path(binary_path, "Binary.txt");

        FILE *binary_file, *first_file;

        first_file = fopen(argv[2], "r");
        if (first_file == NULL) {
            printf("Error: File couldn't be opened!\n");
            return 1;
        }

        binary_file = fopen(binary_path, "w");
        if (binary_file == NULL) {
            printf("Error: Binary file couldn't be created!\n");
            return 1;
        }

        while (!feof(first_file)) {
            int w;
            w = fgetc(first_file);
            if (w != -1) {
                fprintf(binary_file, "%s", search_hf_queue(node, w));
            }
        }

        fclose(first_file);
        fclose(binary_file);

        printf("[OK] Binary encoding completed.\n");

//------------------------------- Building compressed file -------------------------------

        char compressed_path[200];
        get_output_path(compressed_path, "Compressed.txt");

        FILE *compress_file = fopen(compressed_path, "w");
        if (compress_file == NULL) {
            printf("Error: Compressed file couldn't be created!\n");
            return 1;
        }

        binary_file = fopen(binary_path, "r");
        if (binary_file == NULL) {
            printf("Error: Binary file couldn't be opened!\n");
            return 1;
        }

        while (!feof(binary_file)) {
            int ascii = 0, val;
            for (int i = 0; i < 7; i++) {
                if ((val = fgetc(binary_file)) != -1) {
                    ascii += val - 48;
                    ascii *= 2;
                }
                else {
                    ascii *= 2;
                }
            }
            fprintf(compress_file, "%c", (ascii + 64) / 2);
        }

        fclose(compress_file);
        fclose(binary_file);

        printf("[OK] Compression completed: %s\n", compressed_path);

//---------------------------------- Adding goal number ----------------------------------

        FILE *goal_number = fopen(binary_path, "r");
        if (goal_number == NULL) {
            printf("Error: File couldn't be opened!\n");
            return 1;
        }

        compress_file = fopen(compressed_path, "a");
        if (compress_file == NULL) {
            printf("Error: File couldn't be opened!\n");
            return 1;
        }

        long long int i = -1;
        while (!feof(goal_number)) {
            fgetc(goal_number);
            i++;
        }

        i = 7 - (i % 7);

        fprintf(compress_file, "%lld", i);

        fclose(compress_file);
        fclose(goal_number);

//----------------------------- Free the allocated memory --------------------------------

        free_queue(head);
        free_hf_queue(node);

//--------------------------------- Cleanup temporary files ------------------------------

        delete_file(binary_path);

        printf("[OK] Compression completed successfully!\n");
        printf("    Guide file: %s\n", guide_path);
        printf("    Compressed file: %s\n", compressed_path);

        return 0;
    }

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//                          |-- DECOMPRESSION --|
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

    else if (strcmp(argv[1], "decom") == 0) {

        if (argc < 4) {
            printf("Error: Please provide compressed and guide files.\n");
            printf("Usage: main decom <compressed_file> <guide_file>\n");
            return 1;
        }

//------------------------------- Reading the guide file ----------------------------------

        FILE *read_guide = fopen(argv[3], "r");
        if (read_guide == NULL) {
            printf("Error: Guide file '%s' couldn't be opened!\n", argv[3]);
            return 1;
        }

        Hf_code *node = NULL;
        char code[100], code1[100];

        while (!feof(read_guide)) {
            int index = 0;
            while ((code[index] = (char) fgetc(read_guide)) != ' ') {
                if (code[index] == EOF) {
                    break;
                }
                index++;
            }
            code[index] = '\0';

            index = 0;
            int k = 0;
            while ((code1[index] = (char) fgetc(read_guide)) != '\n') {
                if (code[index] == EOF) {
                    k = 1;
                    break;
                }
                index++;
            }
            if (k == 0) {
                int value = 0;
                for (int i = 0; i < index; i++) {
                    value += (code1[i] - '0');
                    value *= 10;
                }
                value /= 10;
                node = add_to_hf_queue(node, code, value);
            }
        }

        fclose(read_guide);

        printf("[OK] Guide file read successfully.\n");

//------------------------------- Creating binary2 file ----------------------------------

        FILE *read_file = fopen(argv[2], "r");
        if (read_file == NULL) {
            printf("Error: Compressed file '%s' couldn't be opened!\n", argv[2]);
            return 1;
        }

        long long int s = -1;
        while (!feof(read_file)) {
            fgetc(read_file);
            s++;
        }

        fclose(read_file);

        char binary2_path[200];
        get_output_path(binary2_path, "Binary2.txt");

        FILE *binary_file = fopen(binary2_path, "w");
        if (binary_file == NULL) {
            printf("Error: Temporary file couldn't be created!\n");
            return 1;
        }

        read_file = fopen(argv[2], "r");
        if (read_file == NULL) {
            printf("Error: File couldn't be opened!\n");
            return 1;
        }

        for (int i = 0; i < s - 1; i++) {
            int a = fgetc(read_file);
            binary(a - 32, binary_file);
        }

        int goal_number = fgetc(read_file);
        goal_number -= 48;

        fclose(read_file);
        fclose(binary_file);

        printf("[OK] Binary decoding completed.\n");

        read_file = fopen(binary2_path, "r");
        if (read_file == NULL) {
            printf("Error: File couldn't be opened!\n");
            return 1;
        }

        long long int s1 = -1;
        while (!feof(read_file)) {
            fgetc(read_file);
            s1++;
        }

        fclose(read_file);

//----------------------------- Building huffman tree -----------------------------------

        Tree *main_tree = (Tree *) malloc(sizeof(Tree));
        if (main_tree == NULL) {
            printf("Error: Memory allocation failed!\n");
            return 1;
        }

        main_tree->right = NULL;
        main_tree->left = NULL;

        while (node != NULL) {
            main_tree = add_to_tree(main_tree, node->code, node->data);
            node = node->next;
        }

//---------------------------- Creating Decompressed file ----------------------------------

        char decompressed_path[200];
        get_output_path(decompressed_path, "Decompressed.txt");

        FILE *decompress = fopen(decompressed_path, "w");
        if (decompress == NULL) {
            printf("Error: Decompressed file couldn't be created!\n");
            return 1;
        }

        binary_file = fopen(binary2_path, "r");
        if (binary_file == NULL) {
            printf("Error: File couldn't be opened!\n");
            return 1;
        }

        Tree *copy = main_tree;
        for (int i = 0; i < s1 - goal_number; i++) {
            int b = fgetc(binary_file);

            if (b == 49) {
                copy = copy->right;
            }
            else if (b == 48) {
                copy = copy->left;
            }

            if (copy->left == NULL && copy->right == NULL) {
                fprintf(decompress, "%c", copy->data);
                copy = main_tree;
            }
        }

        fclose(decompress);
        fclose(binary_file);

        printf("[OK] Decompression completed: %s\n", decompressed_path);

//----------------------------- Free allocated memory ------------------------------------

        free_hf_queue(node);
        free_tree(main_tree);

//--------------------------------- Cleanup temporary files ------------------------------

        delete_file(binary2_path);

        printf("[OK] Decompression completed successfully!\n");
        printf("    Decompressed file: %s\n", decompressed_path);

        return 0;
    }

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//                                 |-- HELP --|
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

    else if (strcmp(argv[1], "help") == 0) {
        printf("--------------------------------------------------------------------------------------------\n");
        printf("                    HUFFMAN TEXT COMPRESSOR - User Guide\n\n");
        printf("COMPRESSION:\n");
        printf("  Usage: main com <input_file>\n");
        printf("  Example: main com sample.txt\n");
        printf("  Output files (in 'output' folder):\n");
        printf("    - Guide.txt: Huffman code mapping (needed for decompression)\n");
        printf("    - Compressed.txt: Your compressed file\n\n");
        printf("DECOMPRESSION:\n");
        printf("  Usage: main decom <compressed_file> <guide_file>\n");
        printf("  Example: main decom Compressed.txt Guide.txt\n");
        printf("  Output file (in 'output' folder):\n");
        printf("    - Decompressed.txt: Your decompressed file\n\n");
        printf("TIPS:\n");
        printf("  - Place input files in the 'samples' folder for organization\n");
        printf("  - Compressed and decompressed files are saved in the 'output' folder\n");
        printf("  - Temporary files (Binary.txt, Binary2.txt) are automatically cleaned up\n");
        printf("--------------------------------------------------------------------------------------------\n");
        return 0;
    }

    printf("Error: Unknown command '%s'\n", argv[1]);
    printf("Available commands: com, decom, help\n");
    return 1;
}
