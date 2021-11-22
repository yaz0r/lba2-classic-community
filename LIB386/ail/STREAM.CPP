#include	<system\adeline.h>

#ifdef	YAZ_WIN32
#include	<system\winsys.h>
#else
#include	<system\dossys.h>
#endif

#include	<ail\common.h>
#include	<ail\sample.h>
#include	<ail\stream.h>

#pragma pack(8)
#include	"soloud.h"
#include	"soloud_wav.h"
#pragma pack(1)

#include	<assert.h>

#include 	<stdlib.h>
#include 	<string.h>

#include	<stdio.h>

//████████████████████████████████████████████████████████████████████████████

#define	Scale(value, scale, range)	( ( (value)*(scale) + (1<<(range-1)) ) >> range )

//████████████████████████████████████████████████████████████████████████████

extern	S32		LibWaveMasterVolume	;

//████████████████████████████████████████████████████████████████████████████

static	char*		Stream			;
static	S32		StreamVolume = 127	;
static	S32		PausedPos		;
static	char		StreamPathName[_MAX_PATH];
static	char		PausedPathName[_MAX_PATH];

//████████████████████████████████████████████████████████████████████████████

static	VOID_FUNC	*StreamManageProc	;

//████████████████████████████████████████████████████████████████████████████

static	VOID_FUNC	ManageStream		;

//████████████████████████████████████████████████████████████████████████████

U32 soloudHandle = 0;
SoLoud::Wav* soloudWave = nullptr;
SoLoud::Soloud* soloudStream = NULL;


static void	ManageStream()
{
	if( Sample_Driver_Enabled && Stream )
	{
		//yaz AIL_service_stream(Stream, 0)	;
	}

	if(StreamManageProc)
	{
		StreamManageProc()	;
	}
}

//████████████████████████████████████████████████████████████████████████████

static void PlayThisStream(char *name, S32 pos)
{
	if( !Sample_Driver_Enabled )	return	;

	StopStream()	;

	//xesf
	//{
	//	FILE * pFile = fopen(name, "rb");
	//	if(pFile == NULL)
	//		return;

	//	fseek(pFile, 0, SEEK_END);
	//	int fileSize = ftell(pFile);
	//	fseek(pFile, 0, SEEK_SET);

	//	char* ptrsample = (char*)malloc(fileSize);
	//	fread(ptrsample, fileSize, 1, pFile);
	//	fclose(pFile);

	//	///

	//	int numChannels = *(short*)((char*)ptrsample + 22);
	//	int sampleRate = *(U32*)((char*)ptrsample + 24);
	//	int bitsPerSample = *(short*)((char*)ptrsample + 34);

	//	char* dataPtr =  ((char*)ptrsample + 36);
	//	while(*(U32*)dataPtr != 'atad')
	//	{
	//		dataPtr++;
	//	}

	//	int samplesSize = *(U32*)(dataPtr + 4);
	//	char * samplesPtr = dataPtr + 8;

	//	
	//	////
	//	int numSamples = samplesSize * 2;
	//	Stream = samplesPtr = (char*)malloc(numSamples * 4);

	//	S16 stepIndex = 0;
	//	S16 predicted = 0;

	//	int adpcm_decode_init(int numChannels);
	//	int adpcm_decode_frame(void *data, int *data_size,unsigned char *buf, int buf_size);

	//	short* decompressedData = (short*)samplesPtr;
	//	unsigned char* inputData = (unsigned char*)dataPtr+8;

	//	int sizeLeftToDecode = samplesSize;

	//	int maxFrameSize= 0x400;
	//	if(sampleRate == 44100)
	//	{
	//		maxFrameSize *=2;
	//	}

	//	adpcm_decode_init(numChannels);
	//	while(sizeLeftToDecode)
	//	{
	//		int frameSize = maxFrameSize;

	//		if(frameSize > sizeLeftToDecode)
	//			frameSize = sizeLeftToDecode;

	//		int decodedSize;
	//		adpcm_decode_frame(decompressedData, &decodedSize, inputData, frameSize);

	//		inputData+=frameSize;
	//		sizeLeftToDecode-=frameSize;
	//		decompressedData+=decodedSize/2;
	//	}


	//	samplesSize = (char*)decompressedData - samplesPtr;

	//	/*
	//	if(streamSource == 0)
	//	{
	//		alGenSources(1, &streamSource);
	//	}

	//	alGenBuffers(1, &streamBuffer);

	//	ALenum error = alGetError();
	//	alBufferData(streamBuffer, AL_FORMAT_STEREO16, samplesPtr, samplesSize, sampleRate);
	//	error = alGetError();
	//	alSourcei(streamSource, AL_BUFFER, streamBuffer);
	//	error = alGetError();

	//	alSourcePlay(streamSource);
	//	*/
	//	free(ptrsample);
	//	
	//}

	//xesf if(!Stream)			return	;

	strcpy(StreamPathName, name)		;

	//yaz AIL_set_stream_position(Stream, pos)	;

	ChangeVolumeStream(
#ifdef	YAZ_WIN32
			UseWaveMixer?StreamVolume:
#endif//YAZ_WIN32
			Scale(StreamVolume, LibWaveMasterVolume, 7));

	//yaz AIL_start_stream(Stream)		;

	// xesf
	soloudWave = new SoLoud::Wav();
	soloudWave->load(StreamPathName);
	soloudHandle = soloudStream->play(*soloudWave, -1, 0, true, 0);
	soloudStream->setAutoStop(soloudHandle, true);
	soloudStream->setPause(soloudHandle, false);

	ManageStream()				;
}

