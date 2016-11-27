/**
 * ALSA midi helper
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/poll.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <alsa/asoundlib.h>

int do_device_list, do_rawmidi_list;
char *port_name = "default";
char *send_file_name;
char *receive_file_name;
char *send_hex;
char *send_data;
int send_data_length;
int receive_file;
int dump;
int timeout;
int stop;
snd_rawmidi_t *input, **inputp;
snd_rawmidi_t *output, **outputp;

static void device_list(void)
{
	int card, err;

	card = -1;
	if ((err = snd_card_next(&card)) < 0) {
		error("cannot determine card number: %s", snd_strerror(err));
		return;
	}
	if (card < 0) {
		error("no sound card found");
		return;
	}
	puts("Dir Device    Name");
	do {
		list_card_devices(card);
		if ((err = snd_card_next(&card)) < 0) {
			break;
		}
	} while (card >= 0);
}

static int is_input(snd_ctl_t *ctl, int card, int device, int sub)
{
	snd_rawmidi_info_t *info;
	int err;

	snd_rawmidi_info_alloca(&info);
	snd_rawmidi_info_set_device(info, device);
	snd_rawmidi_info_set_subdevice(info, sub);
	snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_INPUT);

	if ((err = snd_ctl_rawmidi_info(ctl, info)) < 0 && err != -ENXIO)
		return err;
	else if (err == 0)
		return 1;

	return 0;
}

static int is_output(snd_ctl_t *ctl, int card, int device, int sub)
{
	snd_rawmidi_info_t *info;
	int err;

	snd_rawmidi_info_alloca(&info);
	snd_rawmidi_info_set_device(info, device);
	snd_rawmidi_info_set_subdevice(info, sub);
	snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_OUTPUT);

	if ((err = snd_ctl_rawmidi_info(ctl, info)) < 0 && err != -ENXIO)
		return err;
	else if (err == 0)
		return 1;

	return 0;
}

static void list_device(snd_ctl_t *ctl, int card, int device)
{
	snd_rawmidi_info_t *info;
	const char *name;
	const char *sub_name;
	int subs, subs_in, subs_out;
	int sub, in, out;
	int err;

	snd_rawmidi_info_alloca(&info);
	snd_rawmidi_info_set_device(info, device);

	snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_INPUT);
	snd_ctl_rawmidi_info(ctl, info);
	subs_in = snd_rawmidi_info_get_subdevices_count(info);
	snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_OUTPUT);
	snd_ctl_rawmidi_info(ctl, info);
	subs_out = snd_rawmidi_info_get_subdevices_count(info);
	subs = subs_in > subs_out ? subs_in : subs_out;

	sub = 0;
	in = out = 0;
	if ((err = is_output(ctl, card, device, sub)) < 0) {
		error("cannot get rawmidi information %d:%d: %s",
		      card, device, snd_strerror(err));
		return;
	} else if (err)
		out = 1;

	if (err == 0) {
		if ((err = is_input(ctl, card, device, sub)) < 0) {
			error("cannot get rawmidi information %d:%d: %s",
			      card, device, snd_strerror(err));
			return;
		}
	} else if (err)
		in = 1;

	if (err == 0)
		return;

	name = snd_rawmidi_info_get_name(info);
	sub_name = snd_rawmidi_info_get_subdevice_name(info);
	if (sub_name[0] == '\0') {
		if (subs == 1) {
			printf("%c%c  hw:%d,%d    %s\n",
			       in ? 'I' : ' ', out ? 'O' : ' ',
			       card, device, name);
		} else
			printf("%c%c  hw:%d,%d    %s (%d subdevices)\n",
			       in ? 'I' : ' ', out ? 'O' : ' ',
			       card, device, name, subs);
	} else {
		sub = 0;
		for (;;) {
			printf("%c%c  hw:%d,%d,%d  %s\n",
			       in ? 'I' : ' ', out ? 'O' : ' ',
			       card, device, sub, sub_name);
			if (++sub >= subs)
				break;

			in = is_input(ctl, card, device, sub);
			out = is_output(ctl, card, device, sub);
			snd_rawmidi_info_set_subdevice(info, sub);
			if (out) {
				snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_OUTPUT);
				if ((err = snd_ctl_rawmidi_info(ctl, info)) < 0) {
					error("cannot get rawmidi information %d:%d:%d: %s",
					      card, device, sub, snd_strerror(err));
					break;
				}
			} else {
				snd_rawmidi_info_set_stream(info, SND_RAWMIDI_STREAM_INPUT);
				if ((err = snd_ctl_rawmidi_info(ctl, info)) < 0) {
					error("cannot get rawmidi information %d:%d:%d: %s",
					      card, device, sub, snd_strerror(err));
					break;
				}
			}
			sub_name = snd_rawmidi_info_get_subdevice_name(info);
		}
	}
}

static void list_card_devices(int card)
{
	snd_ctl_t *ctl;
	char name[32];
	int device;
	int err;

	sprintf(name, "hw:%d", card);
	if ((err = snd_ctl_open(&ctl, name, 0)) < 0) {
		return;
	}
	device = -1;
	for (;;) {
		if ((err = snd_ctl_rawmidi_next_device(ctl, &device)) < 0) {
			break;
		}
		if (device < 0)
			break;
		list_device(ctl, card, device);
	}
	snd_ctl_close(ctl);
}
