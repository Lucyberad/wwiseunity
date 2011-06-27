//#define WWISE_DISABLE

using UnityEngine;
using System;
using System.Collections;
using System.Runtime.InteropServices;

public static class WwiseEngine
{
	public const uint GAME_OBJECT_GLOBAL		= 4294967295U;
	
	public const uint AK_SPEAKER_FRONT_LEFT		= 0x1;       ///< Front left speaker bit mask
	public const uint AK_SPEAKER_FRONT_RIGHT	= 0x2;       ///< Front right speaker bit mask
	public const uint AK_SPEAKER_FRONT_CENTER	= 0x4;       ///< Front center speaker bit mask
	public const uint AK_SPEAKER_LOW_FREQUENCY	= 0x8;       ///< Low-frequency speaker bit mask
	public const uint AK_SPEAKER_BACK_LEFT		= 0x10;      ///< Rear left speaker bit mask
	public const uint AK_SPEAKER_BACK_RIGHT		= 0x20;      ///< Rear right speaker bit mask
	public const uint AK_SPEAKER_BACK_CENTER	= 0x100;     ///< Rear center speaker ("surround speaker") bit mask
	public const uint AK_SPEAKER_SIDE_LEFT		= 0x200;     ///< Side left speaker bit mask
	public const uint AK_SPEAKER_SIDE_RIGHT		= 0x400;     ///< Side right speaker bit mask

	public const uint AK_SPEAKER_SETUP_MONO		= AK_SPEAKER_FRONT_CENTER;     ///< 1.0 setup channel mask
	public const uint AK_SPEAKER_SETUP_0POINT1	= AK_SPEAKER_LOW_FREQUENCY;    ///< 0.1 setup channel mask
	public const uint AK_SPEAKER_SETUP_1POINT1	= ( AK_SPEAKER_FRONT_CENTER		| AK_SPEAKER_LOW_FREQUENCY ); ///< 1.1 setup channel mask
	public const uint AK_SPEAKER_SETUP_STEREO	= ( AK_SPEAKER_FRONT_LEFT		| AK_SPEAKER_FRONT_RIGHT );   ///< 2.0 setup channel mask
	public const uint AK_SPEAKER_SETUP_2POINT1	= ( AK_SPEAKER_SETUP_STEREO		| AK_SPEAKER_LOW_FREQUENCY ); ///< 2.1 setup channel mask
	public const uint AK_SPEAKER_SETUP_3STEREO	= ( AK_SPEAKER_SETUP_STEREO		| AK_SPEAKER_FRONT_CENTER );  ///< 3.0 setup channel mask
	public const uint AK_SPEAKER_SETUP_3POINT1	= ( AK_SPEAKER_SETUP_3STEREO	| AK_SPEAKER_LOW_FREQUENCY ); ///< 3.1 setup channel mask
	public const uint AK_SPEAKER_SETUP_4		= ( AK_SPEAKER_SETUP_STEREO		| AK_SPEAKER_BACK_LEFT | AK_SPEAKER_BACK_RIGHT ); ///< 4.0 setup channel mask
	public const uint AK_SPEAKER_SETUP_4POINT1	= ( AK_SPEAKER_SETUP_4			| AK_SPEAKER_LOW_FREQUENCY ); ///< 4.1 setup channel mask
	public const uint AK_SPEAKER_SETUP_5		= ( AK_SPEAKER_SETUP_4			| AK_SPEAKER_FRONT_CENTER );  ///< 5.0 setup channel mask
	public const uint AK_SPEAKER_SETUP_5POINT1	= ( AK_SPEAKER_SETUP_5			| AK_SPEAKER_LOW_FREQUENCY ); ///< 5.1 setup channel mask
	public const uint AK_SPEAKER_SETUP_7POINT1	= ( AK_SPEAKER_SETUP_5POINT1	| AK_SPEAKER_SIDE_LEFT | AK_SPEAKER_SIDE_RIGHT ); ///< 7.1 setup channel mask

#if !WWISE_DISABLE

	#region DllImport WwiseUnity

	//import Wwise Wrapper 
	[DllImport("WwiseUnity")]
	private static extern void DestroyEngine();
	[DllImport("WwiseUnity")]
	private static extern bool Init();
	[DllImport("WwiseUnity")]
	private static extern void ProcessAudio();
	[DllImport("WwiseUnity")]
	private static extern void Term();
	[DllImport("WwiseUnity")]
	private static extern int SetBasePath(string basePath);
	[DllImport("WwiseUnity")]
	private static extern int SetLangSpecificDirName(string specificDirName);

