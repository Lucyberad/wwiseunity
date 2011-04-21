//////////////////////////////////////////////////////////////////////
//
// Author: Adrien "Lucyberad" Bock.
//
//////////////////////////////////////////////////////////////////////

#include "WwiseEngine.hpp"
using namespace WwiseUnity;

// Custom alloc/free functions. These are declared as "extern" in AkMemoryMgr.h
// and MUST be defined by the game developer.
namespace AK
{
#ifdef WIN32
    void * AllocHook( size_t in_size )
    {
        return malloc( in_size );
    }
    void FreeHook( void * in_ptr )
    {
        free( in_ptr );
    }
    // Note: VirtualAllocHook() may be used by I/O pools of the default implementation
    // of the Stream Manager, to allow "true" unbuffered I/O (using FILE_FLAG_NO_BUFFERING
    // - refer to the Windows SDK documentation for more details). This is NOT mandatory;
    // you may implement it with a simple malloc().
    void * VirtualAllocHook(
        void * in_pMemAddress,
        size_t in_size,
        DWORD in_dwAllocationType,
        DWORD in_dwProtect
        )
    {
        return VirtualAlloc( in_pMemAddress, in_size, in_dwAllocationType, in_dwProtect );
    }
    void VirtualFreeHook( 
        void * in_pMemAddress,
        size_t in_size,
        DWORD in_dwFreeType
        )
    {
        VirtualFree( in_pMemAddress, in_size, in_dwFreeType );
    }
#endif
}

// init the singleton
WwiseEngine* WwiseEngine::_singleton = NULL;

WwiseEngine* WwiseEngine::getInstance()
{
	if (!_singleton)
	{
		_singleton =  new WwiseEngine();
	}

	return _singleton;
}

void WwiseEngine::killSingleton()
{
	if (!_singleton)
	{
		delete _singleton;
		_singleton = NULL;
	}
}

