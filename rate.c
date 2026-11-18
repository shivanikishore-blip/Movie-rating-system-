/*
 * Movie Rating System - C CGI backend
 * Receives POST data such as rating=5, stores ratings in ratings.txt,
 * and returns the current average as JSON.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE "ratings.txt"

int main(void) {
    char *length_text = getenv("CONTENT_LENGTH");
    int length = length_text ? atoi(length_text) : 0;
    char body[256] = {0};
    int rating = 0, ch, i;
    FILE *fp;
    int total = 0, count = 0;

    if (length < 0 || length >= (int)sizeof(body)) length = 0;
    for (i = 0; i < length && (ch = getchar()) != EOF; i++)
        body[i] = (char)ch;

    if (sscanf(body, "rating=%d", &rating) != 1 || rating < 1 || rating > 5) {
        printf("Content-Type: application/json\r\n\r\n");
        printf("{\"success\":false,\"message\":\"Rating must be between 1 and 5.\"}");
        return 0;
    }

    fp = fopen(DATA_FILE, "a");
    if (!fp) {
        printf("Content-Type: application/json\r\n\r\n");
        printf("{\"success\":false,\"message\":\"Cannot open ratings file.\"}");
        return 0;
    }
    fprintf(fp, "%d\n", rating);
    fclose(fp);

    fp = fopen(DATA_FILE, "r");
    if (fp) {
        while (fscanf(fp, "%d", &ch) == 1) {
            total += ch;
            count++;
        }
        fclose(fp);
    }

    printf("Content-Type: application/json\r\n");
    printf("Access-Control-Allow-Origin: *\r\n\r\n");
    if (count > 0)
        printf("{\"success\":true,\"average\":%.2f,\"count\":%d}", (double)total / count, count);
    else
        printf("{\"success\":false,\"message\":\"No ratings found.\"}");
    return 0;
}