	[DllImport("WwiseUnity")]
	private static extern int LoadBank(string bankName);
	[DllImport("WwiseUnity")]
	private static extern int UnloadBank(string bankName);

	[DllImport("WwiseUnity")]
	private static extern void SetState(string stateGroup, string state);
	[DllImport("WwiseUnity")]
	private static extern void SetStateById(ulong stateGroupId, ulong stateId);
	// Game Object management
	[DllImport("WwiseUnity")]
	private static extern int RegisterGameObject(uint akId, string gameObjectLabel);
	[DllImport("WwiseUnity")]
	private static extern int UnregisterGameObject(uint akId);
	[DllImport("WwiseUnity")]
	private static extern int UnregisterAllGameObject();
	[DllImport("WwiseUnity")]
	private static extern int SetPosition(uint gameObjectId, float posX, float posY, float posZ, float orientationX, float orientationY, float orientationZ);
	[DllImport("WwiseUnity")] 
	private static extern int SetPositionByListener(uint gameObjectId, float posX, float posY, float posZ, float orientationX, float orientationY, float orientationZ, int listenerIndex);

	[DllImport("WwiseUnity")]
	private static extern void PostEvent(string eventName, uint gameObject);
	[DllImport("WwiseUnity")]
	private static extern void PostEventById(ulong eventId, uint gameObject);

	[DllImport("WwiseUnity")]
	private static extern void SetRTPCValueGlobal(string rtpcName, float value);
	[DllImport("WwiseUnity")]
	private static extern void SetRTPCValue(string rtpcName, float value, uint gameObjectId);
	[DllImport("WwiseUnity")]
	private static extern void SetRTPCValueById(ulong rtpcId, float value, uint  gameObjectId);

	[DllImport("WwiseUnity")]
	private static extern void SetSwitch(string switchGroupName, string switchName, uint gameObjectId);
	[DllImport("WwiseUnity")]
	private static extern void SetSwitchById(ulong switchGroupId, ulong switchId, uint gameObjectId);
	// Listener Management
	[DllImport("WwiseUnity")]
	private static extern int SetListenerPosition(float posX, float posY, float posZ, float orientationFrontX, float orientationFrontY, float orientationFrontZ, float orientationTopX, float orientationTopY, float orientationTopZ);
	[DllImport("WwiseUnity")]
	private static extern int SetListenerPositionById(int listenerIndex, float posX, float posY, float posZ, float orientationFrontX, float orientationFrontY, float orientationFrontZ, float orientationTopX, float orientationTopY, float orientationTopZ);
	[DllImport("WwiseUnity")]
	private static extern int SetGameObjectActiveListeners(uint gameObjectId, uint listenerMask);

	// Trigger
	[DllImport("WwiseUnity")]
	private static extern int PostTriggerById( uint triggerID, uint gameObjectID );
	[DllImport( "WwiseUnity" )]
	private static extern int PostTrigger( string triggerName, uint gameObjectID );

	// L'espace...
	[DllImport( "WwiseUnity" )]
	private static extern int SetListenerSpatialization( uint uIndex, bool bSpatialized );
	[DllImport( "WwiseUnity" )]
	private static extern uint MyChannelMaskFromNumChannels( uint in_uNumChannels );
	[DllImport( "WwiseUnity" )]
	private static extern uint MyChannelMaskToNumChannels( uint in_uChannelMask );
	[DllImport( "WwiseUnity" )]
	private static extern uint MyGetSpeakerConfiguration();

	#endregion

	#region Private Members

    private static uint m_nextSoundGameObjectId = 10;
    private static bool m_hasBeenInitialize = false;

	#endregion

	#region Private Working Members

    static int m_tempResult = 0;

	#endregion 

#endif

	#region Public Methods

	// this method is call before any Start method
    public static void Initialize(string BasePath, string LangSpecificDirName)
    {
#if !WWISE_DISABLE
        // create sound engine and initialize it
        m_hasBeenInitialize = Init();
        if (!m_hasBeenInitialize)
        	HandleError("Sound engine initialization has failed");

        // init basic properties
        m_tempResult = SetBasePath(BasePath);
        if (m_tempResult != 1)
            HandleError("Set base path failed : " + BasePath + " \nerror : " + m_tempResult);
	
        m_tempResult = SetLangSpecificDirName(LangSpecificDirName);
        if (m_tempResult != 1)
			HandleError("SetLangSpecificDirName failed : " + LangSpecificDirName + " \nerror : " + m_tempResult);
        Debug.Log("WwiseEngine : Sound Engine initialized");
#endif
    }