bool WwiseEngine::Init()
{
	//
    // Create and initialize an instance of the default memory manager. Note
    // that you can override the default memory manager with your own. Refer
    // to the SDK documentation for more information.
    //

    AkMemSettings memSettings;
    memSettings.uMaxNumPools = 20;

    if ( AK::MemoryMgr::Init( &memSettings ) != AK_Success )
    {
		throw std::exception( "Could not create the memory manager." );
        return false;
    }

	//
    // Create and initialize an instance of the default streaming manager. Note
    // that you can override the default streaming manager with your own. Refer
    // to the SDK documentation for more information.
    //

    AkStreamMgrSettings stmSettings;
    AK::StreamMgr::GetDefaultSettings( stmSettings );
    
    // Customize the Stream Manager settings here.
    
    if ( !AK::StreamMgr::Create( stmSettings ) )
    {
        throw std::exception( "Could not create the Streaming Manager" );
        return false;
    }

    //
    // Create a streaming device with blocking low-level I/O handshaking.
    // Note that you can override the default low-level I/O module with your own. Refer
    // to the SDK documentation for more information.        
    //
    AkDeviceSettings deviceSettings;
    AK::StreamMgr::GetDefaultDeviceSettings( deviceSettings );
    
    // Customize the streaming device settings here.
    
    // CAkFilePackageLowLevelIOBlocking::Init() creates a streaming device
    // in the Stream Manager, and registers itself as the File Location Resolver.
    if ( g_lowLevelIO.Init( deviceSettings ) != AK_Success )
    {
        throw std::exception( "Could not create the streaming device and Low-Level I/O system" );
        return false;
    }

    //
    // Create the Sound Engine
    // Using default initialization parameters
    //
    
    AkInitSettings initSettings;
    AkPlatformInitSettings platformInitSettings;
    AK::SoundEngine::GetDefaultInitSettings( initSettings );
    AK::SoundEngine::GetDefaultPlatformInitSettings( platformInitSettings );

    if ( AK::SoundEngine::Init( &initSettings, &platformInitSettings ) != AK_Success )
    {
        throw std::exception( "Could not initialize the Sound Engine." );
        return false;
    }

	//
    // Initialize the music engine
    // Using default initialization parameters
    //
    
    AkMusicSettings musicInit;
    AK::MusicEngine::GetDefaultInitSettings( musicInit );
        
    if ( AK::MusicEngine::Init( &musicInit ) != AK_Success )
    {
        throw std::exception( "Could not initialize the Music Engine." );
        return false;
    }

#ifdef DEBUG
    //
    // Initialize communications (not in release build!)
    //
    AkCommSettings commSettings;
    AK::Comm::GetDefaultInitSettings( commSettings );
    if ( AK::Comm::Init( commSettings ) != AK_Success )
    {
        throw std::exception( "Could not initialize communication." );
        return false;
    }
#endif

#ifdef WWISEUNITY_VORBIS
	AK::SoundEngine::RegisterCodec( AKCOMPANYID_AUDIOKINETIC, 
								    AKCODECID_VORBIS, 
						            CreateVorbisFilePlugin, 
						            CreateVorbisBankPlugin );
#endif

#ifdef WWISEUNITY_PLUGIN_FLANGER

	if ( AK::SoundEngine::RegisterPlugin( AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_FLANGER, CreateFlangerFX, CreateFlangerFXParams ) != AK_Success )
    {
        throw std::exception( "Could not initialize Flanger plugin." );
        return false;
    }

#endif

#ifdef WWISEUNITY_PLUGIN_PARAMETRICEQ

	if ( AK::SoundEngine::RegisterPlugin( AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_PARAMETRICEQ, CreateParametricEQFX, CreateParametricEQFXParams ) != AK_Success )
    {
        throw std::exception( "Could not initialize ParametricEQ plugin." );
        return false;
    }

#endif

#ifdef WWISEUNITY_PLUGIN_DISTORTION

	if ( AK::SoundEngine::RegisterPlugin( AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_GUITARDISTORTION, CreateGuitarDistortionFX, CreateGuitarDistortionFXParams ) != AK_Success )
    {
        throw std::exception( "Could not initialize GuitarDistortion plugin." );
        return false;
    }

#endif

#ifdef WWISEUNITY_PLUGIN_MATRIXREVERB

	if ( AK::SoundEngine::RegisterPlugin( AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_MATRIXREVERB, CreateMatrixReverbFX, CreateMatrixReverbFXParams ) != AK_Success )
    {
        throw std::exception( "Could not initialize MatrixReverb plugin." );
        return false;
    }

#endif

#ifdef WWISEUNITY_PLUGIN_PEAKLIMITER

	if ( AK::SoundEngine::RegisterPlugin( AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_PEAKLIMITER, CreatePeakLimiterFX, CreatePeakLimiterFXParams ) != AK_Success )
    {
        throw std::exception( "Could not initialize PeakLimiter plugin." );
        return false;
    }

#endif

#ifdef WWISEUNITY_PLUGIN_ROOMVERB

	if ( AK::SoundEngine::RegisterPlugin( AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_ROOMVERB, CreateRoomVerbFX, CreateRoomVerbFXParams ) != AK_Success )
    {
        throw std::exception( "Could not initialize RoomVerb plugin." );
        return false;
    }

#endif

#ifdef WWISEUNITY_PLUGIN_DELAY

	if ( AK::SoundEngine::RegisterPlugin( AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_DELAY, CreateDelayFX, CreateDelayFXParams ) != AK_Success )
    {
        throw std::exception( "Could not initialize Delay plugin." );
        return false;
    }

#endif

#ifdef WWISEUNITY_PLUGIN_SILENCE

	if ( AK::SoundEngine::RegisterPlugin( AkPluginTypeSource, AKCOMPANYID_AUDIOKINETIC, AKSOURCEID_SILENCE, CreateSilenceSource, CreateSilenceSourceParams ) != AK_Success )
    {
        throw std::exception( "Could not initialize Silence source plugin." );
        return false;
    }

#endif

	return true;
}

void WwiseEngine::ProcessAudio()
{
    // Process bank requests, events, positions, RTPC, etc.
    AK::SoundEngine::RenderAudio();
}

void WwiseEngine::Term()
{
#ifdef DEBUG
	//
	// Terminate Communication Services
	//
	AK::Comm::Term();
#endif

    //
    // Terminate the music engine
    //
    
    AK::MusicEngine::Term();

	//
    // Terminate the sound engine
    //
    
    AK::SoundEngine::Term();

    // Terminate the streaming device and streaming manager
    
    // CAkFilePackageLowLevelIOBlocking::Term() destroys its associated streaming device 
    // that lives in the Stream Manager, and unregisters itself as the File Location Resolver.
    g_lowLevelIO.Term();
    
    if ( AK::IAkStreamMgr::Get() )
        AK::IAkStreamMgr::Get()->Destroy();

    // Terminate the Memory Manager
    AK::MemoryMgr::Term();
}

