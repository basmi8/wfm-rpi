#
/*
 *    Copyright (C)  2009, 2010, 2011
 *    Jan van Katwijk (J.vanKatwijk@gmail.com)
 *    Lazy Chair Programming
 *
 *    This file is part of the SDR-J.
 *    Many of the ideas as implemented in ESDR are derived from
 *    other work, made available through the GNU general Public License. 
 *    All copyrights of the original authors are recognized.
 *
 *    SDR-J is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    SDR-J is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with SDR-J; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef __AUDIO_SINK
#define	__AUDIO_SINK
#include	<QString>
#include	"fm-constants.h"
#include	<portaudio.h>
#include	<stdio.h>
#include	"audio-base.h"
#include	"ringbuffer.h"
#include	<QComboBox>

class	audioSink  : public audioBase {
Q_OBJECT
public:
	                audioSink		(int16_t,
	                                         QComboBox *,
	                                         RingBuffer<int16_t> *);
			~audioSink		(void);
	void		stop			(void);
	void		restart			(void);
public slots:
	bool		set_streamSelector	(int);
private:
	int16_t		numberofDevices		(void);
	QString		outputChannelwithRate	(int16_t, int32_t);
	int16_t		invalidDevice		(void);
	bool		isValidDevice		(int16_t);
	bool		selectDefaultDevice	(void);
	bool		selectDevice		(int16_t);
	int32_t		cardRate		(void);

	bool		OutputrateIsSupported	(int16_t, int32_t);
	void		audioOutput		(float *, int32_t);
	bool		setupChannels		(QComboBox *);
	int32_t		CardRate;
	int16_t		latency;
	int32_t		size;
	bool		portAudio;
	bool		writerRunning;
	int16_t		numofDevices;
	int		paCallbackReturn;
	int16_t		bufSize;
	PaStream	*ostream;
	SNDFILE		*dumpFile;
	RingBuffer<float>	*_O_Buffer;
	PaStreamParameters	outputParameters;

	int16_t		*outTable;
	QComboBox	*streamSelector;
protected:
static	int		paCallback_o	(const void	*input,
	                                 void		*output,
	                                 unsigned long	framesperBuffer,
	                                 const PaStreamCallbackTimeInfo *timeInfo,
					 PaStreamCallbackFlags statusFlags,
	                                 void		*userData);
};

#endif

