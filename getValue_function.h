bool checkPattern(char currentChar, int n) {
    static int patternCount = 0;
    static char lastChars[8] = {'\0'}; // Array to store the last 10 characters

    // Check for the specified pattern
    if (
        lastChars[0] == '}' &&
        lastChars[1] == ',' &&
        currentChar == '{'  
    ) {
        patternCount++;
        
        if (patternCount == n) {
            // Reset counters for the next occurrence
            patternCount = 0;
            std::fill(std::begin(lastChars), std::end(lastChars), '\0'); // Reset array to '\0'
            return true;
        }
    } 

    // Shift characters in the array to make room for the new character
    for (int i = 0; i < 7; ++i) {
    lastChars[i] = lastChars[i + 1];
    }
    // Store the current character in the first position
    lastChars[7] = currentChar;

    return false;
}



String getYrValue(HTTPClient &http, String key, int n, int skip, int get) {
  bool found = false, look = false;
  int ind = 0;
  String ret_str = "";

  int len = http.getSize();
  char char_buff[1];
  WiFiClient * stream = http.getStreamPtr();
  while (http.connected() && (len > 0 || len == -1)) {
    size_t size = stream->available();
    if (size) {
      int c = stream->readBytes(char_buff, ((size > sizeof(char_buff)) ? sizeof(char_buff) : size));
      if (len > 0)
        len -= c;
      if (found) {
          if (skip == 0) {
              // Check for the specified pattern to add "}]" to ret_str and break
              if (checkPattern(char_buff[0], n)) {
                  ret_str += "]";
                  break;
              }

              ret_str += char_buff[0];
              get--;

              // Continue collecting until get is satisfied.
              if (get <= 0)
                  break;
          } else {
              skip--;
          }
      }

      else if ((!look) && (char_buff[0] == key[0])) {
        look = true;
        ind = 1;
      } else if (look && (char_buff[0] == key[ind])) {
        ind ++;
        if (ind == key.length()) found = true;
      } else if (look && (char_buff[0] != key[ind])) {
        ind = 0;
        look = false;
      }
    }
  }
  return ret_str;
}


String extractDataByKey(HTTPClient& http, const char* keyword, const char* stop_keyword, int skip) {
    String result = "[";          // Initialize an empty String to store the result
    char currentSubstring[40] = {'\0'};
    int keywordFound = 0;        
    int skipperInit = 0;

    // Get the response stream
    WiFiClient* stream = http.getStreamPtr();

    // Loop while the connection is open and there is data to read
    while (http.connected() && (stream->available() > 0 || stream->available() == -1)) {
        // Read a byte from the stream
        char currentChar = stream->read();

        // Update the last characters buffer
        for (int i = 0; i < strlen(keyword) - 1; ++i) {
            currentSubstring[i] = currentSubstring[i + 1];
        }
        currentSubstring[strlen(keyword) - 1] = currentChar;

        // Check if the current substring matches the specified keyword
        if (strcmp(currentSubstring, keyword) == 0) {
            keywordFound = 1;        // Set the flag to indicate that the keyword is found
            skipperInit = skip;      // Initilize the skipper
            currentSubstring[0] = '\0'; // Reset the buffer
        }

        // If the keyword is found, append the current character to the result string
        if (keywordFound) {
            if (skipperInit == 0) {
                result += currentChar;
                // Check if the current character is '}'. If yes, reset the flag and add ","
                if (currentChar == *stop_keyword) {
                    keywordFound = 0;
                    if (*stop_keyword != ',') {
                        result += ",";
                    }
                    
                }
            }
            else {
              skipperInit -= 1;
            }
            
        }
    }

    // Replace the last character with "]" outside the loop
    if (!result.isEmpty()) {
        result.remove(result.length() - 1);
        result += "]";
    }
    currentSubstring[0] = '\0';

    return result;  // Return the final result string as a String
}