int WwiseEngine::SetBasePath(WU_STRING basePath)
{
	// we have to pass from char* to wchar_t*
	size_t origsize = strlen(basePath) + 1;
	const size_t newsize = MAX_PATH;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, basePath, _TRUNCATE);

	return g_lowLevelIO.SetBasePath(wcstring);
}

int WwiseEngine::SetLangSpecificDirName(WU_STRING specificDirName)
{
	size_t origsize = strlen(specificDirName) + 1;
	const size_t newsize = MAX_PATH;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, specificDirName, _TRUNCATE);

	return g_lowLevelIO.SetLangSpecificDirName(wcstring);
}

int WwiseEngine::LoadBank(WU_STRING bankName)
{
	AkBankID bankID; // Not used. These banks can be unloaded with their file name.
	return AK::SoundEngine::LoadBank(bankName, AK_DEFAULT_POOL_ID, bankID);
}

int WwiseEngine::UnloadBank(WU_STRING bankName)
{
	return AK::SoundEngine::UnloadBank(bankName);
}

int WwiseEngine::RegisterGameObject(AkGameObjectID akId, WU_STRING gameObjectLabel)
{
	return AK::SoundEngine::RegisterGameObj(akId, gameObjectLabel);
}

int WwiseEngine::UnregisterGameObject(AkGameObjectID akId)
{
	return AK::SoundEngine::UnregisterGameObj(akId);
}

int WwiseEngine::UnregisterAllGameObject()
{
	return AK::SoundEngine::UnregisterAllGameObj();
}

void WwiseEngine::PostEvent(WU_STRING eventName, AkGameObjectID gameObject)
{
	AK::SoundEngine::PostEvent(eventName, gameObject);
}
void WwiseEngine::PostEvent(AkUniqueID eventId, AkGameObjectID gameObject)
{
	AK::SoundEngine::PostEvent(eventId, gameObject);
}

void WwiseEngine::SetRTPCValue(WU_STRING rtpcName, AkRtpcValue value)
{
	AK::SoundEngine::SetRTPCValue(rtpcName, value);
}
void WwiseEngine::SetRTPCValue(WU_STRING rtpcName, AkRtpcValue value, AkGameObjectID gameObjectId)
{
	AK::SoundEngine::SetRTPCValue(rtpcName, value, gameObjectId);
}
void WwiseEngine::SetRTPCValue(AkRtpcID rtpcId, AkRtpcValue value, AkGameObjectID gameObjectId)
{
	AK::SoundEngine::SetRTPCValue(rtpcId, value, gameObjectId);
}

void WwiseEngine::SetState(WU_STRING stateGroup, WU_STRING state)
{
	AK::SoundEngine::SetState(stateGroup, state);
}
void WwiseEngine::SetState(AkStateGroupID stateGroupId, AkStateID stateId)
{
	AK::SoundEngine::SetState(stateGroupId, stateId);
}

void WwiseEngine::SetSwitch(WU_STRING switchGroupName, WU_STRING switchName, AkGameObjectID gameObjectId)
{
	AK::SoundEngine::SetSwitch(switchGroupName, switchName, gameObjectId);
}
void WwiseEngine::SetSwitch(AkSwitchGroupID switchGroupId, AkSwitchStateID switchId, AkGameObjectID gameObjectId)
{
	AK::SoundEngine::SetSwitch(switchGroupId, switchId, gameObjectId);
}

int WwiseEngine::SetListenerPosition(AkListenerPosition& akPosition)
{
	return AK::SoundEngine::SetListenerPosition(akPosition);
}
int WwiseEngine::SetListenerPosition(int listenerIndex, AkListenerPosition& akPosition)
{
	return AK::SoundEngine::SetListenerPosition(akPosition, listenerIndex);
}

int WwiseEngine::SetPosition(AkGameObjectID gameObjectId, AkSoundPosition& position)
{
	return AK::SoundEngine::SetPosition(gameObjectId, position);
}
int WwiseEngine::SetPosition(AkGameObjectID gameObjectId, AkSoundPosition& position, int listenerIndex)
{
	return AK::SoundEngine::SetPosition(gameObjectId, position, listenerIndex);
}

int WwiseEngine::SetGameObjectActiveListeners(AkGameObjectID gameObjectId, AkUInt32 listenerMask)
{
	return AK::SoundEngine::SetActiveListeners(gameObjectId, listenerMask);
}