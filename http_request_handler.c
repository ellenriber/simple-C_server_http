#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

const int ERR_BAD_REQUEST = 1;
const int ERR_METHOD_NOT_ALLOWED = 2;

int *parse_request_line(char *request, char **path, char **method, char **protocol)
{
	char	*request_line;

	request_line = strtok(request, "\r\n");
	*method = strtok(request_line, " ");

	*path = strtok(NULL, " ");

	*protocol = strtok(NULL, " ");

	return 0;	
}

int validate_request_line(char *method, char *protocol)
{
	if(strcmp(protocol, "HTTP/1.1") != 0 && strcmp(protocol, "HTTP/1.0") != 0){
		return ERR_BAD_REQUEST;
	}
	if(strcmp(method, "GET") != 0){
		return ERR_METHOD_NOT_ALLOWED;
	}

	return 0;
}

int	send_response(int socket, char	*response)
{
	return send(socket, response, strlen(response), 0);
}

int	handle_path(int socket, char *path)
{
	char *response;

	if(strcmp(path, "/lelinha") == 0){
		send_response(socket, "HTTP/1.0 200 OK\r\n\r\nOlar Lelinha");
		return 0;
	}	
	if(strcmp(path, "/gustavo") == 0){
		send_response(socket, "HTTP/1.0 200 OK\r\n\r\nOlar Gustavo");
		return 0;
	}
	if(strcmp(path, "/") == 0){
		send_response(socket, "HTTP/1.0 200 OK\r\n\r\nOlar");
		return 0;
	}
	
	send_response(socket, "HTTP/1.0 404 Not Found\r\n");
	return 0;

}

int handle_request(int socket, char *buffer)
{
	char	*path;
	char	*method;
	char	*protocol;
	char 	*response;

	parse_request_line(buffer, &path, &method, &protocol);
	printf("Method = %s, Path = %s, Protocol = %s \n", method, path, protocol);

	switch (validate_request_line(method, protocol))
	{
	case ERR_BAD_REQUEST:
		send_response(socket, "HTTP/1.0 400 Bad Request\r\n");
		return 0;
	case ERR_METHOD_NOT_ALLOWED:
		send_response(socket, "HTTP/1.0 405 Method Not Allowed\r\n");
		return 0;
	}
	
	return handle_path(socket, path);
}