	public static void LoadSoundBanks(string[] banksName) 
    {
#if !WWISE_DISABLE
        foreach (string bankName in banksName)
            LoadSoundBank(bankName);
#endif
	}

	public static void Update()
    {
#if !WWISE_DISABLE
        if (true)
            ProcessAudio();
#endif
	}

    public static void Dispose()
    {
#if !WWISE_DISABLE
        if (m_hasBeenInitialize)
        {
            m_hasBeenInitialize = false;
            // finalize the sound engine
            Term();
            // destroy the sound engine
            DestroyEngine();

            Debug.Log("[WwiseEngine] Sound Engine Destroyed");
        }
#endif
    }
    #endregion

    #region SoundEngine Management

    #region Bank add / remove

    public static void LoadSoundBank(string bankName)
    {
#if !WWISE_DISABLE
		Debug.Log("[WwiseEngine] loading bank - " + bankName);
				if (!m_hasBeenInitialize)
			HandleError("Can't load bank until Initialize(...) has'nt been called.");

        m_tempResult = LoadBank(bankName);
        if (m_tempResult != 1)
			HandleError("Cannot load SoundBank " + bankName + " \nerror : " + m_tempResult);
#endif
    }

    public static void UnloadSoundBank(string bankName)
    {
		#if !WWISE_DISABLE
		Debug.Log("[WwiseEngine] loading bank - " + bankName);
		if (!m_hasBeenInitialize)
			HandleError("Can't unload bank until Initialize(...) has'nt been called.");
		
        m_tempResult = UnloadBank(bankName);
        if (m_tempResult != 1)
			HandleError("Cannot unload SoundBank " + bankName + " \nerror : " + m_tempResult);
		#endif
    }


    #endregion

    #region GameObject add / Remove
    public static uint AddSoundGameObject(string gameObjectLabel)
	{
#if !WWISE_DISABLE
		if (!m_hasBeenInitialize)
			HandleError("Can't register Game Object until Initialize(...) has'nt been called.");
		
        // compute game object id and prepare it for the next registering object
        uint gameObjectId = m_nextSoundGameObjectId++;

        // create a game object
        m_tempResult = RegisterGameObject(gameObjectId, gameObjectLabel);
        if (m_tempResult != 1)
			HandleError("AddSoundGameObject failed " + gameObjectLabel + " \nerror : " + m_tempResult);

        return gameObjectId;
#else
		return 0;
#endif
    }

    public static void RemoveSoundGameObject(uint gameObjectId)
    {
#if !WWISE_DISABLE
		if (!m_hasBeenInitialize)
			HandleError("Can't remove Game Object until Initialize(...) has'nt been called.");
		
        m_tempResult = UnregisterGameObject(gameObjectId);
        if (m_tempResult != 1)
			HandleError("RemoveSoundGameObject failed " + gameObjectId + " \nerror : " + m_tempResult);
#endif
    }

    public static void RemoveAllSoundGameObject()
    {
#if !WWISE_DISABLE
		if (!m_hasBeenInitialize)
			HandleError("Can't remove Game Object until Initialize(...) has'nt been called.");
		
        m_tempResult = UnregisterAllGameObject();
        if (m_tempResult != 1)
            HandleError("RemoveAllSoundGameObject failed \nerror : " + m_tempResult);
#endif
    }
    #endregion

    #region GameObject Position
    public static void SetSoundGameObjectPosition(uint gameObjectId, Vector3 pos, Vector3 orientation)
    {
#if !WWISE_DISABLE
        m_tempResult = SetPosition(gameObjectId, pos.x, pos.y, pos.z, orientation.x, orientation.y, orientation.z);
        if (m_tempResult != 1)
			HandleError("SetSoundGameObjectPosition " + gameObjectId + " \nerror : " + m_tempResult);
#endif
    }

    public static void SetSoundGameObjectPosition(uint gameObjectId, Vector3 pos, Vector3 orientation, int listenerIndex)
    {
#if !WWISE_DISABLE
        m_tempResult = SetPositionByListener(gameObjectId, pos.x, pos.y, pos.z, orientation.x, orientation.y, orientation.z, listenerIndex);
        if (m_tempResult != 1)
			HandleError("SetSoundGameObjectPosition " + gameObjectId + " \nerror : " + m_tempResult);
#endif
    }
    #endregion

	#region GameObject/Listeners

	public static void SetSoundGameObjectActiveListeners( uint gameObjectId, uint listenerMask )
	{
#if !WWISE_DISABLE
		m_tempResult = SetGameObjectActiveListeners( gameObjectId, listenerMask );
		if ( m_tempResult != 1 )
			HandleError( "SetGameObjectActiveListeners failed \nerror : " + m_tempResult );
#endif
	}

