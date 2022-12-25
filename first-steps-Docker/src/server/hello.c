#include <fcgi_stdio.h>

void main(void) {
  while (FCGI_Accept() >= 0) {
    printf("Content-type: text/html\r\n");
    printf("\r\n");
    printf("Hello world!<br>\r\n");
  }
}
