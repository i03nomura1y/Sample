// created date : 2011/11/12 23:03:53
// last updated : 2011/11/12 23:05:11
// 正規表現
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
 
int main() {
  char str[] = "123, 456, 789";
  regex_t preg;
  size_t nmatch = 5;
  regmatch_t pmatch[nmatch];
  int i, j;
 
  //char *regex = "([[:digit:]]+), ([[:digit:]]+), ([[:digit:]]+)";
  char *regex = "[[:digit:]]+";

  if(regcomp(&preg, regex, REG_EXTENDED|REG_NEWLINE) != 0){
	printf("regex compile failed.\n");
	exit(1);
  }
 
  printf("String: %s\n", str);
  printf("RegEx : %s\n", regex);
 
  if(regexec(&preg, str, nmatch, pmatch, 0) != 0) {
	printf("No match.\n");
  }else{
	for(i = 0; i < nmatch; i++){
	  if (pmatch[i].rm_so >= 0 && pmatch[i].rm_eo >= 0) {
		printf("Match pos = %d, %d , str = ",
			   (int)pmatch[i].rm_so, (int)pmatch[i].rm_eo);
		for(j = pmatch[i].rm_so ; j < pmatch[i].rm_eo; j++) putchar(str[j]);
	  }
	  printf("\n");
	}
  }
 
  regfree(&preg);
  return 0;
}
