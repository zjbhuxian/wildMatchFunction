#include <iostream>
using namespace std;
#define MATCH_CHAR(c1, c2, ignore_case) ((c1==c2) || ((ignore_case) && (tolower(c1)==tolower(c2))))

bool enumWildCharMatch(const char *src, const char *pattern, bool ignore_case)
{
  bool ret = false;
  while(*src){
    /**
     * If the current character of pattern is '*',
     * pass it until the character is not '*'.
     */
    if(*pattern == '*'){
      while((*pattern == '*') || (*pattern == '?'))
        pattern++;

      /* If no character after '*', namely matched. */
      if(!*pattern)return true;

      /* Match the rest of characters in pattern */
      while(*src && (!MATCH_CHAR(*src, *pattern, ignore_case)))
        src++;

      /* If no character match, namely matched failed.*/
      if(!*src)return false;

      ret = enumWildCharMatch(src, pattern, ignore_case);

      /**
       * If the rest of characters could not match, but the last character of src matched '*' in pattern
       * in the same location of pattern. Then pass the last character of the src to continue matching the rest of characters.
       */
      while((!ret) && (*(src+1)) && MATCH_CHAR(*(src+1), *pattern, ignore_case))
        ret = enumWildCharMatch(++src, pattern, ignore_case);

      return ret;
    }else{
      /**
       * If the current character of pattern is not '*',
       * match current character.
       */
      if(MATCH_CHAR(*src, *pattern, ignore_case) || ('?' == *pattern))
        return enumWildCharMatch(++src, ++pattern, ignore_case);
      else
        return false;
    }
  }

  if(*pattern)
    return (*pattern == '*') && (*(pattern+1) == 0);

  return true;
}

int main()
{
    std::string orgStr = "testFile.ffs_lock";
    std::string pattern = "*.ffs_lock";
    bool bIgnore_case = false;

    bool bMatch = false;

    bMatch = enumWildCharMatch(orgStr.c_str(), pattern.c_str(), bIgnore_case);

    cout << "Be Match: " << bMatch << endl;
    return 0;
}
