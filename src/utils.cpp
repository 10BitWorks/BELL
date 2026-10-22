#include "utils.h"


/**
 * @brief Case-insensitive substring search.
 * @param haystack The string to be searched.
 * @param needle The substring to search for.
 * @return Pointer to the first occurrence of needle in haystack, or NULL if not found.
 */
char *my_strcasestr(const char *haystack, const char *needle) {
    if (!*needle) return (char *)haystack;
    for (; *haystack; haystack++) {
        if (tolower((unsigned char)*haystack) == tolower((unsigned char)*needle)) {
            const char *h, *n;
            for (h = haystack, n = needle; *h && *n; h++, n++) {
                if (tolower((unsigned char)*h) != tolower((unsigned char)*n)) break;
            }
            if (!*n) return (char *)haystack;
        }
    }
    return NULL;
}

/**
 * Counts the number of times a char is found in a null-terminated char array.
 */
size_t count_char(const char* buffer, char target) {
    size_t count = 0;
    while (*buffer) { // Iterates until the null terminator '\0'
        if (*buffer == target) count++;
        buffer++;
    }
    return count;
}

/**
 * Test if a delimited char array contains only delimeters, white space, and numeric characters.
 * @param buffer The char array to check (e.g., "10, 25, 30")
 * @param separator The separator char
 * @return true if the delimited char array is valid, false otherwise.
 */
bool is_csv_valid(const char *buffer, char delimiter) {

    if((buffer == NULL) || (*buffer == '\0')) return false;

    bool is_valid = true;
    
    while (*buffer) {
        if (isdigit((unsigned char)*buffer)) {
            // skip numeric digits
        } else if (isspace((unsigned char)*buffer)) {
            // Skip whitespace
        } else if (*buffer == delimiter) {
            // Skip delimiter
        } else {
            is_valid = false;
            printf("Invalid character found: '%c' (ASCII %d)\n", *buffer, (unsigned char)*buffer);
        }
        buffer++;
    }

    return is_valid;
}

/**
 * Validates if a char array is a properly formatted CSV of positive integers.
 * Returns true if valid, false otherwise.
 */
bool isValidPositiveIntCSV(const char* buffer, char delimiter) {
    if (buffer == NULL || *buffer == '\0') return false; // Fail on empty/null input

    bool expectingNumber = true; // State: Are we currently looking for a number?
    bool hasNumber = false;      // Track if at least one number was found

    for (int i = 0; buffer[i] != '\0'; i++) {
        char c = buffer[i];

        if (isdigit((unsigned char)c)) {
            expectingNumber = false;
            hasNumber = true;
        } else if (c == delimiter) {
            // Error if we find a delimiter when we were expecting a number 
            // (e.g., leading or consecutive commas delimiters)
            if (expectingNumber) return false;
            expectingNumber = true;
        } else if (isspace((unsigned char)c)) {
            // Optional: Skip whitespace between numbers and commas
            continue; 
        } else {
            // Any other character (negatives '-', letters, symbols) is invalid
            return false;
        }
    }

    // Final check: Must end with a number (not a delimiter) and have at least one value
    return !expectingNumber && hasNumber;
}

/**
 * @brief Parses a delimeted char array into uint32_t without modifying the input.
 * @param input The original char array (not modified).
 * @param delimiter The character used to separate values.
 * @param outputArray The array to store extracted integers.
 * @param max_elements Capacity of the output array.
 * @return Number of integers successfully extracted.
 */
size_t parse_csv_into_integer_array(const char *input, char delimiter, uint32_t *outputArray, size_t maxElements) {
    size_t count = 0;
    const char *start = input;
    const char *end;

    while (count < maxElements && *start != '\0') {
        // Find the next delimiter
        end = strchr(start, delimiter);

        if (end != NULL) {
            // Found delimiter: parse between start and end
            char temp[32]; // Temporary buffer for substring
            size_t len = end - start;
            if (len >= sizeof(temp)) len = sizeof(temp) - 1; // Prevent overflow
            
            strncpy(temp, start, len);
            temp[len] = '\0'; // Null-terminate
            
            outputArray[count++] = (uint32_t)strtoul(temp, NULL, 10);
            start = end + 1; // Move past the delimiter
        } else {
            // No more delimiters: parse the rest
            outputArray[count++] = (uint32_t)strtoul(start, NULL, 10);
            break;
        }
    }
    return count;
}

/**
 * @brief Converts a uint32_t array to a delimited char array.
 * @param input: Pointer to the uint32_t array
 * @param length: Number of elements in the array
 * @param output: Buffer to store the resulting delimited char array
 * @param outputSize: Size of the output buffer
 */
void integer_array_to_csv(uint32_t *input, size_t length, char *output, size_t outputSize) {
    // Example usage
    // uint32_t rawData[] = {1000, 25000, 321, 4000000};
    // char csvBuffer[100]; // Ensure this is large enough
    // integer_array_to_csv(rawData, 4, csvBuffer, sizeof(csvBuffer));

    char temp[16]; // Temporary buffer for each number
    output[0] = '\0'; // Initialize char array as empty with null as first char.

    for (size_t i = 0; i < length; i++) {
        // Format the number (decimal: %u, hex: %lx)
        snprintf(temp, sizeof(temp), "%u", input[i]);
        
        // Append to output
        strcat(output, temp);
        
        // Append comma if not the last element
        if (i < length - 1) {
            strcat(output, ",");
        }
    }
}

void report_array_uint32(uint32_t *array, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("[%u] = %u\n", i, array[i]);
    }
    printf("\n");
}
