
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/sockios.h>
#include <errno.h>
#include <string.h>
#include <linux/if_vnic.h>

static void help(char *program)
{
	fprintf(stderr, "Usage: add [real device name] [virtual device name] [vdev id] \n");
	fprintf(stderr, "       rem [virtual device name] \n");
	fprintf(stderr, "Example #1: %s add eth0 brcm 0 \n", program);
	fprintf(stderr, "        #2: %s rem brcm 0 \n", program);
}

int main(int argc, char *argv[])
{
   	struct vnic_ioctl_args if_request;
	int vid, fd;
	char *cmd, *real_name, *virt_name;

	if (argc < 3) {
		help(argv[0]);
		return 0;
	}

	cmd = argv[1];
	memset(&if_request, 0, sizeof(struct vnic_ioctl_args));
	if (!strcasecmp(cmd, "add")) {
		
		if (strlen(argv[2]) > 10) {
			printf("real device name : the num of characters are no more than 10.\n");
			return -1;
		}
		real_name = argv[2];

		if (strlen(argv[3]) > 10) {
			printf("virtual device name : the num of characters are no more than 10.\n");
			return -1;
		}

		virt_name = argv[3];
		vid = atoi(argv[4]);

		if_request.cmd = ADD_BRCM_CMD;
		strcpy(if_request.real_dev, real_name);
		strcpy(if_request.virt_dev, virt_name);
		if_request.vdev_id= vid;

	} else if (!strcasecmp(cmd, "rem")) {

		if (strlen(argv[2]) > 10) {
			printf("virtual device name : the num of characters are no more than 10.\n");
			return -1;
		}

		virt_name = argv[2];
		vid = atoi(argv[3]);

		if_request.cmd = DEL_BRCM_CMD;
		strcpy(if_request.virt_dev, virt_name);
		if_request.vdev_id= vid;

	} else {
		help(argv[0]);
		return 0;
	}

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      		fprintf(stderr, "FATAL:  Couldn't open a socket..go figure!\n");
      		exit(2);
  	}   

	if (ioctl(fd, SIOCSIFVNIC, &if_request) < 0)
		fprintf(stderr,"ERROR: trying to add/rem brcm: %s\n", strerror(errno));
	return 0;
}