//████████████████████████████████████████████████████████████████████████████

void	OpenStream()
{
	static	char init = TRUE	;

	if(init)
	{
//yaz		StreamManageProc = ManageProc	;
//yaz		ManageProc	 = ManageStream	;
		init 		 = FALSE	;

		// xesf
		S32 rate = 44100;
		S32 chans = 2;
		soloudStream = new SoLoud::Soloud();
		soloudStream->init(SoLoud::Soloud::CLIP_ROUNDOFF, SoLoud::Soloud::BACKENDS::AUTO, rate, 0, chans);
	}
}

//████████████████████████████████████████████████████████████████████████████

void	PlayStream(char *name)
{
	PlayThisStream(name, 0)	;
}

//████████████████████████████████████████████████████████████████████████████

void	ChangeVolumeStream(S32 volume)
{
	if(volume>127)
	{
		volume = 127	;
	}
	else if (volume<0)
	{
		volume = 0	;
	}

	StreamVolume = volume	;

	//xesf
	if( !Sample_Driver_Enabled || !Stream || !soloudWave)	return ;

	//yaz AIL_set_stream_volume(Stream,
#ifdef	YAZ_WIN32
	//yaz 		UseWaveMixer?StreamVolume:
#endif//YAZ_WIN32
	//yaz 		Scale(StreamVolume, LibWaveMasterVolume, 7));

}

//████████████████████████████████████████████████████████████████████████████

S32	GetVolumeStream()
{
	return	StreamVolume	;
}

//████████████████████████████████████████████████████████████████████████████

void	StopStream()
{
	// xesf
	soloudStream->stop(soloudHandle);
	delete soloudWave;
	soloudWave = nullptr;
	soloudHandle = 0;
	StreamPathName[0] = 0;

	if( !Sample_Driver_Enabled || !Stream || !soloudWave)	return ;

	//alSourceStop(streamSource);
	
	free(Stream);
	//alDeleteBuffers(1, &streamBuffer);
	//streamBuffer = 0;

	Stream = NULL		;
	//xesf StreamPathName[0] = 0	;
}

//████████████████████████████████████████████████████████████████████████████

void	PauseStream()
{
	if(!IsStreamPlaying())		return	;

	//yaz AIL_pause_stream(Stream, TRUE)		;
	//alSourcePause(streamSource);

	// xesf
	soloudStream->setPause(soloudHandle, true);

	ManageStream()				;

	//PausedPos = AIL_stream_position(Stream)	;
	strcpy(PausedPathName, StreamPathName)	;

	//xesf StopStream()				;
}

//████████████████████████████████████████████████████████████████████████████

void	ResumeStream()
{
	if( !PausedPathName[0] )	return ;

	//xesf PlayThisStream(PausedPathName, PausedPos) ;

	// xesf
	soloudStream->setPause(soloudHandle, false);

	PausedPathName[0] = 0	;
}

//████████████████████████████████████████████████████████████████████████████

S32	IsStreamPlaying()
{
	S32	playing = false	;

	//xesf
	if( !Sample_Driver_Enabled || !soloudWave )	return FALSE ; //|| !Stream 

	ManageStream()			;

	//ALint status;
	//alGetSourcei(streamSource, AL_SOURCE_STATE, &status);

	//playing = (status != AL_STOPPED);

	// xesf
	playing = soloudStream->isValidVoiceHandle(soloudHandle);

	if(!playing)	StopStream()	;

	return	playing	;
}

//████████████████████████████████████████████████████████████████████████████

char	*StreamName()
{
	IsStreamPlaying()	;

	return	StreamPathName	;
}

//████████████████████████████████████████████████████████████████████████████
