#include "audio.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <sys/types.h>
#include <string.h>
// interprocess comm
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <time.h>
// network stuff
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

// string arrays
int copy_size = string_size * 4;
fix28 string_n[string_size];
// drup amp at last time
fix28 string_n_1[string_size];
// drum update
fix28 new_string[string_size];
// initial condition
float triangle_n[string_size];
// C scale
fix28 rho[8];

// musical scale frequencies
//                      C4      D4      E4      F4      G4      A4      B4      C5
// float notes[8] = { 261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25 } ;
float notes[8] = {261.63, 392.0, 261.63, 293.66, 329.63, 440.0, 392.0, 261.63};

clock_t note_time;

// the light weight bus base
void *virtual_base;

// /dev/mem file descriptor
int fd;

void play(void)
{
	// ===========================================
	// drum index
	int i, j, dist2;
	fix28 new_string_temp, temp;
	float famp = 0.25;
	float fsd = 1;
	// sample rate
	float drive_freq, Fs = 48000;

	// read the LINUX clock (microSec)
	// and set the time so that a not plays soon
	note_time = clock();
	// compute the rhos for the scale
	for (i = 0; i < 8; i++)
	{
		// for each note: compute rho = (2*(length-2)*f/Fs)**2
		rho[i] = float2fix28(pow(2.0 * (string_size - 2) * 0.25 * notes[i] / Fs, 2.0));
	}
	j = 0;

	while (1)
	{
		while (((*(AUDIO_PTR + 1) >> 24) & 0xff) > 1)
		{
			// do drum time sample
			for (i = 1; i < string_size - 2; i++)
			{
				temp = string_n[i - 1] + string_n[i + 1] - times2pt0(string_n[i]);
				new_string_temp = multfix28(rho[j], temp);
				new_string[i] = times0pt9999(new_string_temp + times2pt0(string_n[i]) - times0pt9999(string_n_1[i]));
			}

			// update arrays for next step
			memcpy(string_n_1, string_n, copy_size);
			memcpy(string_n, new_string, copy_size);

			// send time sample to the audio FiFOs
			*(AUDIO_PTR + 2) = fix2audio28(new_string[string_out]);
			*(AUDIO_PTR + 3) = fix2audio28(new_string[string_out]);
		}

		if (clock() - note_time > 700000)
		{
			j++;

			// if end of song reached, break
			if (j > 7)
				break;

			for (i = 1; i < string_size - 2; i++)
			{
				// Triangle puck
				triangle_n[i] = (i <= string_pluck) ? ((float)i / (float)string_pluck) : (1 - (((float)i - string_pluck) / (float)(string_size - string_pluck)));
				// Gaussian pluck
				string_n[i] = float2fix28(triangle_n[i] * famp * exp(-(float)(i - string_pluck) * (i - string_pluck) / (fsd * fsd)));
				string_n_1[i] = string_n[i];
			}
			string_n[0] = 0;
			string_n_1[0] = 0;
			string_n[string_size - 1] = 0;
			string_n_1[string_size - 1] = 0;

			// read LINUX time for the next drum strike
			note_time = clock();
		};
	}
}