	#endregion

    #region Post Sound
    public static void PostSoundEvent(string eventName, uint gameObjectId)
    {
#if !WWISE_DISABLE
        PostEvent(eventName, gameObjectId);
#endif
    }

    public static void PostSoundEvent(ulong eventId, uint gameObjectId)
    {
#if !WWISE_DISABLE
        PostEventById(eventId, gameObjectId);
#endif
    }
    #endregion

    #region RTPC
	public static void UpdateRTPCValue(string rtpcName, float value)
    {
#if !WWISE_DISABLE
        SetRTPCValueGlobal(rtpcName, value);
#endif
    }
    public static void UpdateRTPCValue(string rtpcName, float value, uint gameObjectId)
    {
#if !WWISE_DISABLE
        SetRTPCValue(rtpcName, value, gameObjectId);
#endif
    }

    public static void UpdateRTPCValue(ulong rtpcId, float value, uint gameObjectId)
    {
#if !WWISE_DISABLE
        SetRTPCValueById(rtpcId, value, gameObjectId);
#endif
    }
    #endregion

    #region Switch
    public static void SetSoundSwitch(string switchGroupName, string switchName, uint gameObjectId)
    {
#if !WWISE_DISABLE
        SetSwitch(switchGroupName, switchName, gameObjectId);
#endif
    }

    public static void SetSoundSwitch(ulong switchGroupId, ulong switchId, uint gameObjectId)
    {
#if !WWISE_DISABLE
        SetSwitchById(switchGroupId, switchId, gameObjectId);
#endif
    }
    #endregion

	#region Listener Position
	public static void SetSoundListenerPosition(Vector3 position, Vector3 orientationFront, Vector3 orientationTop)
    {
#if !WWISE_DISABLE
        m_tempResult = SetListenerPosition(position.x, position.y, position.z,
                            orientationFront.x, orientationFront.y, orientationFront.z,
                            orientationTop.x, orientationTop.y, orientationTop.z);
        if (m_tempResult != 1)
			HandleError("SetSoundListenerPosition failed \nerror : " + m_tempResult);
#endif
    }

    public static void SetSoundListenerPosition(int listenerIndex, Vector3 position, Vector3 orientationFront, Vector3 orientationTop)
    {
#if !WWISE_DISABLE
        m_tempResult = SetListenerPositionById(listenerIndex, 
                                position.x, position.y, position.z,
                                orientationFront.x, orientationFront.y, orientationFront.z,
                                orientationTop.x, orientationTop.y, orientationTop.z);
        if (m_tempResult != 1)
			HandleError("SetSoundListenerPosition failed \nerror : " + m_tempResult);
#endif
    }
    #endregion

    #region State Management

    public static void SetSoundState(string stateGroupName, string stateName)
    {
#if !WWISE_DISABLE
        SetState(stateGroupName, stateName);
#endif
    }
    public static void SetSoundState(ulong stateGroupId, ulong stateId)
    {
#if !WWISE_DISABLE
        SetStateById(stateGroupId, stateId);
#endif
    }

    #endregion

	#region Trigger
	public static int PostSoundTrigger( uint triggerID, uint gameObjectID )
	{
#if !WWISE_DISABLE
		return PostTriggerById( triggerID, gameObjectID );
#endif
	}

	public static int PostSoundTrigger( string triggerName, uint gameObjectID )
	{
#if !WWISE_DISABLE
		return PostTrigger( triggerName, gameObjectID );
#endif
	}
	#endregion

	#region Spatiale

	public static int SetSoundListenerSpatialization( uint uIndex, bool bSpatialized )
	{
#if !WWISE_DISABLE
		return SetSoundListenerSpatialization( uIndex, bSpatialized );
#endif
	}

	public static uint ChannelMaskFromNumChannels( uint in_uNumChannels )
	{
#if !WWISE_DISABLE
		return MyChannelMaskFromNumChannels( in_uNumChannels );
#endif
	}

	public static uint ChannelMaskToNumChannels( uint in_uChannelMask )
	{
#if !WWISE_DISABLE
		return MyChannelMaskToNumChannels( in_uChannelMask );
#endif
	}

	public static uint GetSpeakerConfiguration()
	{
#if !WWISE_DISABLE
		return MyGetSpeakerConfiguration();
#endif
	}

	#endregion

	#region Error Handling

	public static void HandleError(string message)
	{
#if !WWISE_DISABLE
	    Debug.LogError("[WwiseEngine] " + message);
		Dispose();
		Debug.Break();
#endif
	}
	
	#endregion

	#endregion
}
