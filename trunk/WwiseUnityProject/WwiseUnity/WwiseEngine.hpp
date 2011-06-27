//////////////////////////////////////////////////////////////////////
//
// Author: Adrien "Lucyberad" Bock.
//
//////////////////////////////////////////////////////////////////////

#ifndef WWISEUNITY_WWISEENGINE_HPP
#define WWISEUNITY_WWISEENGINE_HPP

#include <stdlib.h> //for malloc & free
#include <windows.h> //for DWORD & others.
#include <exception>

#include "WwiseUnityTypes.hpp"

#include <AK/SoundEngine/Common/AkMemoryMgr.h>					// Memory Manager
#include <AK/SoundEngine/Common/AkModule.h>						// Default memory and stream managers
#include <AK/Tools/Common/AkPlatformFuncs.h>					// Thread defines
#include <AK/SoundEngine/Common/IAkStreamMgr.h>					// Streaming Manager
#include "AkFilePackageLowLevelIOBlocking.h"					// Sample low-level I/O implementation (in $(WWISESDK)/samples/SoundEngine/Win32).
#include <AK/SoundEngine/Common/AkSoundEngine.h>				// Sound engine
#include <AK/MusicEngine/Common/AkMusicEngine.h>				// Music Engine
#include <AK/SoundEngine/Common/AkTypes.h>
#include <AK/SoundEngine/Common/AkSpeakerConfig.h>


#ifdef DEBUG
    #include <AK/Comm/AkCommunication.h>
#endif
#ifdef WWISEUNITY_VORBIS										//if defined, link AkVorbisDecoder.lib
	#include <AK/Plugin/AkVorbisFactory.h>
#endif

#ifdef WWISEUNITY_PLUGIN_FLANGER								//if defined, link AkFlangerFX.lib
	#include <AK/Plugin/AkFlangerFXFactory.h>
#endif

#ifdef WWISEUNITY_PLUGIN_PARAMETRICEQ							//if defined, link AkParametricEQFX.lib
	#include <AK/Plugin/AkParametricEQFXFactory.h>
#endif

#ifdef WWISEUNITY_PLUGIN_DISTORTION								//if defined, link AkGuitarDistortionFX.lib
#include <AK/Plugin/AkGuitarDistortionFXFactory.h>
#endif

#ifdef WWISEUNITY_PLUGIN_MATRIXREVERB							//if defined, link AkMatrixReverbFX.lib
#include <AK/Plugin/AkMatrixReverbFXFactory.h>
#endif

#ifdef WWISEUNITY_PLUGIN_PEAKLIMITER							//if defined, link AkPeakLimiterFX.lib
#include <AK/Plugin/AkPeakLimiterFXFactory.h>
#endif

#ifdef WWISEUNITY_PLUGIN_ROOMVERB								//if defined, link AkRoomVerbFX.lib
#include <AK/Plugin/AkRoomVerbFXFactory.h>
#endif

#ifdef WWISEUNITY_PLUGIN_DELAY									//if defined, link AkDelayFX.lib
#include <AK/Plugin/AkDelayFXFactory.h>
#endif

#ifdef WWISEUNITY_PLUGIN_SILENCE
#include <AK/Plugin/AkSilenceSourceFactory.h>					//if defined, link AkSilenceSource.lib
#endif

namespace WwiseUnity
{
	class WwiseEngine
	{
	private:
		// We're using the default Low-Level I/O implementation that's part
		// of the SDK's sample code, with the file package extension
		CAkFilePackageLowLevelIOBlocking g_lowLevelIO; //This is the File Location Resolver.

		static WwiseEngine* _singleton;

	// define the static instance for native interface use
	public:
		static WwiseEngine* getInstance();
		static void killSingleton();

	public:
		bool Init();
		void ProcessAudio();
		void Term();

		int SetBasePath(WU_STRING basePath);
		int SetLangSpecificDirName(WU_STRING specificDirName);

		int LoadBank(WU_STRING bankName);
		int UnloadBank(WU_STRING bankName);

		int RegisterGameObject(AkGameObjectID akId, WU_STRING gameObjectLabel);
		int UnregisterGameObject(AkGameObjectID akId);
		int UnregisterAllGameObject();

		void PostEvent(WU_STRING eventName, AkGameObjectID gameObject);
		void PostEvent(AkUniqueID eventId, AkGameObjectID gameObject);

		void SetRTPCValue(WU_STRING rtpcName, AkRtpcValue value);
		void SetRTPCValue(WU_STRING rtpcName, AkRtpcValue value, AkGameObjectID  gameObjectId);
		void SetRTPCValue(AkRtpcID rtpcId, AkRtpcValue value, AkGameObjectID  gameObjectId);

		void SetState(WU_STRING stateGroup, WU_STRING state);
		void SetState(AkStateGroupID stateGroupId, AkStateID stateId);

		void SetSwitch(WU_STRING switchGroupName, WU_STRING switchName, AkGameObjectID gameObjectId);
		void SetSwitch(AkStateGroupID switchGroupId, AkStateID switchId, AkGameObjectID gameObjectId);

		int SetListenerPosition(AkListenerPosition& akPosition);
		int SetListenerPosition(int listenerIndex, AkListenerPosition& akPosition);

		int SetPosition(AkGameObjectID gameObjectId, AkSoundPosition& position);
		int SetPosition(AkGameObjectID gameObjectId, AkSoundPosition& position, int listenerIndex);

		int SetGameObjectActiveListeners(AkGameObjectID gameObjectId, AkUInt32 listenerMask);

		int PostTrigger( AkTriggerID in_triggerID, AkGameObjectID in_gameObjectID );
		int PostTrigger( WU_STRING in_pszTrigger, AkGameObjectID in_gameObjectID );

		int SetListenerSpatialization( AkUInt32 in_uIndex, bool in_bSpatialized );

		AkChannelMask	MyChannelMaskFromNumChannels( unsigned int in_uNumChannels );
		unsigned int	MyChannelMaskToNumChannels( AkChannelMask in_uChannelMask );
		AkChannelMask	GetSpeakerConfiguration();

	};
}

#endif
