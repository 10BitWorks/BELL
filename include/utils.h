#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

char *my_strcasestr(const char *haystack, const char *needle);
size_t count_char(const char* buffer, char target);
bool is_csv_valid(const char *buffer, char delimiter);
bool isValidPositiveIntCSV(const char* buffer, char delimiter);
size_t parse_csv_into_integer_array(const char *input, char delimiter, uint32_t *outputArray, size_t maxElements);
void integer_array_to_csv(uint32_t *input, size_t length, char *output, size_t outputSize);
void report_array_uint32(uint32_t *array, size_t length);

#endif