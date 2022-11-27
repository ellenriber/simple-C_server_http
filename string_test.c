#include <stdio.h>
#include <string.h>


int test_path() {
	char	request[] = "GET /lelinha HTTP/1.1\r\nHost: localhost:8080 Connection: keep-alive";
	// char	space_delim[] = " ";
	char	*request_line;
	char	*path;
	char	*method;
	char	*protocol;

	printf("%s\n\n", strstr(request, "lelinha"));

	request_line = strtok(request, "\r\n");
	printf("1Requet line = %s\n", request_line);
	method = strtok(request_line, " ");
	printf("Method = %s\n", method);

	path = strtok(NULL, " ");
	printf("Path= %s\n", path);

	protocol = strtok(NULL, " ");
	printf("Protocol= %s\n", protocol);

	printf("Requet = %s\n", request);

	return (0);	
}


int main(void)
{
	if (test_path() == 1) {
		printf("failed test_path");
		return 1;
	}

	return 0;
}
