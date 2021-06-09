#ifndef Parser_h
#define Parser_h
// простой и быстрый парсер строк в отдельные строки и числа

class Parser {
  public:
    Parser (char* data, char newDiv = ',') {
      buf = data;
      div = newDiv;
    }
    
    ~Parser() {
      clear();
    }
    
    void clear() {
      if (str) free(str);
    }
    
    int amount() {
      int i = 0, count = 0;
      while (buf[i++]) if (buf[i] == div) count++;  // подсчёт разделителей
      return ++count;
    }
    
    int parseInts(int* data) {
      int count = 0;
      char* offset = buf;
      while (true) {
        data[count++] = atoi(offset);
        offset = strchr(offset, div);
        if (offset) offset++;
        else break;
      }
      return count;
    }
    
    char* buf = NULL;
    char** str = NULL;

    char* operator [] (uint16_t idx) {
      return str[idx];
    }
    
    char div;
  private:
};

#endif
