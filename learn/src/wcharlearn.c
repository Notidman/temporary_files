#include "wcharlearn.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <string.h>

void 
run_ls1(void)
{
  const size_t buffer_size = 10;
  wchar_t buf[buffer_size];
  size_t count;

  setlocale(LC_ALL, "");
  fputws(L"Введите своё имя: ", stdout);
  fflush(stdout);

  fgetws(buf, buffer_size, stdin);

  fputws(L"Ваше имя (по буквам): \n", stdout);

  wchar_t *pch;
  if( ( pch = wcschr(buf, L'\n')) != NULL)
      *pch = L'\0';

  for(pch = buf, count = 0; *pch != L'\0'; ++pch, ++count)
  {
    putwchar(*pch);
    putwchar(L' ');
  }

  putwchar(L'\n');

  wprintf(L"Введено букв: %zd\n", count);
}
