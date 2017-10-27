#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include <errno.h>

#include <ctype.h>
#include <string.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

char hip[32] = "";
int hport;

int serve(int connfd);

int main(int argc, char **argv) {
	int listenfd, connfd;
	struct sockaddr_in addr;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
    sprintf(error_buf, ERROR_PATT, "socket", "main");
    perror(error_buf);
		return 1;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
  if (argc > 1) {
    hport = atoi(argv[1]);
  } else {
    hport = 7788;
  }
	addr.sin_port = htons(hport);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(listenfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    sprintf(error_buf, ERROR_PATT, "bind", "main");
    perror(error_buf);
		return 1;
	}

	if (listen(listenfd, 10) == -1) {
    sprintf(error_buf, ERROR_PATT, "listen", "main");
    perror(error_buf);
		return 1;
	}

	get_local_ip(listenfd, hip);
	printf("host ip address(eth0): %s\n", hip);

	while (1) {
		if ((connfd = accept(listenfd, NULL, NULL)) == -1) {
      sprintf(error_buf, ERROR_PATT, "accept", "main");
      perror(error_buf);
			continue;
		} else {
			if (fork() == 0) {
				printf("Connection accepted.\n");
			} else {
				serve(connfd);
				return 0;
			}
		}
	}

	close(listenfd);
	return 0;
}

int serve(int connfd)
{
  struct ServerState state;

  srand(time(NULL));

  state.command_fd = connfd;
  state.data_fd = -1;
  state.listen_fd = -1;
  state.trans_mode = -1;
  state.logged = 0;
  state.hport = hport;
  state.binary_flag = 1;
  strcpy(state.hip, hip);

  int c_code = 0;
  int len = 0;
  char message[4096];
  char content[4096];

  send_msg(state.command_fd, RES_READY);

  // loop routine
  while ((len = read_msg(connfd, message))) {
    printf("%s", message);
    c_code = parse_command(message, content);

    if (!state.logged && c_code != USER_CODE && c_code != PASS_CODE) {
      send_msg(connfd, RES_WANTUSER);
      continue;
    }

    switch (c_code) {
      case USER_CODE:
        command_user(&state, content);
        break;

      case PASS_CODE:
        command_pass(&state, content);
        break;

      case XPWD_CODE:
        send_msg(connfd, RES_WANTUSER);
        break;

      case QUIT_CODE:
      case ABOR_CODE:
        command_quit(&state);
        return 0;

      case PORT_CODE:
        command_port(&state, content);
        break;

      case PASV_CODE:
        command_pasv(&state);
        break;

      case RETR_CODE:
        command_retr(&state, content);
        break;

      case STOR_CODE:
        command_stor(&state, content);

      case SYST_CODE:
        send_msg(connfd, RES_SYSTEM);
        break;

      case TYPE_CODE:
        command_type(&state, content);
        break;

      case LIST_CODE:
        command_list(&state, content, 1);
        break;

      case NLST_CODE:
        command_list(&state, content, 0);
        break;

      case MKD_CODE:
        command_mkd(&state, content);
        break;

      default:
        command_unknown(&state);
        break;
    }
  }

  close(connfd);
  return 0;
}