#include <stdio.h>
#include <stdlib.h>
#include <sttring.h>

#include "payloads.h"
#include "wordlists.h"
#include "common.h"

payloads *make_payloads(const char *url, const char *wordlist, const char *extlist){
    wordlists *words = NULL;
    extlists *exts = NULL;
    payloads *payload = NULL;
  
    if(url == NULL)
      return NULL;
  
    if(words = read_wordlists(wordlist) == NULL)
      return NULL;
  
    if(extlist != NULL){
      if(exts = read_wordlists(extlist) == NULL){
          clear_wordlists(&words);
          return NULL;
      }        
    }
    clear_wordlists(&words);
    clear_wordlists(&exts);
    return payload;
}
