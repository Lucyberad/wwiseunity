using UnityEngine;
using System.Collections;

[AddComponentMenu("Wwise/WwiseGameObject")]
public class WwiseGameObject : MonoBehaviour
{

    #region Public Members

    /// <summary>
    /// Define the sound game object name.
    /// There is no need to choose a unique name
    /// </summary>
    public string SoundGameObjectName = "None";

    /// <summary>
    /// Define the SoundListener to link with.
    /// Default Listener index is 0.
    /// Max Listener index is 7.
    /// </summary>
    public int ListenerIndex = 0;

    #endregion

    #region Private Members
 
	private uint m_soundGameObjectId;

    #endregion

    #region Monobehavior Override

	void Start() 
    {
        // be sure that the listener index is in the range...
		if (ListenerIndex > 7 || ListenerIndex < 0)
        {
            Debug.LogError("WwiseGameObject : the listener index is out of range [0..7] : " + ListenerIndex);
            Debug.Break();
        }

        // register a sound game object
        m_soundGameObjectId = WwiseEngine.AddSoundGameObject(SoundGameObjectName);
	
		// we make the gameobject to use only one listener (despite the method allow multiple listener by the second argument listener bitmask).
		WwiseEngine.SetSoundGameObjectActiveListeners(m_soundGameObjectId, (uint)(1 << (ListenerIndex)));
	}
	
	// Update is called once per frame
	void Update () 
    {
    	updatePosition();
	}

    void OnDispose()
    {
    	WwiseEngine.RemoveSoundGameObject(m_soundGameObjectId);
    }
    #endregion

    #region Protected Methods

    // the purpose of this method is to be overrided for any other use of SoundGameObject
    protected void updatePosition()
    {
		WwiseEngine.SetSoundGameObjectPosition(m_soundGameObjectId, transform.position, transform.forward);
    }

    #endregion

    #region Public Methods

    public void PostEvent(string eventName)
    {
		WwiseEngine.PostSoundEvent(eventName, m_soundGameObjectId);
    }

    public void PostEvent(ulong eventId)
    {
		WwiseEngine.PostSoundEvent(eventId, m_soundGameObjectId);
    }

	public void SetRTPC(string rtpcName, float val)
    {
		WwiseEngine.UpdateRTPCValue(rtpcName, val, m_soundGameObjectId);
    }

    public void SetRTPC(ulong rtpcId, float val)
    {
		WwiseEngine.UpdateRTPCValue(rtpcId, val, m_soundGameObjectId);
    }

    public void SetSwitch(string switchGroup, string switchName)
    {
        WwiseEngine.SetSoundSwitch(switchGroup, switchName, m_soundGameObjectId);
    }

    public void SetSwitch(ulong switchGroupId, ulong switchId)
    {
        WwiseEngine.SetSoundSwitch(switchGroupId, switchId, m_soundGameObjectId);
    }
	
    #endregion
}
